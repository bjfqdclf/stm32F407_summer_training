#ifndef __DELAY_H
#define __DELAY_H

#include "stm32f4xx.h"





//1���Լ�д����ʱ����
void delay_ms_me(int ms_time);
//2��ϵͳ��ʱ��΢�
void delay_us(uint32_t nus); 
//3��ϵͳ��ʱ�����뼶
void delay_ms(uint32_t nms); 


#endif /* __DELAY_H */
