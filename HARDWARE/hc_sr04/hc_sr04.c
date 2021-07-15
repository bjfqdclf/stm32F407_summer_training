#include "hc_sr04.h"
#include "led.h"
#include "delay.h"
#include <stdio.h>

void HC_SR04_Init(void)	
{
	//0��GPIO������Ϣ�ṹ
	GPIO_InitTypeDef   GPIO_InitStructrue;	
	
	//1��ʹ��Ӳ��ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);

	//2����ʼ��GPIO��������Ϣ			
	GPIO_InitStructrue.GPIO_Pin		=	GPIO_Pin_6;					//��6������
	GPIO_InitStructrue.GPIO_Mode	=	GPIO_Mode_OUT;				//���ģʽ
	GPIO_InitStructrue.GPIO_OType	=	GPIO_OType_PP;				//����ģʽ���
	GPIO_InitStructrue.GPIO_PuPd	=	GPIO_PuPd_NOPULL;			//������
	GPIO_InitStructrue.GPIO_Speed	=	GPIO_High_Speed;			//������ģʽ
	GPIO_Init(GPIOB, &GPIO_InitStructrue);							//��ʼ��GPIO��������Ϣ

	
	GPIO_InitStructrue.GPIO_Pin		=	GPIO_Pin_6;					//��6������
	GPIO_InitStructrue.GPIO_Mode	=	GPIO_Mode_IN;				//���ģʽ
	//GPIO_InitStructrue.GPIO_OType	=	GPIO_OType_PP;				//����ģʽ���
	GPIO_InitStructrue.GPIO_PuPd	=	GPIO_PuPd_NOPULL;			//������
	GPIO_InitStructrue.GPIO_Speed	=	GPIO_High_Speed;			//������ģʽ
	GPIO_Init(GPIOE, &GPIO_InitStructrue);							
	
	
	//3���������Ÿߵ͵�ƽֵ
	GPIO_ResetBits(GPIOB, GPIO_Pin_6);								//���õ͵�ƽ,һ��ʼ��ʱ��ͼ������Ӧ��Ϊ�͵�ƽ
	GPIO_ResetBits(GPIOE, GPIO_Pin_6);								//���õ͵�ƽ,һ��ʼ��ʱ��ͼ������Ӧ��Ϊ�͵�ƽ
	
}


//2����ȡ�������ľ���
float HC_SR04_Get_Distant(void)
{
	float count=0;											
	
	//һ��PB6(TRIG����)										//һ������һ�����Σ��ó���������
	//1��PB6������Ϊ�ߵ�ƽ
	GPIO_SetBits(GPIOB, GPIO_Pin_6);
	
	//2����ʱ15us
	delay_us(15);
	
	//3��PB6������Ϊ�͵�ƽ
	GPIO_ResetBits(GPIOB, GPIO_Pin_6);
		
	//����PE6(ECHO����)										//������ȡ�������ľ���
	//1���ȴ�PE6���Ÿߵ�ƽ����								//1������
	while(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_6) == 0);
	
	//2�������ߵ�ƽ�ĳ���ʱ��
	while(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_6) == 1)	//2����whileѭ���˳�ʱ���ղ�
	{
		delay_us(9);
		count++;											//3������便���ж��ٸ�8.8us
	}
	//3�������(����ʱ��/2)��ʱ��
	count = count/2;	
	
	//4�����س������ľ���
	
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
