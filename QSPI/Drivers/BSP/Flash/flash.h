/*
 ******************************************************************************
 * @file    flash.h
 * @author  DNK-043
 * @date    28-Dec-2022
 * @brief   This file contains all the functions prototypes for interfacing 
            external QSPI based Flash memory. 
 *******************************************************************************
*/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef QSPI_H
#define QSPI_H

#ifdef __cplusplus
 extern "C" {
#endif



/* Includes ------------------------------------------------------------------*/

#include "main.h"
#include "stddef.h"
#include "math.h"
#include "stdbool.h"


/** @defgroup ExternalFlash_Exported_Constants 
 * @{
 */

/* Macros Defintions ---------------------------------------------------------*/
#define FLASH_OK             0
#define FLASH_ERROR         -1

#define QSPI_STD_CMD_WRSR   0x01
#define QSPI_STD_CMD_RSTEN  0x66
#define QSPI_STD_CMD_RST    0x99

/* Flash Variables --------------------------------------------------------- */
/* Flash Trigger Status */
typedef enum
{
  disable,
  enable
}flash_status_t;


/** @brief Erasing data length. */
typedef enum
{
    QSPI_ERASE_LEN_4KB  = 1,   /**< Erase 4 kB block. */
    QSPI_ERASE_LEN_64KB = 2, /**< Erase 64 kB block . */
    QSPI_ERASE_LEN_ALL  = 3  /**< Erase all. */
} qspi_erase_len;




/** @addtogroup ExternalFlash_Exported_Functions 
 * @{
 */
uint32_t Configure_Flash_Memory(void);
uint32_t Flash_Init(void);
uint32_t Flash_DeInit(void);
uint32_t Flash_Erase(qspi_erase_len len,uint32_t start_address);
uint32_t Flash_Write(void * p_tx_buffer,size_t tx_buffer_length,uint32_t dst_address);
uint32_t Flash_Read(void * p_rx_buffer,size_t rx_buffer_length,uint32_t src_address);
void Trigger_Flash_State(bool status);



/** @addtogroup ExternalFlash_Exported_Variables 
 * @{
 */



#ifdef __cplusplus
}
#endif

#endif /*QSPI_H*/




/***************** (C) COPYRIGHT DotCom IoT *****END OF FILE*************************/
