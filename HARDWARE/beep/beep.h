#ifndef __BEEP_H
#define __BEEP_H

#include "stm32f4xx.h"


/*
	BEEP	PF8
*/

#define BEEP PFOut(8)

//初始化LED函数
void BEEP_Init(void);
void BEEP_Open(void);
void BEEP_Close(void);

/******蜂鸣器响固定ms秒数******
*	parm i	响的ms值
*
*/
void BEEP_Ring(int i);

#endif /* __BEEP_H */
