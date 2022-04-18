/*
 * DataScope_DP.h
 *
 *  Created on: Jan 7, 2022
 *      Author: caoyuqian
 */

#ifndef DATASCOPE_INC_DATASCOPE_DP_H_
#define DATASCOPE_INC_DATASCOPE_DP_H_

#ifdef __cplusplus
extern "C" {
#endif

extern unsigned char DataScope_OutPut_Buffer[42];


void DataScope_Get_Channel_Data(float Data,unsigned char Channel);

unsigned char DataScope_Data_Generate(unsigned char Channel_Number);

#ifdef __cplusplus
}
#endif


#endif /* DATASCOPE_INC_DATASCOPE_DP_H_ */
