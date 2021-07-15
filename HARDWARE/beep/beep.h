#ifndef __BEEP_H
#define __BEEP_H

#include "stm32f4xx.h"


/*
	BEEP	PF8
*/

#define BEEP PFOut(8)

//��ʼ��LED����
void BEEP_Init(void);
void BEEP_Open(void);
void BEEP_Close(void);

/******��������̶�ms����******
*	parm i	���msֵ
*
*/
void BEEP_Ring(int i);

#endif /* __BEEP_H */
