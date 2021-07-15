#include "beep.h"
#include "delay.h"
void BEEP_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	//使能时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF|RCC_AHB1Periph_GPIOE, ENABLE);	// 使能时钟
	
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_8;	// 引脚
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_OUT;	// 模式
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;	// 推挽模式
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_NOPULL;	// 不拉
	GPIO_InitStruct.GPIO_Speed=GPIO_High_Speed;	// 高速
	
	
	// 初始化引脚信息，将上述信息写到寄存器中
	GPIO_Init(GPIOF,&GPIO_InitStruct);
		
	GPIO_ResetBits(GPIOF,GPIO_Pin_8);	// 设置低电平	BEEP不响

}


//蜂鸣器响
void BEEP_Open(void)
{
	GPIO_SetBits(GPIOF,GPIO_Pin_8);
}

//蜂鸣器不响
void BEEP_Close(void)
{
	GPIO_ResetBits(GPIOF,GPIO_Pin_8);
}

//蜂鸣器响固定ms秒数
void BEEP_Ring(int i)
{
	BEEP_Open();
	delay_ms(i);
	BEEP_Close();
}
