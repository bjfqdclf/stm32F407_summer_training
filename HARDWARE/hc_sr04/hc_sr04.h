#ifndef __HC_SR04_H
#define __HC_SR04_H

#include "stm32f4xx.h"


/*
	输入	PE6
	输出	PB6

*/

// 初始化KEY函数
void HC_SR04_Init(void);


float HC_SR04_Get_Distant(void);
void HC_SR04_Print(void);
void HC_SR04_Ladar(void);
void HC_SR04_Ladar_Level(void);
void HC_SR04_Ladar_Open(void);
#endif /* __HC_SR04_H */
