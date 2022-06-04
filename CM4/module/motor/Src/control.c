/*
 * control.c
 *
 *  Created on: Mar 14, 2022
 *      Author: caoyuqian
 */

#include "control.h"
#include "GPIO_bsp.h"
#include "MPU6050.h"

uint8_t Flag_Target;			//分频标志位
uint32_t j, sum;

const float T = 0.156;
const float L = 0.1445;
const float K = 622.8;

const double PI = 3.14159265;
const uint32_t ZHONGZHI = 0;
const uint32_t DIFFERENCE = 100;

int min_Pwm = 1300;

/****************************************************************************/
uint8_t delay_50;
uint8_t delay_flag;

long int Motor_Left;
long int Motor_Right;		//电机PWM变量

long int Target_Left = 0;
long int Target_Right = 0;		//电机目标

float Velocity;
float Angle;
float Servo;

float Velocity_KP = 10;
float Velocity_KI = 10;	//速度控制PID参数

int Voltage;
int Voltage_Count;
int Voltage_All;

int Encoder_Left;
int Encoder_Right;
/*************************************************************************/
/**************************************************************************
 函数功能：小车运动数学模型
 入口参数：速度和转角
 返回  值：无
 **************************************************************************/
void Kinematic_Analysis(float velocity, float angle)
{
	Target_Left = (velocity - angle);
	Target_Right = (velocity + angle);      //后轮差速
}

/**************************************************************************
 函数功能：绝对值函数
 入口参数：int
 返回  值：unsigned int
 **************************************************************************/
int myabs(int a)
{
	int temp;

	if (a < 0)
	{
		temp = -a;
	}
	else
	{
		temp = a;
	}

	return temp;
}

/**************************************************************************
 函数功能：增量PI控制器
 入口参数：编码器测量值，目标速度
 返回  值：电机PWM
 根据增量式离散PID公式
 pwm+=Kp[e（k）-e(k-1)]+Ki*e(k)+Kd[e(k)-2e(k-1)+e(k-2)]
 e(k)代表本次偏差
 e(k-1)代表上一次的偏差  以此类推
 pwm代表增量输出
 在我们的速度控制闭环系统里面，只使用PI控制
 pwm+=Kp[e（k）-e(k-1)]+Ki*e(k)
 **************************************************************************/
int Incremental_PI_Left(int Encoder, int Target)
{
	static int Bias, Pwm, Last_bias;
	//static int vol_flags;

#if 1

	if ((Target <= 3) && (Target >= -3) && (Target != 0) && (Pwm != 0))
	{
		if (((Target > 0) && (Pwm > 1000)) || ((Target < 0) && (Pwm < -1000)))
		//if (!((Target ^ Pwm) & 0x8000))
		{
			Pwm = 0 - Pwm;
		}
	}

#endif

	Bias = Encoder - Target;                //计算偏差
	Pwm += Velocity_KP * (Bias - Last_bias) + Velocity_KI * Bias;   //增量式PI控制器
	if (Pwm > 8400)
	{
		Pwm = 8400;
	}
	else if (Pwm < -8400)
	{
		Pwm = -8400;
	}

#if 1
	if (Pwm < 1423 && Pwm > -1330)
	{
		if (Target > 0)
		{
			Pwm = -1330;
		}
		else if (Target < 0)
		{
			Pwm = 1423;
		}
		else
		{
			Pwm = Pwm;
		}
	}
#endif

	Last_bias = Bias;	                   //保存上一次偏差
	return Pwm;                         //增量输出
}
int Incremental_PI_Right(int Encoder, int Target)
{
	static int Bias, Pwm, Last_bias;
	Bias = Encoder - Target;                //计算偏差
	Pwm += Velocity_KP * (Bias - Last_bias) + Velocity_KI * Bias;   //增量式PI控制器
	if (Pwm > 8400)
	{
		Pwm = 8400;
	}
	else if (Pwm < -8400)
	{
		Pwm = -8400;
	}
	Last_bias = Bias;	                   //保存上一次偏差
	return Pwm;                         //增量输出
}

/**************************************************************************
 函数功能：赋值给PWM寄存器
 入口参数：PWM
 返回  值：无
 **************************************************************************/
