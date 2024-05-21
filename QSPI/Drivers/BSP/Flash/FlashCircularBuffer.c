/**
******************************************************************************
* @file    FlashCircularBuffer.c
* @author  DNK-043
* @date    28-Dec-2022
* @brief   Source file for storing data in circular buffer in QSPI Flash
******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/

#include "FlashCircularBuffer.h"
#include "stdbool.h"
#include "main.h"
#include "MX25L_QSPI_Flash.h"
#include "flash.h"

/* Macros Defintions ---------------------------------------------------------*/


/* Flash Circular Buffer Variables ---------------------------------------------------------*/
flash_circular_buffer fcb;


/* Function Definitions ---------------------------------------------------------*/

/*
 * @brief  Function to check whether data is available to be read
 * @param  buffer    Pointer to flash circular buffer
 * @retval bool 
*/
static bool isDataAvailable(flash_circular_buffer* buffer)
{
  return buffer->data_available;
}

/*
 * @brief  Function to check whether memory is available
 * @param  buffer    Pointer to flash circular buffer
 * @retval bool 
*/
static bool isMemoryAvailable(flash_circular_buffer* buffer)
{
  return buffer->memory_available;
}



/*
 * @brief  Function to Initialize Circular Buffer
 * @param  buffer    Pointer to flash circular buffer
 * @retval None
*/
void FlashCircularBufferInit(flash_circular_buffer* buffer)
{
  buffer->tx_data = NULL;
  buffer->rx_data = NULL;
  buffer->head = FLASH_BUFFER_START_ADDR;
  buffer->tail = FLASH_BUFFER_START_ADDR;
  buffer->data_available = false;
  buffer->memory_available = true;
}



/*
 * @brief  Function to Store data in Flash Ring Buffer
 * @param  buffer    Pointer to flash circular buffer
 * @param  dataToBuffer    Pointer to dataset to store in ring buffer
 * @retval FCB Status
*/

