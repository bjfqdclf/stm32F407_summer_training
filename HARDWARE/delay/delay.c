#include "delay.h"


//1���Լ�д����ʱ����
void delay_ms_me(int ms_time)
{
	int ms_i = 0;
	while(ms_time--)
	{
		ms_i = 12000;
		while(ms_i--);
	}
}

//ϵͳ��ʱ����
//2��΢�
void delay_us(uint32_t nus)
{

	SysTick->CTRL = 0; 									// Disable SysTick���ر�ϵͳʱ�Ӻ�������üĴ���
	SysTick->LOAD = SystemCoreClock/8/1000000*nus; 		//���ü���ֵ
	SysTick->VAL = 0; 									// Clear current value as well as count flag����յ�ǰֵ���б�־λ
	SysTick->CTRL = 1; 									// Enable SysTick timer with processor clock��ʹ��ϵͳ��ʱ����ʼ���㣬��ʹ��8��Ƶ��ʱ��
	while ((SysTick->CTRL & 0x00010000)==0);			// Wait until count flag is set���ȴ��������
	SysTick->CTRL = 0; 									// Disable SysTick���ر�ϵͳʱ�Ӵ���˵���ٽ��ж�ʱ����	

}

//3�����뼶
void delay_ms(uint32_t nms)
{
	while(nms --)
	{
		SysTick->CTRL = 0; 								// Disable SysTick���ر�ϵͳʱ�Ӻ�������üĴ���
		SysTick->LOAD = SystemCoreClock/8/1000; 		// ���ü���ֵ
		SysTick->VAL = 0; 								// Clear current value as well as count flag����յ�ǰֵ���б�־λ
		SysTick->CTRL = 1; 								// Enable SysTick timer with processor clock��ʹ��ϵͳ��ʱ����ʼ���㣬��ʹ��8��Ƶ��ʱ��
		while ((SysTick->CTRL & 0x00010000)==0);		// Wait until count flag is set���ȴ��������
		SysTick->CTRL = 0; 								// Disable SysTick���ر�ϵͳʱ�Ӵ���˵���ٽ��ж�ʱ����	
	
	}

}