void Set_Pwm(int motor_a, int motor_b)
{
	if (motor_a > 0)
	{

		__MOTOR_LEFT_PWMA1(8400);
		__MOTOR_LEFT_PWMA2(8400 - motor_a);
	}
	else if (motor_a < 0)
	{

		__MOTOR_LEFT_PWMA2(8400);
		__MOTOR_LEFT_PWMA1(8400 + motor_a);
	}
	else
	{
		__MOTOR_LEFT_PWMA2(0);
		__MOTOR_LEFT_PWMA1(0);
	}

	if (motor_b > 0)
	{

		__MOTOR_RIGHT_PWMB1(8400);
		__MOTOR_RIGHT_PWMB2(8400 - motor_b);
	}
	else if (motor_b < 0)
	{

		__MOTOR_RIGHT_PWMB2(8400);
		__MOTOR_RIGHT_PWMB1(8400 + motor_b);
	}
	else
	{
		__MOTOR_RIGHT_PWMB2(0);
		__MOTOR_RIGHT_PWMB1(0);
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	Flag_Target = !Flag_Target; //分频标志位

	if (delay_flag == 1)
	{
		if (++delay_50 == 5)
		{

			delay_50 = 0, delay_flag = 0; //给主函数提供50ms的精准延时
		}
	}

	if (Flag_Target == 1) //5ms读取一次陀螺仪和加速度计的值，并执行一下其他的命令
	{
		/*if(Usart_Flag==0&&Usart_ON_Flag==1){
		 memcpy(rxbuf,Urxbuf,8*sizeof(uint8_t));	//如果解锁了串口控制标志位，读取相关的指令
		 }*/

		Read_DMP();   //===更新姿态
		//Key();//扫描按键变化
		/*if(Flag_Show==0){
		 Led_Flash(100);   //显示OLED的时候 LED闪烁
		 }
		 else if(Flag_Show==1){
		 Led_Flash(0);  //使用上位机的时候，LED常亮
		 }

		 Voltage_All+=Get_battery_volt();     //多次采样累积
		 // Read_Distane();//四路超声波测距读取，默认注释，开启还需要去掉主函数的初始化代码的注释。读取的变量在Distance_A,Distance_B,Distance_C,Distance_D
		 if(++Voltage_Count==100){
		 Voltage=Voltage_All/100,Voltage_All=0,Voltage_Count=0;//求平均值 获取电池电压
		 }*/
	}
	if (Flag_Target == 0)
	{

		Encoder_Right = __MOTOR_READ_RIGHT_ENCODER(); //===读取编码器的值	 //为了保证M法测速的时间基准，首先读取编码器数据
		__MOTOR_CLEAR_RIGHT_ENCODER();
		Encoder_Left = __MOTOR_READ_LEFT_ENCODER();    //===读取编码器的值
		__MOTOR_CLEAR_LEFT_ENCODER();
		Read_DMP();  //===更新姿态
		/*if(Flag_Way==2)   //CCD模式下 读取CCD数据并提取中线
		 {
		 RD_TSL();  //===读取线性CCD数据
		 Find_CCD_Zhongzhi(); //===提取中线
		 }
		 if(Flag_Way==3)		//电磁巡线模式下，采集3个电感的数据并提取中线
		 {
		 Sensor_Left=Get_Adc(11);                //采集左边电感的数据
		 Sensor_Right=Get_Adc(13);               //采集右边电感的数据
		 Sensor_Middle=Get_Adc(12);              //采集中间电感的数据
		 sum=Sensor_Left*1+Sensor_Middle*100+Sensor_Right*199;  //归一化处理
		 Sensor=sum/(Sensor_Left+Sensor_Middle+Sensor_Right);   //求中线偏差
		 }
		 */
		//Get_RC();   //===接收控制指令
		if (
		//Turn_Off(Voltage)==0
		1)//===如果电池电压不存在异常
		{
			Motor_Left = Incremental_PI_Left(Encoder_Left, Target_Left); //===速度闭环控制计算左电机最终PWM
			Motor_Right = Incremental_PI_Right(Encoder_Right, Target_Right); //===速度闭环控制计算右电机最终PWM
			Xianfu_Pwm(8200);                          //===PWM限幅
			Set_Pwm(Motor_Left, Motor_Right);     //===赋值给PWM寄存器
		}
		else
		{
			Set_Pwm(0, 0);    //===赋值给PWM寄存器
		}
	}
}

/**************************************************************************
 函数功能：限制PWM赋值
 入口参数：幅值
 返回  值：无
 **************************************************************************/
void Xianfu_Pwm(int amplitude)
{
	if (Motor_Left < -amplitude)
	{
		Motor_Left = -amplitude;	//限制最小值
	}
	if (Motor_Left > amplitude)
	{
		Motor_Left = amplitude;	  //限制最大值
	}
	if (Motor_Right < -amplitude)
	{
		Motor_Right = -amplitude;	  //限制最小值
	}
	if (Motor_Right > amplitude)
	{
		Motor_Right = amplitude;	//限制最大值
	}
}