#if(!CUSTOM_DEBUG)
fcb_status WriteDatasetToFlash(flash_circular_buffer* buffer, void* dataToBuffer, uint16_t length)
{
  uint32_t dst_addr,next_addr,err_code,data_len;
  uint32_t current_addr; 
  uint32_t head_sector, tail_sector;


  buffer->tx_data = (DATASET*)dataToBuffer;
  dst_addr = buffer->head;
  data_len = sizeof(DATASET);

  /* Calculate next address */  
  if((buffer->head + data_len) >= FLASH_BUFFER_SIZE)
  {
    next_addr = FLASH_BUFFER_START_ADDR;
  }
  else
  {
    next_addr = (unsigned int)(buffer->head + data_len);
  }

  
  /*Check whether the buffer head and tail sectors are going to overlap*/
  if(buffer->tail > buffer->head)
  {
    // if the difference is less than 4096
    if((buffer->tail - buffer->head) < QSPI_BLOCK_SIZE_64K)
    {
      //Calculate current sector number from the address
      head_sector = next_addr / QSPI_BLOCK_SIZE_64K;
      tail_sector = buffer->tail / QSPI_BLOCK_SIZE_64K;

      /*Check whether head and tail sector are same */
      if(head_sector == tail_sector)
      {
        printf("FCB : No empty locations to write\r\n. Next Addr: %lu  Tail: %u\n",next_addr,buffer->tail);
        return FCB_ADDR_ON_SAME_SECTOR;
      }
    }
  }


  /* Check availablity of free memory locations */
 /* Not storing the data into the location just before the circular buffer tail
 (meaning that the head would advance to the current location of the tail),
  we're about to overflow the buffer and so we don't write the character or
  advance the head. */
  if(next_addr != buffer->tail)
  {
    /* Write data to flash and increment the head position */
    err_code = Flash_Write(buffer->tx_data, data_len, dst_addr);

    if(err_code == QSPI_OK)
    {
      buffer->head = buffer->head + data_len;
      buffer->data_available = true;
      printf("Flash Buffer Current Head: %d, Tail: %d \n",fcb.head,fcb.tail);
      err_code = QSPI_OK;
    }
    else
    {
      printf("FCB: Write Operation Failed\n");
      err_code = QSPI_ERROR;
    }


    /*Reset the circular buffer head to start position,
     if the head has reached the end address of memory */
    if(buffer->head == FLASH_BUFFER_END_ADDR)
    {
      buffer->head = FLASH_BUFFER_START_ADDR;
    }
  }
  else
  {
    buffer->memory_available = false;
    err_code = FCB_NO_EMPTY_LOCATIONS;
    printf("FCB Status: No empty locations");
  }
  
  return err_code;

}
#else
fcb_status WriteDatasetToFlash(flash_circular_buffer* buffer, void* dataToBuffer, uint16_t length)
{
  uint32_t dst_addr,next_addr,err_code,data_len;
  uint32_t current_addr;
  uint32_t head_sector, tail_sector;


  buffer->tx_data = (my_info*)dataToBuffer;
  dst_addr = buffer->head;
  data_len = sizeof(my_info);

  /* Calculate next address */
  if((buffer->head + data_len) >= FLASH_BUFFER_SIZE)
  {
    next_addr = FLASH_BUFFER_START_ADDR;
  }
  else
  {
    next_addr = (unsigned int)(buffer->head + data_len);
  }


  /*Check whether the buffer head and tail sectors are going to overlap*/
  if(buffer->tail > buffer->head)
  {
    // if the difference is less than 4096
    if((buffer->tail - buffer->head) < QSPI_BLOCK_SIZE_64K)
    {
      //Calculate current sector number from the address
      head_sector = next_addr / QSPI_BLOCK_SIZE_64K;
      tail_sector = buffer->tail / QSPI_BLOCK_SIZE_64K;

      /*Check whether head and tail sector are same */
      if(head_sector == tail_sector)
      {
        printf("FCB : No empty locations to write\r\n. Next Addr: %lu  Tail: %u\n",next_addr,buffer->tail);
        return FCB_ADDR_ON_SAME_SECTOR;
      }
    }
  }


  /* Check availablity of free memory locations */
 /* Not storing the data into the location just before the circular buffer tail 
 (meaning that the head would advance to the current location of the tail),
  we're about to overflow the buffer and so we don't write the character or
  advance the head. */
  if(next_addr != buffer->tail)
  {
    /* Write data to flash and increment the head position */
    err_code = Flash_Write(buffer->tx_data, data_len, dst_addr);

    if(err_code == QSPI_OK)
    {
      buffer->head = buffer->head + data_len;
      buffer->data_available = true;
      printf("Flash Buffer Current Head: %d, Tail: %d \n",fcb.head,fcb.tail);
      err_code = QSPI_OK;
    }
    else
    {
      printf("FCB: Write Operation Failed\n");
      err_code = QSPI_ERROR;
    }

    
    /*Reset the circular buffer head to start position,
     if the head has reached the end address of memory */  
    if(buffer->head == FLASH_BUFFER_END_ADDR)
    {
      buffer->head = FLASH_BUFFER_START_ADDR;
    }
  }
  else
  {
    buffer->memory_available = false;
    err_code = FCB_NO_EMPTY_LOCATIONS;
    printf("FCB Status: No empty locations");
  }
  
  return err_code;

}
#endif

/*
 * @brief  Function to Read data from Flash Circular Buffer
 * @param  buffer    Pointer to flash circular buffer
 * @param  dataToBuffer    Pointer to dataset to store in ring buffer
 * @retval FCB Status
*/

