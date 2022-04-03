/*
 * BSP_Motor.h
 *
 *  Created on: 2022年4月3日
 *      Author: caoyuqian
 */

#ifndef INC_BSP_MOTOR_H_
#define INC_BSP_MOTOR_H_

#include "Debug_Flags.h"

typedef enum
{
	BSP_MOTOR_ENUM_ERROR = -1,
	MOTOR_LEFT	=	0,
	MOTOR_RIGHT	=	1,
}BSP_MOTOR_ENUM;

typedef enum
{
	BSP_MOTOR_SenseOfRotation_ERROR = -1,
	MOTOR_FORWARD = 0,
	MOTOR_REVERSE = 1,
}BSP_MOTOR_SenseOfRotation;

///
///初始化
///
void BSP_Motor_Init();

///
///读取工作状态
///
float BSP_Motor_GetVelocityOfLeft();
float BSP_Motor_GetVelocityOfRight();
BSP_MOTOR_SenseOfRotation BSP_Motor_GetSenseOfRotationLeft();
BSP_MOTOR_SenseOfRotation BSP_Motor_GetSenseOfRotationRight();

///
///控制
///
void BSP_Motor_STOP();
void BSP_Motor_GO_AHEAD(long int velocity);
void BSP_Motor_GO_BACK(long int velocity);
void BSP_Motor_TURN_LEFT(float velocity,float angle);
void BSP_Motor_TURN_RIGHT(float velocity,float angle);

///
///MOTOR PID
///
void Xianfu_Pwm(int amplitude);
int myabs(int a);
int Incremental_PI_Left (int Encoder,int Target);
int Incremental_PI_Right (int Encoder,int Target);
void Set_Pwm(int motor_a,int motor_b);
#endif /* INC_BSP_MOTOR_H_ */
