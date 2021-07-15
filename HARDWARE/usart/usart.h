#ifndef __USART_H
#define __USART_H

#include "stm32f4xx.h"


/*
	RX	PA9
	TX	PA10
*/




//��ʼ��LED����
void USART1_Init(int);
void USART_Send_word(uint16_t);
void USART_Send_words(char *);


/******����led��˸�ٶ�******
*
*	param��USART_ReceiveData
*
*	��������whileѭ������ LED_Flash(led_num,time);
*	��Ҫ����ȫ�ֱ��� time
*
*/
void USART_Led_Speed_Adjust(uint8_t r_data);

/******�ַ������Ʋ���******
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