#if(!CUSTOM_DEBUG)
fcb_status ReadDatasetFromFlash(flash_circular_buffer* buffer,void* rcvBuffer,uint32_t length)
{
  uint32_t src_addr,data_len,err_code;
  
  /* Storing reciev buffer */
  buffer->rx_data = (DATASET*)rcvBuffer;


  data_len = length;
  src_addr = buffer->tail;

  /*Check wether data is available to read from flash */  
  if(src_addr != buffer->head)
  {
      err_code = Flash_Read(buffer->rx_data, data_len,src_addr);

      if(err_code == FCB_OK)
      {
        buffer->tail = buffer->tail + data_len;
        printf("Flash Buffer Current Head: %d, Tail: %d \n",fcb.head,fcb.tail);
      }
      else
      {
        err_code = FCB_READ_ERROR;
        printf("FCB: Read Operation failed");
      }   

    /*Reset the circular buffer tail to start position,
     if the tail has reached the end address of memory */  
    if(buffer->tail == FLASH_BUFFER_END_ADDR)
    {
      /* Reset the tail position */
      buffer->tail = FLASH_BUFFER_START_ADDR;
    }
    
    /* Erase the read sector if the buffer head isn't locating memory
     in that sector */
      EraseFlashSector(buffer,src_addr);
      
  }
  else
  {
    buffer->data_available = false;
    printf("FCB Status: No data available to read\n");
    err_code = FCB_NO_DATA_AVAILABLE;
  }

  return err_code;
}
#else
fcb_status ReadDatasetFromFlash(flash_circular_buffer* buffer,void* rcvBuffer,uint32_t length)
{
  uint32_t src_addr,data_len,err_code;

  /* Storing reciev buffer */
  buffer->rx_data = (my_info*)rcvBuffer;


  data_len = length;
  src_addr = buffer->tail;

  /*Check wether data is available to read from flash */
  if(src_addr != buffer->head)
  {
      err_code = Flash_Read(buffer->rx_data, data_len,src_addr);

      if(err_code == FCB_OK)
      {
        buffer->tail = buffer->tail + data_len;
        printf("Flash Buffer Current Head: %d, Tail: %d \n",fcb.head,fcb.tail);
      }
      else
      {
        err_code = FCB_READ_ERROR;
        printf("FCB: Read Operation failed");
      }

    /*Reset the circular buffer tail to start position,
     if the tail has reached the end address of memory */
    if(buffer->tail == FLASH_BUFFER_END_ADDR)
    {
      /* Reset the tail position */
      buffer->tail = FLASH_BUFFER_START_ADDR;
    }

    /* Erase the read sector if the buffer head isn't locating memory
     in that sector */
      EraseFlashSector(buffer,src_addr);

  }
  else
  {
    buffer->data_available = false;
    printf("FCB Status: No data available to read\n");
    err_code = FCB_NO_DATA_AVAILABLE;
  }

  return err_code;
}
#endif

