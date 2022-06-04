/*
 * control.h
 *
 *  Created on: Mar 14, 2022
 *      Author: caoyuqian
 */

#ifndef INC_CONTROL_H_
#define INC_CONTROL_H_

#include "stm32mp1xx_hal.h"

//extern MotorControler MotorControler1;
extern uint8_t delay_50;
extern uint8_t delay_flag;

extern long int Motor_Left;
extern long int Motor_Right;		//电机PWM变量

extern long int Target_Left;
extern long int Target_Right;		//电机目标�????

extern float Velocity;
extern float Angle;
extern float Servo;				//速度和角度变�????

extern float Velocity_KP;
extern float Velocity_KI;	//速度控制PID参数

extern int Voltage;
extern int Voltage_Count;
extern int Voltage_All;

extern int Encoder_Left;
extern int Encoder_Right;

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
