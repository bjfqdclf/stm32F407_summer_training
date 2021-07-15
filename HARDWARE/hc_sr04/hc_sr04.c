#include "hc_sr04.h"
#include "led.h"
#include "key.h"
#include "delay.h"
#include <stdio.h>
extern int time;	// 更改闪灯速度
int level=1;
void HC_SR04_Init(void)	
{
	//0、GPIO配置信息结构
	GPIO_InitTypeDef   GPIO_InitStructrue;	
	
	//1、使能硬件时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);

	//2、初始化GPIO的引脚信息			
	GPIO_InitStructrue.GPIO_Pin		=	GPIO_Pin_6;					//第6个引脚
	GPIO_InitStructrue.GPIO_Mode	=	GPIO_Mode_OUT;				//输出模式
	GPIO_InitStructrue.GPIO_OType	=	GPIO_OType_PP;				//推挽模式输出
	GPIO_InitStructrue.GPIO_PuPd	=	GPIO_PuPd_NOPULL;			//不用拉
	GPIO_InitStructrue.GPIO_Speed	=	GPIO_High_Speed;			//高性能模式
	GPIO_Init(GPIOB, &GPIO_InitStructrue);							//初始化GPIO的引脚信息

	
	GPIO_InitStructrue.GPIO_Pin		=	GPIO_Pin_6;					//第6个引脚
	GPIO_InitStructrue.GPIO_Mode	=	GPIO_Mode_IN;				//输出模式
	//GPIO_InitStructrue.GPIO_OType	=	GPIO_OType_PP;				//推挽模式输出
	GPIO_InitStructrue.GPIO_PuPd	=	GPIO_PuPd_NOPULL;			//不用拉
	GPIO_InitStructrue.GPIO_Speed	=	GPIO_High_Speed;			//高性能模式
	GPIO_Init(GPIOE, &GPIO_InitStructrue);							
	
	
	//3、设置引脚高低电平值
	GPIO_ResetBits(GPIOB, GPIO_Pin_6);								//设置低电平,一开始的时序图表明，应该为低电平
	GPIO_ResetBits(GPIOE, GPIO_Pin_6);								//设置低电平,一开始的时序图表明，应该为低电平
	
}


//2、获取超声波的距离
float HC_SR04_Get_Distant(void)
{
	float count=0;											
	
	//一、PB6(TRIG引脚)										//一、发送一个波形，让超声波工作
	//1、PB6引脚置为高电平
	GPIO_SetBits(GPIOB, GPIO_Pin_6);
	
	//2、延时15us
	delay_us(15);
	
	//3、PB6引脚置为低电平
	GPIO_ResetBits(GPIOB, GPIO_Pin_6);
		
	//二、PE6(ECHO引脚)										//二、获取超声波的距离
	//1、等待PE6引脚高电平出现								//1、发波
	while(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_6) == 0);
	
	//2、算出其高电平的持续时间
	while(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_6) == 1)	//2、当while循环退出时，收波
	{
		delay_us(9);
		count++;											//3、算出其究竟有多少个8.8us
	}
	//3、计算出(来回时间/2)的时间
	count = count/2;	
	
	//4、返回超声波的距离
	
	return 3.3*count;

	
}


void HC_SR04_Print(void)
{
	int ultrasonic_distant;
	ultrasonic_distant = HC_SR04_Get_Distant();
	if(ultrasonic_distant>20 && ultrasonic_distant<4000)
	{
		printf("distant is %dmm\r\n", ultrasonic_distant);
	}
	delay_ms(500);
}



// 雷达功能
void HC_SR04_Ladar(void)
{
	int ultrasonic_distant;
	ultrasonic_distant = HC_SR04_Get_Distant();
	if(ultrasonic_distant>20 && ultrasonic_distant<4000)
	{
		time=ultrasonic_distant/level;	
		printf("distant is %dmm\r\n", ultrasonic_distant);
	}
	delay_ms(100);
}

// 三级可调灵敏度
void HC_SR04_Ladar_Level(void)
{
	LED_Close(level+1);
	if(level!=3)
	{
		level++;
	}else{
		level=1;
	}
	LED_Open(level+1);
	//printf("Level:%d\n",level);
}

void HC_SR04_Ladar_Open(void)
{
	if(KEY_Scan()==1)
	{
		while(1)
		{
			
			LED_BEEP_Flash(3,time);
			HC_SR04_Ladar();
			if(KEY_Check(2)){
				break;
			}
			if(KEY_Check(3)){
				HC_SR04_Ladar_Level();
				while(KEY_Check(3));
			}
		}
	}else if(KEY_Scan()==3){
		HC_SR04_Ladar_Level();
		while(KEY_Check(3));
	}

}