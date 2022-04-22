/*
 * delay.c
 *
 *  Created on: 2022年3月15日
 *      Author: caoyuqian
 */
#include "delay.h"

const uint32_t CPU_FREQUENCY_MHZ = 209;

void delay_us(__IO uint32_t Delay)
{
	int last;
	int curr;
	int val;

	int temp;

	while(Delay != 0)
	{
		temp = Delay>900?900:Delay;
		last = SysTick->VAL;
		curr = last-CPU_FREQUENCY_MHZ*temp;

		if (curr >= 0)
		{
			do
			{
				val = SysTick->VAL;
			}
			while((val<last)&&(val>=curr));

		}
		else
		{
			curr += CPU_FREQUENCY_MHZ*1000;
			do
			{
				val = SysTick->VAL;
			}
			while((val >= last)||(val < curr));
		}
		Delay -= temp;
	}

}

void delay_ms(__IO uint32_t Delay)
{
	HAL_Delay(Delay);
}
