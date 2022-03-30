/*
 * control.h
 *
 *  Created on: Mar 14, 2022
 *      Author: caoyuqian
 */

#ifndef INC_CONTROL_H_
#define INC_CONTROL_H_

#include "GPIO_bsp.h"
#include "MPU6050.h"

//extern MotorControler MotorControler1;
#define PI 3.14159265
#define ZHONGZHI 0
#define DIFFERENCE 100
//extern	int Balance_Pwm,Velocity_Pwm,Turn_Pwm;
void Kinematic_Analysis(float velocity,float angle);
//int EXTI15_10_IRQHandler(void);
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
//void Set_Pwm(int motor_a,int motor_b,int servo);
void Key(void);
void Xianfu_Pwm(int amplitude);
void Xianfu_Velocity(int amplitude_A,int amplitude_B);
//u8 Turn_Off( int voltage);
int myabs(int a);
int Incremental_PI_Left (int Encoder,int Target);
int Incremental_PI_Right (int Encoder,int Target);
void Get_RC(void);
void  Find_CCD_Zhongzhi(void);
void Set_Pwm(int motor_a,int motor_b);

#endif /* INC_CONTROL_H_ */
