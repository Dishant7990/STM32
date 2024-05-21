/*
 ******************************************************************************
 * @file    MX25L_QSPI.c
 * @author  DNK-043
 * @date    28-Dec-2022
 *******************************************************************************
*/

#ifndef MX25L_QSPI_FLASH_H_
#define MX25L_QSPI_FLASH_H_

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "MX25L512.h"
#include "stdio.h"

/** @addtogroup STM32L496ZGP_NUCLEO_QSPI
  * @{
  */


/* Exported constants --------------------------------------------------------*/
/** @defgroup STM32L486ZGP_NUCLEO_QSPI_Exported_Constants STM32F769I_DISCOVERY_QSPI Exported Constants
  * @{
  */
/* QSPI Error codes */
#define QSPI_OK            ((uint8_t)0x00)
#define QSPI_ERROR         ((uint8_t)0x01)
#define QSPI_BUSY          ((uint8_t)0x02)
#define QSPI_NOT_SUPPORTED ((uint8_t)0x04)
#define QSPI_SUSPENDED     ((uint8_t)0x08)

#define QSPI_FLASH_BUSY	1
#define QSPI_FLASH_FREE	0

#define FLASH_STATUSE_TIMEOUT  200000 //120


/* Definition for QSPI clock resources */
#define QSPI_CLK_ENABLE()          __HAL_RCC_QSPI_CLK_ENABLE()
#define QSPI_CLK_DISABLE()         __HAL_RCC_QSPI_CLK_DISABLE()
#define QSPI_CS_GPIO_CLK_ENABLE()  __HAL_RCC_GPIOB_CLK_ENABLE()
#define QSPI_CLK_GPIO_CLK_ENABLE() __HAL_RCC_GPIOB_CLK_ENABLE()
#define QSPI_D0_GPIO_CLK_ENABLE()  __HAL_RCC_GPIOB_CLK_ENABLE()
#define QSPI_D1_GPIO_CLK_ENABLE()  __HAL_RCC_GPIOB_CLK_ENABLE()
#define QSPI_D2_GPIO_CLK_ENABLE()  __HAL_RCC_GPIOA_CLK_ENABLE()
#define QSPI_D3_GPIO_CLK_ENABLE()  __HAL_RCC_GPIOA_CLK_ENABLE()

#define QSPI_FORCE_RESET()         __HAL_RCC_QSPI_FORCE_RESET()
#define QSPI_RELEASE_RESET()       __HAL_RCC_QSPI_RELEASE_RESET()

/* Definition for QSPI Pins */
/* QSPI_CS */
#define QSPI_CS_PIN                GPIO_PIN_11
#define QSPI_CS_GPIO_PORT          GPIOB
#define QSPI_CS_PIN_AF             GPIO_AF10_QUADSPI
/* QSPI_CLK */
#define QSPI_CLK_PIN               GPIO_PIN_10
#define QSPI_CLK_GPIO_PORT         GPIOB
#define QSPI_CLK_PIN_AF            GPIO_AF10_QUADSPI
/* QSPI_D0 */
#define QSPI_D0_PIN                GPIO_PIN_1
#define QSPI_D0_GPIO_PORT          GPIOB
#define QSPI_D0_PIN_AF             GPIO_AF10_QUADSPI
/* QSPI_D1 */
#define QSPI_D1_PIN                GPIO_PIN_0
#define QSPI_D1_GPIO_PORT          GPIOB
#define QSPI_D1_PIN_AF             GPIO_AF10_QUADSPI
/* QSPI_D2 */
#define QSPI_D2_PIN                GPIO_PIN_7
#define QSPI_D2_GPIO_PORT          GPIOA
#define QSPI_D2_PIN_AF             GPIO_AF10_QUADSPI
/* QSPI_D3 */
#define QSPI_D3_PIN                GPIO_PIN_6
#define QSPI_D3_GPIO_PORT          GPIOA
#define QSPI_D3_PIN_AF             GPIO_AF10_QUADSPI




/**
  * @}
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup STM32L496ZGP_NUCLEO_QSPI_Exported_Types STM32L496ZGP_NUCLEO_QSPI Exported Types
  * @{
  */
/* QSPI Info */
typedef struct {
  uint32_t FlashSize;          /*!< Size of the flash */
  uint32_t EraseSectorSize;    /*!< Size of sectors for the erase operation */
  uint32_t EraseSectorsNumber; /*!< Number of sectors for the erase operation */
  uint32_t ProgPageSize;       /*!< Size of pages for the program operation */
  uint32_t ProgPagesNumber;    /*!< Number of pages for the program operation */
} QSPI_Info;

/**
  * @}
  */

typedef enum{
	PAGE_0   =  0x000,
	PAGE_1	 =	0x100,
	PAGE_2	 =	0x200,
	PAGE_3	 =	0x300,
	PAGE_4	 =	0x400,
	PAGE_5	 =	0x500,
	PAGE_6	 =	0x600,
	PAGE_7	 =	0x700,
	PAGE_8	 =	0x800,
	PAGE_9	 =	0x900
}flash_page_address_t;


/* Exported functions --------------------------------------------------------*/
/** @addtogroup STM32L496ZGP_NUCLEO_QSPI_Exported_Functions
  * @{
  */
uint8_t BSP_QSPI_Init       (void);
uint8_t BSP_QSPI_DeInit     (void);
uint8_t BSP_QSPI_Read       (uint8_t* pData, uint32_t ReadAddr, uint32_t Size);
uint8_t BSP_QSPI_Write      (uint8_t* pData, uint32_t WriteAddr, uint32_t Size);
uint8_t BSP_QSPI_Erase_Sector(uint32_t SectorAddress);
uint8_t BSP_QSPI_Erase_Block(uint32_t BlockAddress);
uint8_t BSP_QSPI_Erase_Chip (void);
uint8_t BSP_QSPI_GetStatus  (void);
uint8_t BSP_QSPI_GetInfo    (QSPI_Info* pInfo);
uint8_t BSP_QSPI_EnableMemoryMappedMode(void);
uint8_t BSP_QSPI_ReadID(uint8_t *pData);

/* These functions can be modified in case the current settings
   need to be changed for specific application needs */
//void BSP_QSPI_MspInit(QSPI_HandleTypeDef *hqspi, void *Params);
//void BSP_QSPI_MspDeInit(QSPI_HandleTypeDef *hqspi, void *Params);


/**
  * @brief  this function chack the BUSY flash of flash.
  * @retval None
  */
extern uint8_t waitForFlashbusy(void);


/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

#endif /* MX25L_QSPI_FLASH_H_ */
