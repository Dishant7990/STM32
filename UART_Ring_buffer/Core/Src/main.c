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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "UartRingbuffer.h"
#include <string.h>
#include <stdio.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
#define MY_MENU "\r\n1 = Write data\r\n " \
	            "2 = Read data\r\n"
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef hlpuart1;

/* USER CODE BEGIN PV */
//char UserData_Buff[100];
//char Rx_data[100];
//static int idx;

char buffer[100];
int cmd;

char name[20];
char age[3];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_LPUART1_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
//void writedata(void) {
//	memset(name, 0, 20);
//	memset(buffer, 0, 100);
//	printf("\r\nPlease Enter your name:\r\n");
//	HAL_Delay(10000);
//	while(1){
//	do {
//		if (IsDataAvailable()) {
//			static int idx = 0;
//			buffer[idx] = Uart_read();
//			idx++;
//			HAL_Delay(1000);
//		}
//	} while (IsDataAvailable());
//	memset(name, 0, 20);
//	strcpy(name, buffer);
//	//name[sizeof(name) - 1] = '\0';
//	printf("\n%s %s\n", name, name);
//	memset(buffer, 0, 100);
//
//
//
//	printf("\r\nPlease Enter your Age:\r\n");
//	memset(age, 0, 3);
//	HAL_Delay(10000);
//	do {
//		if (IsDataAvailable()) {
//			static int idx = 0;
//			buffer[idx] = Uart_read();
//			idx++;
//			HAL_Delay(1000);
//		}
//	} while (IsDataAvailable());
//	memset(age, 0, 3);
//	strncpy(age, buffer, sizeof(age) - 1);
//	age[sizeof(age) - 1] = '\0';
////	age = buffer[0];
//	memset(buffer, 0, 100);
//	break;
//	}
//}

void writedata(void) {
    memset(name, 0, sizeof(name));
    memset(age, 0, sizeof(age));

    printf("\r\nPlease Enter your name:\r\n");

    fflush(stdout); // Ensure any buffered output is flushed
    HAL_Delay(10000); // Add a delay to ensure stability

    // Read user input for name
    int idx = 0;
    do {
        if (IsDataAvailable()) {
            char c = Uart_read();
            printf("%c", c); // Echo back character to console
            fflush(stdout); // Ensure character is displayed immediately
            if (c == '\n') {
                break; // Exit loop when Enter is pressed
            }
            name[idx++] = c;
            HAL_Delay(10); // Small delay for stability
        }
    } while (IsDataAvailable());
    name[idx] = '\0'; // Ensure null termination

    printf("\r\nPlease Enter your Age:\r\n");
    fflush(stdout);
    HAL_Delay(10000);

    // Read user input for age
    idx = 0;
    do {
        if (IsDataAvailable()) {
            char c = Uart_read();
            printf("%c", c); // Echo back character to console
            fflush(stdout); // Ensure character is displayed immediately
            if (c == '\n') {
                break; // Exit loop when Enter is pressed
            }
            age[idx++] = c;
            HAL_Delay(10); // Small delay for stability
        }
    } while (IsDataAvailable());
    age[idx] = '\0'; // Ensure null termination

    printf("\r\nData written successfully!\r\n");
}


void printData(void) {
	printf("\r\nName : %s\r\n", name);
	printf("\r\nAge : %s\r\n", age);
}

void printMenu(void){
	printf("\r\nMenu:\n%s", MY_MENU);
}
/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {

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
	MX_LPUART1_UART_Init();
	/* USER CODE BEGIN 2 */
	Ringbuf_init();

//  while(1){
//	  do{
//	  	  if(IsDataAvailable()){
//	  		  static int idx = 0;
//	  		  buffer[idx] = Uart_read();
//	  		  //printf("Read Data: %d\r\n", data);
//	  		  //Wait_for("\n");
//	  		  //Get_string(Rx_data);
//	  		  // = Uart_write(data);
//	  		  idx++;
//	  		  HAL_Delay(1000);
//
//	  		  //HAL_UART_Transmit(&hlpuart1, (uint8_t *)data, 1, 500);
//	  	  }
//	  	  }while(IsDataAvailable());
//	  break;
//  }
//  HAL_UART_Transmit(&hlpuart1,(uint8_t *)buffer, sizeof(buffer),1000);
//
//  HAL_Delay(1000);
	printf("\r\nMenu:\n%s", MY_MENU);

	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1) {
		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */

////	  HAL_UART_Receive(&hlpuart1,(uint8_t *) RX_data, sizeof(RX_data), 1000);
//////	  HAL_Delay(200);
////	  HAL_UART_Transmit(&hlpuart1,(uint8_t *)  RX_data, sizeof(RX_data), 1000);
//		do {
//			if (IsDataAvailable()) {
//				static int idx = 0;
//				buffer[idx] = Uart_read();
//				//printf("Read Data: %d\r\n", data);
//				//Wait_for("\n");
//				//Get_string(Rx_data);
//				// = Uart_write(data);
//				idx++;
//				HAL_Delay(100);
//
//				//HAL_UART_Transmit(&hlpuart1, (uint8_t *)data, 1, 500);
//			}
//		} while (IsDataAvailable());
////	  if (IsDataAvailable()) {
////	      int data = Uart_read();
////	      printf("Read Data: %d\r\n", data);
////	      HAL_Delay(1000);
////
////	      // Read user input as a string and store it in UserData_Buff
////	      memset(UserData_Buff, 0, sizeof(UserData_Buff)); // Initialize the buffer with null characters
////	      Get_string(UserData_Buff);
////
////	      // You can now use UserData_Buff for further processing or storage
////
////	      Uart_write(data);
////	  }
//		HAL_UART_Transmit(&hlpuart1, (uint8_t*) buffer, sizeof(buffer), 1000);
//		memset(buffer, 0, 100);
//		HAL_Delay(100);
		do{
		if (IsDataAvailable()) {
			cmd = Uart_read();
			switch (cmd) {
			case 'M':
				memset(buffer, 0, 100);
				printMenu();
				break;

			case '1':
				memset(buffer, 0, 100);
				writedata();
				break;

			case '2':
				memset(buffer, 0, 100);
				printData();
				break;
			default:
				printf("Invalid Input\r\n");
				break;
			}
		}
		}while(IsDataAvailable());
		HAL_Delay(1000);
	}
	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

	/** Configure the main internal regulator output voltage
	 */
	if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1)
			!= HAL_OK) {
		Error_Handler();
	}

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
	RCC_OscInitStruct.PLL.PLLM = 1;
	RCC_OscInitStruct.PLL.PLLN = 10;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
	RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK) {
		Error_Handler();
	}
}

/**
 * @brief LPUART1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_LPUART1_UART_Init(void) {

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
	if (HAL_UART_Init(&hlpuart1) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN LPUART1_Init 2 */

	/* USER CODE END LPUART1_Init 2 */

}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void) {
	/* USER CODE BEGIN MX_GPIO_Init_1 */
	/* USER CODE END MX_GPIO_Init_1 */

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOG_CLK_ENABLE();
	HAL_PWREx_EnableVddIO2();
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
void Error_Handler(void) {
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1) {
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
