#ifndef __HC_SR04_H
#define __HC_SR04_H

#include "stm32f4xx.h"


/*
	����	PE6
	���	PB6

*/

// ��ʼ��KEY����
void HC_SR04_Init(void);


float HC_SR04_Get_Distant(void);
void HC_SR04_Print(void);
#endif /* __HC_SR04_H */
