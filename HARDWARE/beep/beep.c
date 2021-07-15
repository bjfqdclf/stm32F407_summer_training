#include "beep.h"
#include "delay.h"
void BEEP_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	//ʹ��ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF|RCC_AHB1Periph_GPIOE, ENABLE);	// ʹ��ʱ��
	
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_8;	// ����
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_OUT;	// ģʽ
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;	// ����ģʽ
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_NOPULL;	// ����
	GPIO_InitStruct.GPIO_Speed=GPIO_High_Speed;	// ����
	
	
	// ��ʼ��������Ϣ����������Ϣд���Ĵ�����
	GPIO_Init(GPIOF,&GPIO_InitStruct);
		
	GPIO_ResetBits(GPIOF,GPIO_Pin_8);	// ���õ͵�ƽ	BEEP����

}


//��������
void BEEP_Open(void)
{
	GPIO_SetBits(GPIOF,GPIO_Pin_8);
}

//����������
void BEEP_Close(void)
{
	GPIO_ResetBits(GPIOF,GPIO_Pin_8);
}

//��������̶�ms����
void BEEP_Ring(int i)
{
	BEEP_Open();
	delay_ms(i);
	BEEP_Close();
}
