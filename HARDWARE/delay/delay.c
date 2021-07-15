#include "delay.h"


//1、自己写的延时函数
void delay_ms_me(int ms_time)
{
	int ms_i = 0;
	while(ms_time--)
	{
		ms_i = 12000;
		while(ms_i--);
	}
}

//系统延时函数
//2、微妙级
void delay_us(uint32_t nus)
{

	SysTick->CTRL = 0; 									// Disable SysTick，关闭系统时钟后才能设置寄存器
	SysTick->LOAD = SystemCoreClock/8/1000000*nus; 		//设置计数值
	SysTick->VAL = 0; 									// Clear current value as well as count flag，清空当前值还有标志位
	SysTick->CTRL = 1; 									// Enable SysTick timer with processor clock，使能系统定时器开始计算，且使用8分频的时钟
	while ((SysTick->CTRL & 0x00010000)==0);			// Wait until count flag is set，等待计数完成
	SysTick->CTRL = 0; 									// Disable SysTick，关闭系统时钟代表说不再进行定时计数	

}

//3、毫秒级
void delay_ms(uint32_t nms)
{
	while(nms --)
	{
		SysTick->CTRL = 0; 								// Disable SysTick，关闭系统时钟后才能设置寄存器
		SysTick->LOAD = SystemCoreClock/8/1000; 		// 设置计数值
		SysTick->VAL = 0; 								// Clear current value as well as count flag，清空当前值还有标志位
		SysTick->CTRL = 1; 								// Enable SysTick timer with processor clock，使能系统定时器开始计算，且使用8分频的时钟
		while ((SysTick->CTRL & 0x00010000)==0);		// Wait until count flag is set，等待计数完成
		SysTick->CTRL = 0; 								// Disable SysTick，关闭系统时钟代表说不再进行定时计数	
	
	}

}
