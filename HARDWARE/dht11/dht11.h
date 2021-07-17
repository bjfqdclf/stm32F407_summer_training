#ifndef __DHT11_H
#define __DHT11_H

#include "stm32f4xx.h"
#include "delay.h"


// 1����ʼ��dhtll����
void DHT11_Init(void);

// 2����ʪ��ת��ģʽ(���롢���)
void DHT11_Convert_Mode(GPIOMode_TypeDef GPIO_Mode);

// 3����ȡ��ʪ������
int DHT11_Get_Data(char *buf);

// 4����ȡ��ʪ������,����ӡ
void DTH11_Get_Print(void);

#endif /* __DHT11_H */
