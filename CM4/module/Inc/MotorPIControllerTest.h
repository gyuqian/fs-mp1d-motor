/*
 * MotorPIControlerTest.h
 *
 *  Created on: Mar 30, 2022
 *      Author: caoyuqian
 */

#ifndef INC_MOTORPICONTROLLERTEST_H_
#define INC_MOTORPICONTROLLERTEST_H_

#include "Debug_Flags.h"

#if MOTOR_PID_CONTROLOR_TEST

void MOTOR_Init();

void GO_AHEAD();
void GO_BACK();
void TURN_LEFT();
void TURN_RIGHT();
void STOP();

#endif


#endif /* INC_MOTORPICONTROLLERTEST_H_ */
