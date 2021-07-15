#ifndef __KEY_H
#define __KEY_H

#include "stm32f4xx.h"


/*
	key0	PA0
	key1	PE2
	key2	PE3
	key3	PE4
*/

// ��ʼ��KEY����
void KEY_Init(void);

int KEY_Check(int);

/******����ɨ��******
*	return 0,1,2,3,4
*
*/
int KEY_Scan(void);

/******����******
*	return 0,1
*
*/
int KEY_Password(void);
#endif /* __KEY_H */
