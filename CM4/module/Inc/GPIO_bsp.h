/*
 * GPIO_bsp.h
 *
 *  Created on: 2022年3月14日
 *      Author: caoyuqian
 */

#ifndef MODULE_INC_GPIO_BSP_H_
#define MODULE_INC_GPIO_BSP_H_

#include "Debug_flags.h"
#include "main.h"
#include "ipcc.h"
#include "lptim.h"
#include "usart.h"
#include "gpio.h"
#include "tim.h"
//#include "stm32mp1xx_hal_tim.h"
//#include "MPU6050.h"

#include "dmpKey.h"
#include "dmpmap.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#if __STM32F405_

typedef struct MotorPIDControl{
	long int Motor_Left;
	long int Motor_Right;		//电机PWM变量

	long int Target_Left;
	long int Target_Right;		//电机目标值

	float Velocity;				//速度和角度变量

	float Velocity_KP;
	float Velocity_KI;	//速度控制PID参数
}MotorControler;

///
///外设控制
///
//#define USE_HARDWARE_I2C

///
///ENCODER
///
#define MOTOR_LEFT_ENCODER_TIM &htim2
#define MOTOR_RIGHT_ENCODER_TIM &htim4

enum
{

	Motor_Left_Encoder	=	2,
	Motor_Right_Encoder	=	4

}Encoder_ENUM;

#define __MOTOR_READ_LEFT_ENCODER() (-__HAL_TIM_GET_COUNTER(MOTOR_LEFT_ENCODER_TIM))
#define __MOTOR_CLEAR_LEFT_ENCODER() __HAL_TIM_SET_COUNTER(MOTOR_LEFT_ENCODER_TIM,0)
#define __MOTOR_READ_RIGHT_ENCODER() __HAL_TIM_GET_COUNTER(MOTOR_RIGHT_ENCODER_TIM)
#define __MOTOR_CLEAR_RIGHT_ENCODER() __HAL_TIM_SET_COUNTER(MOTOR_RIGHT_ENCODER_TIM,0)

///
///PWM
///

#define __MOTOR_LEFT_PWMA1(n)		__HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_3,n) //PC8
#define __MOTOR_LEFT_PWMA2(n)		__HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_1,n) //PC6
#define __MOTOR_RIGHT_PWMB1(n)		__HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_4,n) //PC9
#define __MOTOR_RIGHT_PWMB2(n)		__HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_2,n) //PC7
//#define SET_PWMA(n) __HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_3,n);
//#define SET_PWMB(n) __HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_4,n);

///
///MOTOR_GPIO
///

//#define LEFT_MOTOR_GPIO_AIN1 GPIO_PIN_13
//#define LEFT_MOTOR_GPIO_AIN2 GPIO_PIN_12
//#define RIGHT_MOTOR_GPIO_BIN1 GPIO_PIN_14
//#define RIGHT_MOTOR_GPIO_BIN2 GPIO_PIN_15

#endif

#if __STM32MP157a_

#define MOTOR_LEFT_ENCODER_TIM &hlptim1
#define MOTOR_RIGHT_ENCODER_TIM &hlptim2

#define __MOTOR_READ_LEFT_ENCODER()		(-HAL_LPTIM_ReadCounter(MOTOR_LEFT_ENCODER_TIM))
#define __MOTOR_CLEAR_LEFT_ENCODER()	__HAL_TIM_SET_COUNTER(MOTOR_LEFT_ENCODER_TIM,0)
#define __MOTOR_READ_RIGHT_ENCODER()	HAL_LPTIM_ReadCounter(MOTOR_RIGHT_ENCODER_TIM)
#define __MOTOR_CLEAR_RIGHT_ENCODER()	__HAL_TIM_SET_COUNTER(MOTOR_RIGHT_ENCODER_TIM,0)

#define __MOTOR_LEFT_PWMA1(n)		__HAL_TIM_SET_COMPARE(&htim13,TIM_CHANNEL_1,n) //PF8
#define __MOTOR_LEFT_PWMA2(n)		__HAL_TIM_SET_COMPARE(&htim14,TIM_CHANNEL_1,n) //PF9
#define __MOTOR_RIGHT_PWMB1(n)		__HAL_TIM_SET_COMPARE(&htim16,TIM_CHANNEL_1,n) //PF6
#define __MOTOR_RIGHT_PWMB2(n)		__HAL_TIM_SET_COMPARE(&htim17,TIM_CHANNEL_1,n) //PF7

#endif
///
///GPIO重定向
///

#define __PASET(n)		HAL_GPIO_WritePin(GPIOA, n, GPIO_PIN_SET)
#define __PARESET(n)	HAL_GPIO_WritePin(GPIOA, n, GPIO_PIN_RESET)

#define __PBSET(n)		HAL_GPIO_WritePin(GPIOB, n, GPIO_PIN_SET)
#define __PBRESET(n)	HAL_GPIO_WritePin(GPIOB, n, GPIO_PIN_RESET)
#define __PCSET(n)		HAL_GPIO_WritePin(GPIOC, n, GPIO_PIN_SET)
#define __PCRESET(n)	HAL_GPIO_WritePin(GPIOC, n, GPIO_PIN_RESET)

#define __GET_PA_STATE(n) HAL_GPIO_ReadPin(GPIOA,n)
#define __GET_PB_STATE(n) HAL_GPIO_ReadPin(GPIOB,n)
#define __GET_PC_STATE(n) HAL_GPIO_ReadPin(GPIOC,n)

#endif /* MODULE_INC_GPIO_BSP_H_ */
