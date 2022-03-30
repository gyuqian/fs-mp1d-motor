/*
 * DEBUG_FLGS.h
 *
 *  Created on: Mar 17, 2022
 *      Author: caoyuqian
 */

#ifndef INC_DEBUG_FLAGS_H_
#define INC_DEBUG_FLAGS_H_

#define BOOL_TRUE 1
#define BOOL_FALSE 0

///
///DEBUG
///
#define TIM1_CALLBACK_DEBUG			BOOL_FALSE

#define PWM_DEBUG_MODE				BOOL_FALSE
#define PID_CONTROLER_DEBUG_MODE	BOOL_FALSE

#define __STM32F405_ 				BOOL_FALSE
#define __STM32MP157a_ 				BOOL_TRUE

#define MOTOR_PID_CONTROLOR_TEST	BOOL_TRUE

//#undef BOOL_TRUE
//#undef BOOL_FALSE

#endif /* INC_DEBUG_FLAGS_H_ */
