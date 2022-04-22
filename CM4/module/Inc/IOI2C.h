/*
 * IOI2C.h
 *
 *  Created on: 2022年3月15日
 *      Author: caoyuqian
 */

#ifndef INC_IOI2C_H_
#define INC_IOI2C_H_

#include "GPIO_bsp.h"
#include "delay.h"
//#include "stm32f4xx.h"
//#include "sys.h"
  /**************************************************************************
作者：平衡小车之家
我的淘宝小店：http://shop114407458.taobao.com/
**************************************************************************/
//IO口操作宏定义
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2))
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr))
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum))


//IO方向设置
#define SDA_IN()  {GPIOG->MODER&=~(3<<(2*2));GPIOG->MODER|=0<<2*2;}	//PB11输入模式
#define SDA_OUT() {GPIOG->MODER&=~(3<<(2*2));GPIOG->MODER|=1<<2*2;} 	//PB11输出模式

#ifdef USE_HARDWARE_I2C

#else
//IO操作函数
//#define IIC_SCL    PBout(10) //SCL
//#define IIC_SDA    PBout(11) //SDA
//#define READ_SDA   PBin(11)  //输入SDA

#define IIC_SCL(n) HAL_GPIO_WritePin(GPIOG,GPIO_PIN_1,n)
#define IIC_SCL_SET() HAL_GPIO_WritePin(GPIOG,GPIO_PIN_1,GPIO_PIN_SET)
#define IIC_SCL_CLR() HAL_GPIO_WritePin(GPIOG,GPIO_PIN_1,GPIO_PIN_RESET)
#define IIC_SDA(n) HAL_GPIO_WritePin(GPIOG,GPIO_PIN_2,n)
#define IIC_SDA_SET() HAL_GPIO_WritePin(GPIOG,GPIO_PIN_2,GPIO_PIN_SET)
#define IIC_SDA_CLR() HAL_GPIO_WritePin(GPIOG,GPIO_PIN_2,GPIO_PIN_RESET)

#define READ_SDA() HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_2)

//IIC所有操作函数
void IIC_Init(void);                //初始化IIC的IO口
int IIC_Start(void);				//发送IIC开始信号
void IIC_Stop(void);	  			//发送IIC停止信号
void IIC_Send_Byte(uint8_t txd);			//IIC发送一个字节
uint8_t IIC_Read_Byte(unsigned char ack);//IIC读取一个字节
int IIC_Wait_Ack(void); 			//IIC等待ACK信号
void IIC_Ack(void);					//IIC发送ACK信号
void IIC_NAck(void);				//IIC不发送ACK信号

void IIC_Write_One_Byte(uint8_t daddr,uint8_t addr,uint8_t data);
uint8_t IIC_Read_One_Byte(uint8_t daddr,uint8_t addr);
unsigned char I2C_Readkey(unsigned char I2C_Addr);

unsigned char I2C_ReadOneByte(unsigned char I2C_Addr,unsigned char addr);
unsigned char IICwriteByte(unsigned char dev, unsigned char reg, unsigned char data);
uint8_t IICwriteBytes(uint8_t dev, uint8_t reg, uint8_t length, uint8_t* data);
uint8_t IICwriteBits(uint8_t dev,uint8_t reg,uint8_t bitStart,uint8_t length,uint8_t data);
uint8_t IICwriteBit(uint8_t dev,uint8_t reg,uint8_t bitNum,uint8_t data);
uint8_t IICreadBytes(uint8_t dev, uint8_t reg, uint8_t length, uint8_t *data);

int i2cWrite(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *data);
int i2cRead(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *buf);
#endif

#endif /* INC_IOI2C_H_ */
