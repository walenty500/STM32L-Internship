/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "tim.h"
#include "ts.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "kontrolauart.h"
#include "timer.h"
#include <stdio.h>
#include<stdlib.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
	TimeStamp_type test2;
	void TIM7_IRQHandler(void);
//	AddTimestamp(&test2,2000);
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void delay(int a);
void send_string(char* s);
uint8_t receive_buffer;
uint8_t dataHadleFlag=0;
uint8_t buf_size;
uint8_t buf_output;
uint8_t countr=0;
uint8_t data_main=0;
GPIO_InitTypeDef GPIO_InitStruct;
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

uint8_t czy=0;
uint8_t TS_updated=0;

void toggle_led_blue()
{
	HAL_GPIO_TogglePin(LD4_GPIO_Port,LD4_Pin);
}

void toggle_led_green()
{
	HAL_GPIO_TogglePin(LD3_GPIO_Port,LD3_Pin);
	AddTimestamp(&test2,2000);
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
  MX_ADC_Init();
  MX_TS_Init();
  MX_USART1_UART_Init();
  MX_TIM7_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT(&htim7);
int ctr=0;
	const char message[] = "Benek";
	const char message2[] = "Hello World";

	HAL_UART_Receive_IT(&huart1, &receive_buffer, 1);

	__HAL_UART_CLEAR_IDLEFLAG(&huart1);
	__HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE);

//	*head=NULL;
	TimeStamp_type test;
	test.Handler=&toggle_led_blue;
	AddTimestamp(&test,2000);
//	Del_First_Timestamp();
//	TimeStamp_type test2;
	test2.Handler=&toggle_led_green;
	AddTimestamp(&test2,4000);
	TimeStamp_type test3;
	test3.Handler=&toggle_led_blue;
	AddTimestamp(&test3,6000);
	TimeStamp_type test5;
	test5.Handler=&toggle_led_green;
	AddTimestamp(&test5,8000);
//	TS_updated=UpdateTimeStamp();
//	DelTimeStamp(&test3);
//	DelTimeStamp(&test);
//	DelTimeStamp(&test3);
//	Del_First_Timestamp();

//	List_Init(head);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	while (1)
{
//	uint8_t currRxsize=dataInRx();
//	if(dataHadleFlag==1)   //Judging whether it is idle interruption
//		{
//		dataHadleFlag=0;                   //Clear idle interrupt sign (otherwise it will continue to enter interrupt)
//	       handleData();
//	       czy++;
//
//		}
	if(UpdateTimeStamp()) continue;
	//wysylanie wiadomosci na klikniecie przycisku
	  if(HAL_GPIO_ReadPin(B1_GPIO_Port,B1_Pin))
	 	  {
	 		  while(HAL_GPIO_ReadPin(B1_GPIO_Port,B1_Pin))
	 		  {

	 		  }

	 		 putCharTx(11, message2);

//	 		ctr++;
//	 		ctr=ctr%2;
//	 		if(ctr==0){
//		 		HAL_UART_Transmit(&huart1, (uint8_t*)message, strlen(message), HAL_MAX_DELAY);
//		 		}else{
//		 			HAL_UART_Transmit(&huart1, (uint8_t*)message2, strlen(message2), HAL_MAX_DELAY);
//		 		}
	 	  }
	//wysylanie co 5s danych z Tx - trzeba wczesniej do tx cos wpisac
//			HAL_Delay(5000);
//			uint8_t dane_wyslane[MY_BUFOR_BUFSIZE];
//			uint8_t dataInTxBuf=dataInTx();
//			if(dataInTxBuf!=0)
//			{
//				obslugaCzytaniaCyclicTx(1,&data_main);
//				HAL_UART_Transmit_IT(&huart1, &data_main, 1);
//			}
//	 		HAL_GPIO_TogglePin(LD4_GPIO_Port,LD4_Pin);
//	 		obslugaCzytania(1);
//

//	 	  }
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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
  RCC_OscInitStruct.PLL.PLLDIV = RCC_PLL_DIV3;
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
}

