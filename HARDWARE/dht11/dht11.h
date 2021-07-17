#ifndef __DHT11_H
#define __DHT11_H

#include "stm32f4xx.h"
#include "delay.h"


// 1、初始化dhtll函数
void DHT11_Init(void);

// 2、温湿度转换模式(输入、输出)
void DHT11_Convert_Mode(GPIOMode_TypeDef GPIO_Mode);

// 3、获取温湿度数据
int DHT11_Get_Data(char *buf);

// 4、获取温湿度数据,并打印
void DTH11_Get_Print(void);

#endif /* __DHT11_H */
