#include "led.h"
#include "beep.h"
#include "delay.h"
#include "usart.h"
extern int time;	// ���������ٶ�
extern int speed_falg;	// ���ƿ��Ʊ�־λ
extern int led_speed_num;	// �������ĸ���
extern int led_speed_arr_flag[];	// �������Ƶı�־
extern int led_arr_flag[];	// ���޿��Ƶı�־
// ������תǰҪ���ļ���Ҫ����
// ��תʱ����go����find����Ȼ����������


void LED_Init(void)
{
	// GPIO������Ϣ�ṹ��
	GPIO_InitTypeDef GPIO_InitStruct;
	
	// ʹ��ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF|RCC_AHB1Periph_GPIOE, ENABLE);	// ʹ��ʱ��
	
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_9|GPIO_Pin_10;	// ����
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_OUT;	// ģʽ
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;	// ����ģʽ
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_NOPULL;	// ����
	GPIO_InitStruct.GPIO_Speed=GPIO_High_Speed;	// ����
	
	
	// ��ʼ��������Ϣ����������Ϣд���Ĵ�����
	GPIO_Init(GPIOF,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_13|GPIO_Pin_14;
	GPIO_Init(GPIOE,&GPIO_InitStruct);
	
	// �������ŵĸߵ͵�ƽֵ
	GPIO_SetBits(GPIOF,GPIO_Pin_9|GPIO_Pin_10);	// ���øߵ�ƽ	led����
	GPIO_SetBits(GPIOE,GPIO_Pin_13|GPIO_Pin_14);
	// GPIO_ResetBits(GPIOF,GPIO_Pin_9);	// ���õ͵�ƽ	led����
	
	
}


// led������
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


// led����
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

// ��ˮ��
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
// ����
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

// �����ٶ�
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