#if(!CUSTOM_DEBUG)
fcb_status EraseFlashSector(flash_circular_buffer* buffer,uint32_t sector_addr)
{
  uint32_t err_code = FCB_OK;

   
 /* Erase the previosuly read sector as soon as the current flash buffer tail
  position points to adddress on the next */
 switch(buffer->tail)
 {
   case ((BLOCK1_ADDR - ((QSPI_BLOCK_SIZE_64K * 1) % sizeof(DATASET)) + sizeof(DATASET))):   
   case ((BLOCK2_ADDR - ((QSPI_BLOCK_SIZE_64K * 2) % sizeof(DATASET)) + sizeof(DATASET))):      
   case ((BLOCK3_ADDR - ((QSPI_BLOCK_SIZE_64K * 3) % sizeof(DATASET)) + sizeof(DATASET))):      
   case ((BLOCK4_ADDR - ((QSPI_BLOCK_SIZE_64K * 4) % sizeof(DATASET)) + sizeof(DATASET))):      
   case ((BLOCK5_ADDR - ((QSPI_BLOCK_SIZE_64K * 5) % sizeof(DATASET)) + sizeof(DATASET))):   
   case ((BLOCK6_ADDR - ((QSPI_BLOCK_SIZE_64K * 6) % sizeof(DATASET)) + sizeof(DATASET))):      
   case ((BLOCK7_ADDR - ((QSPI_BLOCK_SIZE_64K * 7) % sizeof(DATASET)) + sizeof(DATASET))):          
  
   case ((BLOCK8_ADDR - ((QSPI_BLOCK_SIZE_64K * 8) % sizeof(DATASET)) + sizeof(DATASET))):          
   case ((BLOCK9_ADDR - ((QSPI_BLOCK_SIZE_64K * 9) % sizeof(DATASET)) + sizeof(DATASET))):          
   case ((BLOCK10_ADDR - ((QSPI_BLOCK_SIZE_64K * 10) % sizeof(DATASET)) + sizeof(DATASET))):          
   case ((BLOCK11_ADDR - ((QSPI_BLOCK_SIZE_64K * 11) % sizeof(DATASET)) + sizeof(DATASET))):          
   case ((BLOCK12_ADDR - ((QSPI_BLOCK_SIZE_64K * 12) % sizeof(DATASET)) + sizeof(DATASET))):          
   case ((BLOCK13_ADDR - ((QSPI_BLOCK_SIZE_64K * 13) % sizeof(DATASET)) + sizeof(DATASET))):          
   case ((BLOCK14_ADDR - ((QSPI_BLOCK_SIZE_64K * 14) % sizeof(DATASET)) + sizeof(DATASET))):          

       /* Check if buffer head position is ahead or behind
        the tail position. If head position is greate than 
        tail erase the previos sector */
       if(buffer->head > buffer->tail)
       {
         err_code = Flash_Erase(QSPI_ERASE_LEN_64KB,sector_addr - sizeof(DATASET));

         if(err_code == QSPI_OK)
         {
           printf("FCB : Erased Sector Address: %lu\n",sector_addr- sizeof(DATASET));
           HAL_Delay(1);
           err_code = FCB_OK;
         }
         else
         {
           err_code = FCB_ERASE_ERROR;
         }
       }
       else
       {
         /* Check whether the current buffer header position sector and
          previous buffer tail posoition sector macthes or not. If it odesn't macth 
          erase the sector */
         if((int)(buffer->head/QSPI_BLOCK_SIZE_64K) != (int)((buffer->tail - sizeof(DATASET))/QSPI_BLOCK_SIZE_64K))
         {            
           err_code = Flash_Erase(QSPI_ERASE_LEN_64KB,sector_addr - sizeof(DATASET));

           if(err_code == QSPI_OK)
           {
             printf("FCB : Erased Sector Address: %lu\n",sector_addr- sizeof(DATASET));
             HAL_Delay(1);
             err_code = FCB_OK;
           }
           else
           {
             err_code = FCB_ERASE_ERROR;
           }
         }
         else
         {
           printf("FCB: Header sector and Tail sector matches.\r\nCant erase memory\n");
           err_code = FCB_ADDR_ON_SAME_SECTOR;
         }
       }
     
      break;
     
      /* Event generated when tail rollsover the buffer */
     case FLASH_BUFFER_START_ADDR : 
       /* Check if the buffer header position is not overlapping 
       the last sector in the flash buffer */
       if((int)(buffer->head/QSPI_BLOCK_SIZE_64K) != ((FLASH_BUFFER_END_ADDR - sizeof(DATASET))/QSPI_BLOCK_SIZE_64K))
       {
         err_code = Flash_Erase(QSPI_ERASE_LEN_64KB,sector_addr - sizeof(DATASET));

         if(err_code == QSPI_OK)
         {
           printf("FCB : Erased Sector Address: %lu\n",sector_addr- sizeof(DATASET));
           HAL_Delay(1);
           err_code = FCB_OK;
         }  
       }  
      break;

 }
 

 return  err_code;

}
#else

