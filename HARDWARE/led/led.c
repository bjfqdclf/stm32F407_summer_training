#include "led.h"
#include "beep.h"
#include "delay.h"
#include "usart.h"
extern int time;	// 更改闪灯速度
extern int speed_falg;	// 闪灯控制标志位
extern int led_speed_num;	// 控制闪哪个灯
extern int led_speed_arr_flag[];	// 有无闪灯的标志
extern int led_arr_flag[];	// 有无开灯的标志
// 函数跳转前要库文件，要编译
// 跳转时不是go就是find，不然就在你左右


void LED_Init(void)
{
	// GPIO配置信息结构体
	GPIO_InitTypeDef GPIO_InitStruct;
	
	// 使能时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF|RCC_AHB1Periph_GPIOE, ENABLE);	// 使能时钟
	
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_9|GPIO_Pin_10;	// 引脚
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_OUT;	// 模式
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;	// 推挽模式
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_NOPULL;	// 不拉
	GPIO_InitStruct.GPIO_Speed=GPIO_High_Speed;	// 高速
	
	
	// 初始化引脚信息，将上述信息写到寄存器中
	GPIO_Init(GPIOF,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_13|GPIO_Pin_14;
	GPIO_Init(GPIOE,&GPIO_InitStruct);
	
	// 设置引脚的高低电平值
	GPIO_SetBits(GPIOF,GPIO_Pin_9|GPIO_Pin_10);	// 设置高电平	led灯灭
	GPIO_SetBits(GPIOE,GPIO_Pin_13|GPIO_Pin_14);
	// GPIO_ResetBits(GPIOF,GPIO_Pin_9);	// 设置低电平	led灯亮
	
	
}


// led亮函数
void LED_Open(int i)
{
	switch(i){
		case 1:
				GPIO_ResetBits(GPIOF,GPIO_Pin_9);
			
		break;
		case 2:
				GPIO_ResetBits(GPIOF,GPIO_Pin_10);
			
		break;
		case 3:
				GPIO_ResetBits(GPIOE,GPIO_Pin_13);
			
		break;
		
		case 4:
				GPIO_ResetBits(GPIOE,GPIO_Pin_14);
		break;
		
	}
	
}


// led灭函数
void LED_Close(int i)
{
	switch(i){
		case 1:
				GPIO_SetBits(GPIOF,GPIO_Pin_9);
		break;
		case 2:
				GPIO_SetBits(GPIOF,GPIO_Pin_10);
		break;
		case 3:
				GPIO_SetBits(GPIOE,GPIO_Pin_13);
		break;
		case 4:
				GPIO_SetBits(GPIOE,GPIO_Pin_14);
		break;
		
	}
	
}

// 流水灯
void LED_Water(void)
{
	int i;
	for(i=1;i<=4;i++)
	{
		LED_Open(i);
		delay_ms(200);
		LED_Close(i);
	}

}
// 闪灯
void LED_Flash(int i,int times)
{
	if(speed_falg)
	{
	LED_Open(led_speed_num);
	delay_ms(times);
	LED_Close(led_speed_num);
	delay_ms(times);
	}
}

void LED_BEEP_Flash(int i,int times)
{
	
	//BEEP_Open();
	LED_Open(led_speed_num);
	delay_ms(times);
	LED_Close(led_speed_num);
	//BEEP_Close();
	delay_ms(times);
	
}

// 更改速度
void LED_Speed(int flag)
{	
	
	if(flag)	// flag==1
	{
		time+=10;

	}else{
		if(time!=0)
		{	
			time-=10;
		}
	}
}
