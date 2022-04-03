/*
 * BSP_Motor.c
 *
 *  Created on: 2022年4月3日
 *      Author: caoyuqian
 */

#include "BSP_Motor.h"
#include "control.h"

void BSP_Motor_Init()
{
	HAL_LPTIM_Encoder_Start(&hlptim1,0xFFFF);
	HAL_LPTIM_Encoder_Start(&hlptim2,0xFFFF);
	HAL_TIM_PWM_Start(&htim13, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim14, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim16, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim17, TIM_CHANNEL_1);

	//HAL_TIM_Base_Start_IT(&htim1);
}

float BSP_Motor_GetVelocity(int hMotor)
{
	switch(hMotor)
	{
	case MOTOR_LEFT:
		return (Encoder_Left/4.0/10.0);
		break;

	case MOTOR_RIGHT:
		return (Encoder_Right/4.0/10.0);
		break;

	default:
		return BSP_MOTOR_ENUM_ERROR;
	}
}

float BSP_Motor_GetVelocityOfLeft()
{
	return (BSP_Motor_GetVelocity(MOTOR_LEFT));
}

float BSP_Motor_GetVelocityOfRight()
{
	return (BSP_Motor_GetVelocity(MOTOR_RIGHT));
}

static BSP_MOTOR_SenseOfRotation BSP_Motor_GetSenseOfRotation(int hMotor)
{
	switch(hMotor)
	{
	case MOTOR_LEFT:
		if(__HAL_LPTIM_GET_FLAG(MOTOR_LEFT_ENCODER_TIM,LPTIM_FLAG_UP))
		{
			return MOTOR_FORWARD;
		}
		else
		{
			return MOTOR_REVERSE;
		}
		break;

	case MOTOR_RIGHT:
		if(__HAL_LPTIM_GET_FLAG(MOTOR_RIGHT_ENCODER_TIM,LPTIM_FLAG_UP))
		{
			return MOTOR_FORWARD;
		}
		else
		{
			return MOTOR_REVERSE;
		}
		break;
	default:
			return BSP_MOTOR_ENUM_ERROR;
	}
}

BSP_MOTOR_SenseOfRotation BSP_Motor_GetSenseOfRotationLeft()
{
	return (BSP_Motor_GetSenseOfRotation(MOTOR_LEFT));
}

BSP_MOTOR_SenseOfRotation BSP_Motor_GetSenseOfRotationRight()
{
	return (BSP_Motor_GetSenseOfRotation(MOTOR_RIGHT));
}

static void BSP_MOTOR_SetVelocity(long int left_velocity,long int right_velocity)
{
	Target_Left=left_velocity;
	Target_Right=right_velocity;
}

void BSP_Motor_STOP()
{
	BSP_MOTOR_SetVelocity(0,0);
}
void BSP_Motor_GO_AHEAD(long int velocity)
{
	BSP_MOTOR_SetVelocity(velocity,velocity);
}
void BSP_Motor_GO_BACK(long int velocity)
{
	BSP_MOTOR_SetVelocity(velocity, velocity);
}
void BSP_Motor_TURN_LEFT(float velocity,float angle)
{
	BSP_MOTOR_SetVelocity(velocity-angle, velocity+angle);
	//Target_Left=(long int)((velocity-angle));
	//Target_Right=(long int)((velocity+angle));
}
void BSP_Motor_TURN_RIGHT(float velocity,float angle)
{
	BSP_MOTOR_SetVelocity(velocity+angle, velocity-angle);
	//Target_Left=(long int)((velocity+angle));
	//Target_Right=(long int)((velocity-angle));
}