fcb_status EraseFlashSector(flash_circular_buffer* buffer,uint32_t sector_addr)
{
  uint32_t err_code = FCB_OK;


 /* Erase the previosuly read sector as soon as the current flash buffer tail
  position points to adddress on the next */
 switch(buffer->tail)
 {
   case ((BLOCK1_ADDR - ((QSPI_BLOCK_SIZE_64K * 1) % sizeof(my_info)) + sizeof(my_info))):
   case ((BLOCK2_ADDR - ((QSPI_BLOCK_SIZE_64K * 2) % sizeof(my_info)) + sizeof(my_info))):
   case ((BLOCK3_ADDR - ((QSPI_BLOCK_SIZE_64K * 3) % sizeof(my_info)) + sizeof(my_info))):
   case ((BLOCK4_ADDR - ((QSPI_BLOCK_SIZE_64K * 4) % sizeof(my_info)) + sizeof(my_info))):
   case ((BLOCK5_ADDR - ((QSPI_BLOCK_SIZE_64K * 5) % sizeof(my_info)) + sizeof(my_info))):
   case ((BLOCK6_ADDR - ((QSPI_BLOCK_SIZE_64K * 6) % sizeof(my_info)) + sizeof(my_info))):
   case ((BLOCK7_ADDR - ((QSPI_BLOCK_SIZE_64K * 7) % sizeof(my_info)) + sizeof(my_info))):

   case ((BLOCK8_ADDR - ((QSPI_BLOCK_SIZE_64K * 8) % sizeof(my_info)) + sizeof(my_info))):
   case ((BLOCK9_ADDR - ((QSPI_BLOCK_SIZE_64K * 9) % sizeof(my_info)) + sizeof(my_info))):
   case ((BLOCK10_ADDR - ((QSPI_BLOCK_SIZE_64K * 10) % sizeof(my_info)) + sizeof(my_info))):
   case ((BLOCK11_ADDR - ((QSPI_BLOCK_SIZE_64K * 11) % sizeof(my_info)) + sizeof(my_info))):
   case ((BLOCK12_ADDR - ((QSPI_BLOCK_SIZE_64K * 12) % sizeof(my_info)) + sizeof(my_info))):
   case ((BLOCK13_ADDR - ((QSPI_BLOCK_SIZE_64K * 13) % sizeof(my_info)) + sizeof(my_info))):
   case ((BLOCK14_ADDR - ((QSPI_BLOCK_SIZE_64K * 14) % sizeof(my_info)) + sizeof(my_info))):

       /* Check if buffer head position is ahead or behind
        the tail position. If head position is greate than
        tail erase the previos sector */
       if(buffer->head > buffer->tail)
       {
         err_code = Flash_Erase(QSPI_ERASE_LEN_64KB,sector_addr - sizeof(my_info));

         if(err_code == QSPI_OK)
         {
           printf("FCB : Erased Sector Address: %lu\n",sector_addr- sizeof(my_info));
           HAL_Delay(1);
           err_code = FCB_OK;
         }
         else
         {
           err_code = FCB_ERASE_ERROR;
         }
       }
       else
       {
         /* Check whether the current buffer header position sector and
          previous buffer tail posoition sector macthes or not. If it odesn't macth
          erase the sector */
         if((int)(buffer->head/QSPI_BLOCK_SIZE_64K) != (int)((buffer->tail - sizeof(my_info))/QSPI_BLOCK_SIZE_64K))
         {
           err_code = Flash_Erase(QSPI_ERASE_LEN_64KB,sector_addr - sizeof(my_info));

           if(err_code == QSPI_OK)
           {
             printf("FCB : Erased Sector Address: %lu\n",sector_addr- sizeof(my_info));
             HAL_Delay(1);
             err_code = FCB_OK;
           }
           else
           {
             err_code = FCB_ERASE_ERROR;
           }
         }
         else
         {
           printf("FCB: Header sector and Tail sector matches.\r\nCant erase memory\n");
           err_code = FCB_ADDR_ON_SAME_SECTOR;
         }
       }

      break;

      /* Event generated when tail rollsover the buffer */
     case FLASH_BUFFER_START_ADDR :
       /* Check if the buffer header position is not overlapping
       the last sector in the flash buffer */
       if((int)(buffer->head/QSPI_BLOCK_SIZE_64K) != ((FLASH_BUFFER_END_ADDR - sizeof(my_info))/QSPI_BLOCK_SIZE_64K))
       {
         err_code = Flash_Erase(QSPI_ERASE_LEN_64KB,sector_addr - sizeof(my_info));

         if(err_code == QSPI_OK)
         {
           printf("FCB : Erased Sector Address: %lu\n",sector_addr- sizeof(my_info));
           HAL_Delay(1);
           err_code = FCB_OK;
         }
       }
      break;

 }

 return  err_code;
}
#endif



/***************** (C) COPYRIGHT DotCom IoT *****  END OF FILE *************************/
