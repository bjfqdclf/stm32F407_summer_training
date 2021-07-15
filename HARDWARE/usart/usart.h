#ifndef __USART_H
#define __USART_H

#include "stm32f4xx.h"
#include <stdio.h>
#include <string.h>

/*
	RX	PA9
	TX	PA10
*/




//初始化LED函数
void USART1_Init(int);
void USART_Send_word(uint16_t);
void USART_Send_words(char *);


/******调节led闪烁速度******
*
*	param：USART_ReceiveData
*
*	主函数中while循环调用 LED_Flash(led_num,time);
*	需要设置全局变量 time
*
*/
void USART_Led_Speed_Adjust(uint8_t r_data);

/******字符串控制操作******
*
*	- input
*		- CloseLe+num	
*		- OpenLed+num	
*		- LedFast
*		- LedLow
*		- LedShan+num	
*		- LedNotShan+num	
*/
void USART_Recv_Data_Do(void);
#endif /* __USART_H */
