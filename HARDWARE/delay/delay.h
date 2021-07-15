#ifndef __DELAY_H
#define __DELAY_H

#include "stm32f4xx.h"





//1、自己写的延时函数
void delay_ms_me(int ms_time);
//2、系统定时器微妙级
void delay_us(uint32_t nus); 
//3、系统定时器毫秒级
void delay_ms(uint32_t nms); 


#endif /* __DELAY_H */
