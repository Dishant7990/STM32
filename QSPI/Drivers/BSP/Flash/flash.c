/*
 ******************************************************************************
 * @file    flash.c
 * @author  DNK-043
 * @date    28-Dec-2022
 * @brief   This file provides a set of functions needed to interface the
  *         external flash
 *******************************************************************************
*/


/* Includes ------------------------------------------------------------------*/

#include "flash.h"
#include "stddef.h"
#include "main.h"
#include "stdbool.h"
#include "MX25L_QSPI_Flash.h"


/* Macros Defintions ---------------------------------------------------------*/


/* QSPI Flash Variables ---------------------------------------------------------*/




/* Function Definitions ---------------------------------------------------------*/

/*
 * @brief  Function to initialize External Flash Memory
 * @param  None      
 * @retval BSP status
*/
uint32_t Flash_Init(void)
{
    int32_t err_code = QSPI_OK;

    err_code = BSP_QSPI_Init();
    if(err_code != QSPI_OK)
    {
      printf("QSPI Flash Initialization failed\r\n");
    }

    return err_code;
}


/*
 * @brief  Function to De-Initilaize External Flash Memory
 * @param  None      
 * @retval BSP status
*/
uint32_t Flash_DeInit(void)
{
  int32_t err_code = QSPI_OK;

  BSP_QSPI_DeInit();

  return err_code;
}


/*
 * @brief  Function to erase blocks of External Flash Memory
* @param  len          Len. of Blocks: QSPI_ERASE_LEN_4KB,
                                       QSPI_ERASE_LEN_64KB,
                                       QSPI_ERASE_LEN_ALL
 * @param  start_address  Start Address to Erase data
 * @retval BSP status
*/
uint32_t Flash_Erase(qspi_erase_len len,uint32_t start_address)
{
    int32_t err_code = QSPI_OK;

    switch (len)
    {
    /* Sector Erase */
    case 1 :
    	err_code = BSP_QSPI_Erase_Sector(start_address);
    	if(err_code != QSPI_OK)
    	{
    		printf("Sector : Erase failed\r\n");
    	}
    	break;

    /* Block Erase (64KB) */
    case 2:
    	err_code = BSP_QSPI_Erase_Block(start_address);
    	if(err_code != QSPI_OK)
    	{
    		printf("Block : Erase failed\r\n");
    	}
    	break;

    /* Chip Erase */
    case 3 :
    	err_code = BSP_QSPI_Erase_Chip();
    	if(err_code != QSPI_OK)
    	{
    		printf("FLASH : Erase failed\r\n");
    	}
    	break;

    default:
    	break;
    }

    return err_code;
}


/*
 * @brief  Function to write data to External Flash Memory
 * @param  p_tx_buffer        pointer to the data to be written 
 * @param  tx_buffer_length   length of data to be written
 * @param  dst_address        Destination address to write data
 * @retval BSP status
*/
uint32_t Flash_Write(void * p_tx_buffer,size_t tx_buffer_length,uint32_t dst_address)
{
    int32_t err_code = QSPI_OK;

    err_code = BSP_QSPI_Write(p_tx_buffer,dst_address,tx_buffer_length);
    if(err_code != QSPI_OK)
    {
       printf("FLASH : Flash write operation failed\r\n");
    }
    printf("FLASH : Flash write operation Done!!\r\n");
    return err_code;
}



/*
 * @brief  Function to Read data from External Flash Memory
 * @param  p_rx_buffer        pointer to buffer that store the read data
 * @param  rx_buffer_length   length of data to be read
 * @param  src_address        Source address to read data from 
 * @retval BSP status
*/
uint32_t Flash_Read(void * p_rx_buffer,size_t rx_buffer_length,uint32_t src_address)
{
    int32_t err_code = QSPI_OK;

    err_code = BSP_QSPI_Read(p_rx_buffer, src_address, rx_buffer_length);
    if(err_code != QSPI_OK)
    {
       printf("FLASH : Flash read operation failed\r\n");
    }
    printf("FLASH : Flash Read operation Done!!\r\n");
    return err_code;
}




/***************** (C) COPYRIGHT DotCom IoT *****  END OF FILE*************************/
