#ifndef __LED_H
#define __LED_H

#include "stm32f4xx.h"


/*
	D1	PF9
	D2	PF10
	D3	PE13
	D4	PE14
*/


#define LED0 PFout(9)

//��ʼ��LED����
void LED_Init(void);
void LED_Open(int);
void LED_Close(int i);

void LED_Water(void); // ��ˮ��

/******����******
*	param i: led number	1,2,3,4
*	param time: globa variable
*
*/
void LED_Flash(int i,int time);	// ����
void LED_BEEP_Flash(int i,int times);
/******�޸������ٶ�******
*	param flag:	1 time+		0 time- 
*	//δʵ��param interval:	time spacing
*
*/
void LED_Speed(int);	// �޸������ٶ�
#endif /* __LED_H */
