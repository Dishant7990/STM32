/**
******************************************************************************
* @file    FlashCircularBuffer.h
* @author  DNK-034
* @date    28-Dec-2022
* @brief   Header file for storing data in circular buffer in QSPI Flash
******************************************************************************
*/

#ifndef DATAFLASH_H
#define	DATAFLASH_H

#ifdef	__cplusplus
extern "C" {
#endif


#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


/* QSPI Memory Orientation in Bytes*/
#define QSPI_PAGE_SIZE       256
#define QSPI_SECTOR_SIZE     4096
#define QSPI_BLOCK_SIZE_32K  32768
#define QSPI_BLOCK_SIZE_64K  65536

/* QSPI Memory blocks in numbers */
#define QSPI_TOTAL_SECTORS     2048
#define QSPI_TOTAL_BLOCKS_32K  256
#define QSPI_TOTAL_BLOCKS_64K  128 

/* External Memory Start and End Addr reserved for Storing sensor data */
#define FLASH_CIRCULAR_SECTORS_CNT  2
#define FLASH_CIRCULAR_BUFFER_SIZE (QSPI_BLOCK_SIZE_64K * FLASH_CIRCULAR_SECTORS_CNT)
#define FLASH_MEM_START_ADDR       BLOCK0_ADDR
#define FLASH_MEM_END_ADDR         (FLASH_MEM_START_ADDR + FLASH_CIRCULAR_BUFFER_SIZE) 

/* Circular Buffer Start and End Address based 
on the reserved sensor data memory */
#if(MP34DT05_ENABLE == 0)
#define FLASH_BUFFER_LEFTOVER_ADDR (FLASH_MEM_END_ADDR % sizeof(DATASET))
#else
#define FLASH_BUFFER_LEFTOVER_ADDR (FLASH_MEM_END_ADDR % 32000)
#endif 

#define FLASH_BUFFER_SIZE (FLASH_MEM_END_ADDR - FLASH_BUFFER_LEFTOVER_ADDR)
#define FLASH_BUFFER_START_ADDR FLASH_MEM_START_ADDR
#define FLASH_BUFFER_END_ADDR FLASH_BUFFER_SIZE

/* QSPi FLASH Buffer Operation Status */
typedef enum
{
  FCB_OK,
  FCB_WRITE_ERROR,
  FCB_READ_ERROR,
  FCB_ERASE_ERROR,
  FCB_NO_EMPTY_LOCATIONS,
  FCB_ADDR_ON_SAME_SECTOR,
  FCB_NO_DATA_AVAILABLE,  
}fcb_status;

typedef struct
{
uint32_t water_meter_version;
uint32_t flow_total_ml;
uint32_t run_time_hours;
//uint8_t buff[1000];
}DATASET;

/*Ring Buffer Structure*/
typedef struct
{
  DATASET* tx_data;
  DATASET* rx_data;
  volatile unsigned int head;
  volatile unsigned int tail;
  volatile bool data_available;
  volatile bool memory_available;
}flash_circular_buffer;


/* External flash Memory Organization */
typedef enum{
  BLOCK0_ADDR  = 0x000000,
  BLOCK1_ADDR  = 0x010000,
  BLOCK2_ADDR  = 0x020000,
  BLOCK3_ADDR  = 0x030000,
  BLOCK4_ADDR  = 0x040000,
  BLOCK5_ADDR  = 0x050000,    
  BLOCK6_ADDR  = 0x060000,
  BLOCK7_ADDR  = 0x070000,
  BLOCK8_ADDR  = 0x080000,
  BLOCK9_ADDR  = 0x090000,
  BLOCK10_ADDR = 0x0A0000,
  BLOCK11_ADDR = 0x0B0000,
  BLOCK12_ADDR = 0x0C0000,    
  BLOCK13_ADDR = 0x0D0000,
  BLOCK14_ADDR = 0x0E0000,
  BLOCK15_ADDR = 0x0F0000,      
}flash_block_addr_t;


/* Function Declaration */
void FlashCircularBufferInit(flash_circular_buffer* buffer);
fcb_status WriteDatasetToFlash(flash_circular_buffer* buffer,void* dataToBuffe, uint16_t length);
fcb_status ReadDatasetFromFlash(flash_circular_buffer* buffer,void* rcvBuffer, uint32_t length);
fcb_status EraseFlashSector(flash_circular_buffer* buffer,uint32_t sector_addr);


extern flash_circular_buffer fcb;
extern volatile bool m_finished;

#ifdef	__cplusplus
}
#endif


#endif	/* DATAFLASH_H */
