/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "usb_device.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "usbd_hid.h"
#include "stdio.h"
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

/* USER CODE BEGIN PV */
extern USBD_HID_HandleTypeDef hUsbDeviceFS;

typedef struct {
	uint8_t MODIFIER;
	uint8_t RESERVED;
	uint8_t KEYCODE1;
	uint8_t KEYCODE2;
	uint8_t KEYCODE3;
	uint8_t KEYCODE4;
	uint8_t KEYCODE5;
	uint8_t KEYCODE6;

}keyboardReportDes;

keyboardReportDes HIDkeyBoard = {0,0,0,0,0,0,0,0};

char msg_buff[100];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
//void KeyBoardPrint(char *data, uint16_t length) {
//
//	for (uint16_t count = 0; count < length; count++)
//	{
//		if (data[count] >= 0x41 && data[count] <= 0x5A)
//		{
//			HIDkeyBoard.MODIFIER = 0x02;  // Print char in Capital
//			HIDkeyBoard.KEYCODE1 = data[count] - 0x3D;
//			USBD_HID_SendReport(&hUsbDeviceFS, &HIDkeyBoard, sizeof(HIDkeyBoard));
//
//			HAL_Delay(15);
//			HIDkeyBoard.MODIFIER = 0x00;
//			HIDkeyBoard.KEYCODE1 = 0x00;
//			USBD_HID_SendReport(&hUsbDeviceFS, &HIDkeyBoard, sizeof(HIDkeyBoard));
//
//		}
//		else if (data[count] >= 0x61 && data[count] <= 0x7A)
//		{
//			HIDkeyBoard.KEYCODE1 = data[count] - 0x5D;
//			USBD_HID_SendReport(&hUsbDeviceFS, &HIDkeyBoard, sizeof(HIDkeyBoard));
//
//			HAL_Delay(15);
//			HIDkeyBoard.KEYCODE1 = 0x00;
//			USBD_HID_SendReport(&hUsbDeviceFS, &HIDkeyBoard, sizeof(HIDkeyBoard));
//
//		}
//
//		else if (data[count] == 0x20)
//		{
//			HIDkeyBoard.KEYCODE1 = 0x2C;
//			USBD_HID_SendReport(&hUsbDeviceFS, &HIDkeyBoard, sizeof(HIDkeyBoard));
//
//			HAL_Delay(15);
//			HIDkeyBoard.KEYCODE1 = 0x00;
//			USBD_HID_SendReport(&hUsbDeviceFS, &HIDkeyBoard, sizeof(HIDkeyBoard));
//
//		}
//
//		else if (data[count] == 0x0A)
//		{
//			HIDkeyBoard.KEYCODE1 = 0x28;
//			USBD_HID_SendReport(&hUsbDeviceFS, &HIDkeyBoard, sizeof(HIDkeyBoard));
//
//			HAL_Delay(15);
//			HIDkeyBoard.KEYCODE1 = 0x00;
//			USBD_HID_SendReport(&hUsbDeviceFS, &HIDkeyBoard, sizeof(HIDkeyBoard));
//
//		}
//		HAL_Delay(25);
//	}
//}
void KeyBoardPrint(char *data, uint16_t length) {
    for (uint16_t count = 0; count < length; count++) {
        if (data[count] >= 0x41 && data[count] <= 0x5A) { // Uppercase A-Z
            HIDkeyBoard.MODIFIER = 0x06;  // Left Shift
            HIDkeyBoard.KEYCODE1 = data[count] - 0x3D;
        } else if (data[count] >= 0x61 && data[count] <= 0x7A) { // Lowercase a-z
            HIDkeyBoard.KEYCODE1 = data[count] - 0x5D;
        } else if (data[count] == 0x20) { // Space
            HIDkeyBoard.KEYCODE1 = 0x2C;
        } else if (data[count] == 0x0A) { // New line
            HIDkeyBoard.KEYCODE1 = 0x28;
        } else {
            HIDkeyBoard.KEYCODE1 = 0x00;
        }

        USBD_HID_SendReport(&hUsbDeviceFS, &HIDkeyBoard, sizeof(HIDkeyBoard));
        HAL_Delay(15);

        HIDkeyBoard.MODIFIER = 0x00;
        HIDkeyBoard.KEYCODE1 = 0x00;
        USBD_HID_SendReport(&hUsbDeviceFS, &HIDkeyBoard, sizeof(HIDkeyBoard));
        HAL_Delay(25);
    }
}
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
  MX_USB_DEVICE_Init();
  /* USER CODE BEGIN 2 */
  sprintf(msg_buff, "hello, i am dishantpari\r\n ");
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	/*
	 * This a basic ABC printing in every 1 sec
	HIDkeyBoard.MODIFIER = 0x02;  // Print char in Capital
	HIDkeyBoard.KEYCODE1 = 0x04;  // Print 'A'
	HIDkeyBoard.KEYCODE2 = 0x05;  // Print 'B'
	HIDkeyBoard.KEYCODE3 = 0x06;  // Print 'C'
	USBD_HID_SendReport(&hUsbDeviceFS, &HIDkeyBoard, sizeof(HIDkeyBoard));
	HAL_Delay(50);

	HIDkeyBoard.MODIFIER = 0x00;  // Clear input
	HIDkeyBoard.KEYCODE1 = 0x00;  // Clear input
	HIDkeyBoard.KEYCODE2 = 0x00;  // Clear input
	HIDkeyBoard.KEYCODE3 = 0x00;  // Clear input
	USBD_HID_SendReport(&hUsbDeviceFS, &HIDkeyBoard, sizeof(HIDkeyBoard));
	HAL_Delay(1000);
	*/

	  /** Now we set our name and print it every 2 sec**/
	  /*
		 HIDkeyBoard.MODIFIER = 0x02;  // Print char in Capital
	HIDkeyBoard.KEYCODE1 = 0x07;  // Print 'D'
	HIDkeyBoard.KEYCODE2 = 0x0C;  // Print 'I'
	HIDkeyBoard.KEYCODE3 = 0x16;  // Print 'S'
	HIDkeyBoard.KEYCODE4 = 0x0B;  // Print 'H'
	HIDkeyBoard.KEYCODE5 = 0x04;  // Print 'A'
	HIDkeyBoard.KEYCODE6 = 0x11;  // Print 'N'
	USBD_HID_SendReport(&hUsbDeviceFS, &HIDkeyBoard, sizeof(HIDkeyBoard));
	HAL_Delay(100);

//	HIDkeyBoard.MODIFIER = 0x00;  // Clear input
	HIDkeyBoard.KEYCODE1 = 0x00;  // Clear input
	HIDkeyBoard.KEYCODE2 = 0x00;  // Clear input
	HIDkeyBoard.KEYCODE3 = 0x00;  // Clear input
	HIDkeyBoard.KEYCODE4 = 0x00;  // Clear input
	HIDkeyBoard.KEYCODE5 = 0x00;  // Clear input
	HIDkeyBoard.KEYCODE6 = 0x00;  // Clear input
	USBD_HID_SendReport(&hUsbDeviceFS, &HIDkeyBoard, sizeof(HIDkeyBoard));
	HAL_Delay(100);

//	HIDkeyBoard.MODIFIER = 0x02;  // Print char in Capital
	HIDkeyBoard.KEYCODE1 = 0x17;  // Print 'T'
	HIDkeyBoard.KEYCODE2 = 0x13;  // Print 'P'
	HIDkeyBoard.KEYCODE3 = 0x04;  // Print 'A'
	HIDkeyBoard.KEYCODE4 = 0x15;  // Print 'R'
	HIDkeyBoard.KEYCODE5 = 0x0C;  // Print 'I'
	HIDkeyBoard.KEYCODE6 = 0x58;  // 'ENTER'
	USBD_HID_SendReport(&hUsbDeviceFS, &HIDkeyBoard, sizeof(HIDkeyBoard));
	HAL_Delay(100);

	HIDkeyBoard.MODIFIER = 0x00;  // Clear input
	HIDkeyBoard.KEYCODE1 = 0x00;  // Clear input
	HIDkeyBoard.KEYCODE2 = 0x00;  // Clear input
	HIDkeyBoard.KEYCODE3 = 0x00;  // Clear input
	HIDkeyBoard.KEYCODE4 = 0x00;  // Clear input
	HIDkeyBoard.KEYCODE5 = 0x00;  // Clear input
	HIDkeyBoard.KEYCODE6 = 0x00;  // Clear input
	USBD_HID_SendReport(&hUsbDeviceFS, &HIDkeyBoard, sizeof(HIDkeyBoard));

	HAL_Delay(1000);
	*/

	KeyBoardPrint(msg_buff, strlen(msg_buff));
	HAL_Delay(100);
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_HSI48;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLLMUL_4;
  RCC_OscInitStruct.PLL.PLLDIV = RCC_PLLDIV_2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_HSI48;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
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