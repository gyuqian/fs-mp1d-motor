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
#include "ipcc.h"
#include "lptim.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
//#include "tim.h"

#include "Debug_Flags.h"
#include "BSP_Motor.h"
#include "MPU6050.h"
#if PID_CONTROLER_DEBUG_MODE
#include "MotorPIControllerTest.h"
#include "control.h"
#endif
#if USE_DATASCOPE
#include "show.h"
#endif

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
//extern LPTIM_HandleTypeDef hlptim2;
//extern UART_HandleTypeDef huart4;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
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
	//uint32_t i=0;
	//int Encoder_Right_Last=0;
	//int Encoder_Right_temp=0;

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  if(IS_ENGINEERING_BOOT_MODE())
  {
    /* Configure the system clock */
    SystemClock_Config();
  }
  else
  {
    /* IPCC initialisation */
     MX_IPCC_Init();
  }

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_LPTIM2_Init();
  MX_LPTIM1_Init();
  MX_TIM16_Init();
  MX_TIM17_Init();
  MX_TIM13_Init();
  MX_TIM14_Init();
  MX_TIM1_Init();
  MX_USART3_UART_Init();
  MX_UART5_Init();
  /* USER CODE BEGIN 2 */
  BSP_Motor_Init();

  HAL_GPIO_WritePin(GPIOH, GPIO_PIN_6,GPIO_PIN_SET);
  //MPU6050_initialize();
  //DMP_Init();
  HAL_GPIO_WritePin(GPIOH, GPIO_PIN_6,GPIO_PIN_RESET);

#if MOTOR_PID_CONTROLOR_TEST
  HAL_TIM_Base_Start_IT(&htim1);
#endif
  HAL_Delay(1000);

#if MOTOR_PID_CONTROLOR_TEST
  //BSP_Motor_GO_AHEAD(-575);

  //GO_BACK();
  Target_Left=-0;
  Target_Right=-0;
  //Encoder_Right=__MOTOR_READ_RIGHT_ENCODER();
#endif

#if LPTIM_ENCODER_MOD_TEST
		__HAL_TIM_SET_COUNTER(MOTOR_LEFT_ENCODER_TIM,100);
		//__HAL_TIM_IS_TIM_COUNTING_DOWN(MOTOR_LEFT_ENCODER_TIM);
#endif
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
#if LPTIM_ENCODER_MOD_TEST
		//__HAL_TIM_SET_COUNTER(MOTOR_LEFT_ENCODER_TIM,100);
		//__HAL_TIM_SET_COUNTER(MOTOR_LEFT_ENCODER_TIM,0);
		//__HAL_TIM_IS_TIM_COUNTING_DOWN(MOTOR_LEFT_ENCODER_TIM);

	  HAL_LPTIM_Encoder_Stop(&hlptim2);
	  ((&hlptim2)->Instance->CNT = 0);
	  HAL_LPTIM_Encoder_Start(&hlptim2, 0xFFFF);

	  HAL_LPTIM_Encoder_Stop(&hlptim2);
	  ((&hlptim2)->Instance->CNT = 100);
	  HAL_LPTIM_Encoder_Start(&hlptim2, 0xFFFF);
#endif
#if 0
	  uint32_t temp;
	  HAL_Delay(100);
	  temp=HAL_LPTIM_ReadCounter(&hlptim2);
	  HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_12);

	  uint8_t str1[10]="UART5\r\n";

	  HAL_UART_Transmit(&huart5,(uint8_t *)"LPTIME2\r\n", sizeof("LPTIME2\r\n"), 1000);
	  HAL_UART_Transmit(&huart5,str1,sizeof(str1),1000);

	  __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_2,4200);
#endif
#if PID_CONTROLER_DEBUG_MODE

		HAL_Delay(10);
		//Encoder_Right_Last=Encoder_Right;

		Encoder_Right=__MOTOR_READ_RIGHT_ENCODER();  ////为了保证M法测速的时间基准，首先读取编码器数据
#if 0
		if(Encoder_Right_Last>Encoder_Right)
		{
			Encoder_Right_temp=Encoder_Right+65536-Encoder_Right_Last;
		}
		else
		{
			Encoder_Right_temp=Encoder_Right-Encoder_Right_Last;
		}
