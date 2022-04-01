/*
 * MotorPIControlerTest.c
 *
 *  Created on: Mar 30, 2022
 *      Author: caoyuqian
 */

#include "MotorPIControllerTest.h"
#include "GPIO_bsp.h"
#include "control.h"

#if MOTOR_PID_CONTROLOR_TEST

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	HAL_Delay(10);

	Encoder_Right=__MOTOR_READ_RIGHT_ENCODER();  ////为了保证M法测速的时间基准，首先读取编码器数据
	__MOTOR_CLEAR_RIGHT_ENCODER();
	Encoder_Left=__MOTOR_READ_LEFT_ENCODER();    //
	__MOTOR_CLEAR_LEFT_ENCODER();

	Motor_Left=Incremental_PI_Left(Encoder_Left,Target_Left);  //===速度闭环控制计算左电机最终PWM
	Motor_Right=Incremental_PI_Right(Encoder_Right,Target_Right);  //===速度闭环控制计算右电机最终PWM
	Xianfu_Pwm(8200);                          //===PWM限幅
	Set_Pwm(Motor_Left,Motor_Right);
}

void MOTOR_STOP()
{
	Target_Left=0;
	Target_Right=0;
}
void GO_AHEAD(long int velocity)
{
	Target_Left=Target;
	Target_Right=Target;
}
void GO_BACK(long int velocity)
{
	Target_Left=-Target;
	Target_Right=-Target;
}
void TURN_LEFT(float velocity,float angle)
{
	Target_Left=(velocity-angle);
	Target_Right=(velocity+angle);
}
void TURN_RIGHT(float velocity,float angle)
{
	Target_Left=(velocity+angle);
	Target_Right=(velocity-angle);
}

void MOTOR_Init()
{
	HAL_LPTIM_Encoder_Start(&hlptim1,0xFFFF);
	HAL_LPTIM_Encoder_Start(&hlptim2,0xFFFF);
	HAL_TIM_PWM_Start(&htim13, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim14, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim16, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim17, TIM_CHANNEL_1);

	//HAL_TIM_Base_Start_IT(&htim1);
}

#endif
