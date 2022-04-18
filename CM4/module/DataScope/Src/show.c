/*
 * show.c
 *
 *  Created on: Jan 7, 2022
 *      Author: caoyuqian
 */

#include "show.h"
#include "DataScope_DP.h"
#include "GPIO_bsp.h"
#include "control.h"

void DataScope(void)
{
	int Send_Count;
	//int i;

	DataScope_Get_Channel_Data( Target_Left, 1 );
	DataScope_Get_Channel_Data( Encoder_Left, 2 );
	DataScope_Get_Channel_Data( Target_Right, 3 );
	DataScope_Get_Channel_Data( Encoder_Right , 4 );
//	DataScope_Get_Channel_Data(0, 5 );
//	DataScope_Get_Channel_Data(0 , 6 );
//	DataScope_Get_Channel_Data(0, 7 );
//	DataScope_Get_Channel_Data( 0, 8 );
//	DataScope_Get_Channel_Data(0, 9 );
//	DataScope_Get_Channel_Data( 0 , 10);

	Send_Count = DataScope_Data_Generate(4);

//	CDC_Transmit_FS((uint8_t *)DataScope_OutPut_Buffer, Send_Count);
	HAL_UART_Transmit(&huart5, (uint8_t *)DataScope_OutPut_Buffer, Send_Count, 1000);
}