#endif
		__MOTOR_CLEAR_RIGHT_ENCODER();

		//uint32_t temp=__MOTOR_READ_RIGHT_ENCODER();
		Encoder_Left=__MOTOR_READ_LEFT_ENCODER();    //
		__MOTOR_CLEAR_LEFT_ENCODER();

		Motor_Left=Incremental_PI_Left(Encoder_Left,Target_Left);  //===速度闭环控制计算左电机最终PWM
		Motor_Right=Incremental_PI_Right(Encoder_Right,Target_Right);  //===速度闭环控制计算右电机最终PWM
		Xianfu_Pwm(8200);                          //===PWM限幅
		Set_Pwm(Motor_Left,Motor_Right);

		//BSP_Motor_GetSenseOfRotationLeft();
		//BSP_Motor_GetSenseOfRotationRight();
		//Set_Pwm(-8200, -8200);


		HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_12);
#endif
#if USE_DATASCOPE
		DataScope();
		HAL_Delay(50);
#endif
#if !(MOTOR_PID_CONTROLOR_TEST)
		HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_12);
		HAL_GPIO_TogglePin(GPIOH, GPIO_PIN_6);
		HAL_Delay(100);

		//__HAL_TIM_SET_COMPARE(&htim13,TIM_CHANNEL_1,4199);
		//__HAL_TIM_SET_COMPARE(&htim14,TIM_CHANNEL_1,4199);
		//__HAL_TIM_SET_COMPARE(&htim16,TIM_CHANNEL_1,4199);
		//__HAL_TIM_SET_COMPARE(&htim17,TIM_CHANNEL_1,4199);
#else
		/*if(i==40)
		{
			i=0;
			if(Target_Left<50&&Target_Right<50)
			{
				Target_Left+=2;
				Target_Right+=2;
			}
			else
			{
				Target_Left=50;
				Target_Right=50;
			}
		}
		else
		{
			i++;
		}*/
#endif
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSI
                              |RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.HSIDivValue = RCC_HSI_DIV1;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  RCC_OscInitStruct.PLL2.PLLState = RCC_PLL_NONE;
  RCC_OscInitStruct.PLL3.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL3.PLLSource = RCC_PLL3SOURCE_HSE;
  RCC_OscInitStruct.PLL3.PLLM = 2;
  RCC_OscInitStruct.PLL3.PLLN = 52;
  RCC_OscInitStruct.PLL3.PLLP = 3;
  RCC_OscInitStruct.PLL3.PLLQ = 2;
  RCC_OscInitStruct.PLL3.PLLR = 2;
  RCC_OscInitStruct.PLL3.PLLRGE = RCC_PLL3IFRANGE_1;
  RCC_OscInitStruct.PLL3.PLLFRACV = 2048;
  RCC_OscInitStruct.PLL3.PLLMODE = RCC_PLL_FRACTIONAL;
  RCC_OscInitStruct.PLL4.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** RCC Clock Config
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_ACLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_PCLK3|RCC_CLOCKTYPE_PCLK4
                              |RCC_CLOCKTYPE_PCLK5;
  RCC_ClkInitStruct.AXISSInit.AXI_Clock = RCC_AXISSOURCE_HSI;
  RCC_ClkInitStruct.AXISSInit.AXI_Div = RCC_AXI_DIV1;
  RCC_ClkInitStruct.MCUInit.MCU_Clock = RCC_MCUSSOURCE_PLL3;
  RCC_ClkInitStruct.MCUInit.MCU_Div = RCC_MCU_DIV1;
  RCC_ClkInitStruct.APB4_Div = RCC_APB4_DIV1;
  RCC_ClkInitStruct.APB5_Div = RCC_APB5_DIV1;
  RCC_ClkInitStruct.APB1_Div = RCC_APB1_DIV2;
  RCC_ClkInitStruct.APB2_Div = RCC_APB2_DIV2;
  RCC_ClkInitStruct.APB3_Div = RCC_APB3_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Set the HSE division factor for RTC clock
  */
  __HAL_RCC_RTC_HSEDIV(1);
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
