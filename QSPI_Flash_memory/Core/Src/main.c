/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "flash.h"
#include "string.h"
#include "stdio.h"
#include "MX25L_QSPI_Flash.h"
#include "FlashCircularBuffer.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef hlpuart1;

QSPI_HandleTypeDef hqspi;

/* USER CODE BEGIN PV */
uint8_t *temp_buff = 0;
char *writebuff = "hello !!";
uint8_t test_buff[256];
uint8_t readbuff[300];
uint8_t PAGE_[10];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_QUADSPI_Init(void);
static void MX_LPUART1_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */


  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_QUADSPI_Init();
  MX_LPUART1_UART_Init();
  /* USER CODE BEGIN 2 */

  /* Initialize the Flash */
  Flash_Init();
  /* Initialize the circular buffer */
  FlashCircularBufferInit(&fcb);

  /* Structure for the read buffer */
  DATASET readSens;

  /* Structure for the write buffer */
  DATASET sensor_data = { .flow_total_ml = 1,
		  	  	  	  	  .run_time_hours = 2,
						  .water_meter_version = 1
  };

  for(int indx = 0; indx < 256; indx++)
  {
	  test_buff[indx] = 'A';
  }

  /* Read Flash ID */
  BSP_QSPI_ReadID(temp_buff);
  HAL_Delay(1000);

  /* To erase whole chip un-comment the below section */
  Flash_Erase(QSPI_ERASE_LEN_ALL,0);
  waitForFlashbusy();

  /* Erase the blocks of chip*/
//  Flash_Erase(QSPI_ERASE_LEN_64KB,BLOCK0_ADDR);
//  Flash_Erase(QSPI_ERASE_LEN_64KB,BLOCK1_ADDR);
//  Flash_Erase(QSPI_ERASE_LEN_64KB,BLOCK2_ADDR);
//  Flash_Erase(QSPI_ERASE_LEN_64KB,BLOCK3_ADDR);
//  Flash_Erase(QSPI_ERASE_LEN_64KB,BLOCK4_ADDR);
//  Flash_Erase(QSPI_ERASE_LEN_64KB,BLOCK5_ADDR);
//  Flash_Erase(QSPI_ERASE_LEN_64KB,BLOCK6_ADDR);
//  Flash_Erase(QSPI_ERASE_LEN_64KB,BLOCK7_ADDR);

  /* Wait for the chip erase */
  waitForFlashbusy();

  /* Write data to the flash using the circular buffer /
   * Sector size = 4096 Bytes
   * Block size  = 65536 Bytes
   * Total blocks of 64KB = 16
   * 4096 x 16 =  65536
   * 65536 / 12 = 5461.333333333(12bytes at the time)
   * 5461.333333333 = 5500 */
  for(int index = 0; index < 5500; index++)
  {
	  WriteDatasetToFlash(&fcb, &sensor_data, sizeof(DATASET));
	  /* Wait till the write complete */
	  waitForFlashbusy();
	  HAL_Delay(1);

	  /* Increase the dummy structure data for testing purpose */
	  sensor_data.flow_total_ml += 1;
	  sensor_data.run_time_hours += 1;
  }

  /* Read data form the flash using circular buffer */
  for(int index = 0; index < 5500; index++)
  {
	  ReadDatasetFromFlash(&fcb, &readSens, sizeof(readSens));
	  waitForFlashbusy();
	  HAL_Delay(1);
  }

  /* Wait for some time to debug */
  HAL_Delay(3000);

  sensor_data.water_meter_version = 2;

  /* Check the data role over to the FCB */
  for(int i=0;i<5500;i++)
  {
	  WriteDatasetToFlash(&fcb, &sensor_data, sizeof(DATASET));
	  waitForFlashbusy();
	  HAL_Delay(1);
	  sensor_data.flow_total_ml += 1;
	  sensor_data.run_time_hours += 1;
  }

  for(int i=0;i<5500;i++)
  {
	  ReadDatasetFromFlash(&fcb, &readSens, sizeof(readSens));
	  waitForFlashbusy();
	  HAL_Delay(1);
  }

  /* Debug time */
  HAL_Delay(3000);

  /* Simple read/write to the flash */
  Flash_Write(test_buff, sizeof(test_buff)/sizeof(test_buff[0]), PAGE_0);
  HAL_Delay(1000);
  waitForFlashbusy();
  Flash_Read(readbuff, 300, PAGE_0);
  HAL_Delay(1000);
  waitForFlashbusy();


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief LPUART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_LPUART1_UART_Init(void)
{

  /* USER CODE BEGIN LPUART1_Init 0 */

  /* USER CODE END LPUART1_Init 0 */

  /* USER CODE BEGIN LPUART1_Init 1 */

  /* USER CODE END LPUART1_Init 1 */
  hlpuart1.Instance = LPUART1;
  hlpuart1.Init.BaudRate = 115200;
  hlpuart1.Init.WordLength = UART_WORDLENGTH_8B;
  hlpuart1.Init.StopBits = UART_STOPBITS_1;
  hlpuart1.Init.Parity = UART_PARITY_NONE;
  hlpuart1.Init.Mode = UART_MODE_TX_RX;
  hlpuart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  hlpuart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  hlpuart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&hlpuart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN LPUART1_Init 2 */

  /* USER CODE END LPUART1_Init 2 */

}

/**
  * @brief QUADSPI Initialization Function
  * @param None
  * @retval None
  */
static void MX_QUADSPI_Init(void)
{

  /* USER CODE BEGIN QUADSPI_Init 0 */

  /* USER CODE END QUADSPI_Init 0 */

  /* USER CODE BEGIN QUADSPI_Init 1 */

  /* USER CODE END QUADSPI_Init 1 */
  /* QUADSPI parameter configuration*/
  hqspi.Instance = QUADSPI;
  hqspi.Init.ClockPrescaler = 0;
  hqspi.Init.FifoThreshold = 4;
  hqspi.Init.SampleShifting = QSPI_SAMPLE_SHIFTING_NONE;
  hqspi.Init.FlashSize = 21;
  hqspi.Init.ChipSelectHighTime = QSPI_CS_HIGH_TIME_1_CYCLE;
  hqspi.Init.ClockMode = QSPI_CLOCK_MODE_0;
  hqspi.Init.FlashID = QSPI_FLASH_ID_1;
  hqspi.Init.DualFlash = QSPI_DUALFLASH_DISABLE;
  if (HAL_QSPI_Init(&hqspi) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN QUADSPI_Init 2 */

  /* USER CODE END QUADSPI_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  HAL_PWREx_EnableVddIO2();

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