/* USER CODE BEGIN 4 */

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
//	HAL_GPIO_TogglePin(LD3_GPIO_Port,LD3_Pin);
//	HAL_UART_Receive_IT (&huart1, &receive_buffer, 1);
//	putCharRx(receive_buffer);
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
//	HAL_GPIO_TogglePin(LD4_GPIO_Port,LD4_Pin);
//	uint8_t dataInTxBuf=dataInTx();
//	if(dataInTxBuf!=0)
//	{
//		obslugaCzytaniaCyclicTx(1,&data_main);
//		HAL_UART_Transmit_IT(&huart1, &data_main, 1);
//	}
//	else
//	{
//		__HAL_UART_DISABLE_IT(&huart1, UART_IT_TXE);
//	}
}

void user_uart_handler(UART_HandleTypeDef *huart)
{
//	if(__HAL_UART_GET_FLAG(&huart1, UART_FLAG_IDLE))   //Judging whether it is idle interruption
//		{
//	       __HAL_UART_CLEAR_IDLEFLAG(&huart1);                     //Clear idle interrupt sign (otherwise it will continue to enter interrupt)
////	       czy++;
//	       dataHadleFlag=1;
//		}
	if ((USART1->SR & USART_SR_TXE) != RESET)
	{
		uint8_t dataInTxBuf=sizeofTx();
			uint8_t data=0;
			if(dataInTxBuf!=0)
			{
				HAL_GPIO_TogglePin(LD4_GPIO_Port,LD4_Pin);
				data=getCharTX();
				USART1->DR=((data) & (uint8_t)0x00FF);
//				USART1->DR=((data) & (uint8_t)0x00FF);
		//		__HAL_UART_ENABLE_IT(&huart1, UART_IT_TXE);
		//		HAL_UART_Transmit_IT(&huart1, &data_main, 1);
			}

			else
			{
				__HAL_UART_DISABLE_IT(&huart1, UART_IT_TXE);
				//return;(?)
			}
	}

    if (((USART1->SR & USART_SR_RXNE) != RESET) && ((USART1->CR1 & USART_CR1_RXNEIE) != RESET))
    {
    	uint8_t dataInRxBuf=sizeofRX();
		uint8_t data=0;
		if(dataInRxBuf>=MY_BUFOR_BUFSIZE)
		{
			HAL_GPIO_TogglePin(LD3_GPIO_Port,LD3_Pin);
			data=USART1->DR;
			putCharRx(data);
//      UART_Receive_IT(huart);
//      return;
		}
		else
		{
			__HAL_UART_DISABLE_IT(&huart1, UART_IT_RXNE);
		}
    }
//	uint8_t dataInTxBuf=sizeofTx();
//	uint8_t data=0;
//	if(dataInTxBuf!=0)
//	{
//		HAL_GPIO_TogglePin(LD4_GPIO_Port,LD4_Pin);
//		data=getCharTX();
//		USART1->DR=((data) & (uint8_t)0x00FF);
////		__HAL_UART_ENABLE_IT(&huart1, UART_IT_TXE);
////		HAL_UART_Transmit_IT(&huart1, &data_main, 1);
//	}
//	else
//	{
//		__HAL_UART_DISABLE_IT(&huart1, UART_IT_TXE);
//	}

//	uint8_t dataInRxBuf=dataInRx();
//	if(dataInRxBuf!=0)
//	{
//		HAL_GPIO_TogglePin(LD3_GPIO_Port,LD3_Pin);
//		obslugaCzytaniaCyclicTx(1,&data_main);
//		USART1->DR=(&data_main);
////		__HAL_UART_ENABLE_IT(&huart1, UART_IT_TXE);
////		HAL_UART_Transmit_IT(&huart1, &data_main, 1);
//	}
//	else
//	{
//		__HAL_UART_DISABLE_IT(&huart1, UART_IT_TXE);
//	}
}

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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
