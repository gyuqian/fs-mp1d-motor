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

void GO_AHEAD(long int);
void GO_BACK(long int);
void TURN_LEFT(float,float);
void TURN_RIGHT(float,float);
void STOP();

#endif


#endif /* INC_MOTORPICONTROLLERTEST_H_ */
