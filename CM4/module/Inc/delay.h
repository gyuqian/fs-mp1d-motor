/*
 * delay.h
 *
 *  Created on: 2022年3月15日
 *      Author: caoyuqian
 */

#ifndef INC_DELAY_H_
#define INC_DELAY_H_

#ifdef __cplusplus
extern "C" {
#endif
#include "GPIO_bsp.h"

void delay_us(__IO uint32_t Delay);
void delay_ms(__IO uint32_t Delay);


#ifdef __cplusplus
}
#endif

#endif /* INC_DELAY_H_ */
