#include "usart.h"
#include "led.h"
#include "delay.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
extern int time;	// ���������ٶ�
extern int speed_falg;	// ���ƿ��Ʊ�־λ
extern int led_speed_num;	// �������ĸ���
extern int led_speed_arr_flag[];	// �������Ƶı�־
extern int led_arr_flag[];	// ���޿��Ƶı�־

char usart1_r_data_buf[128]={0};	// �������Դ���1���ַ�����������
char usart1_r_data_tmp_buf[128]={0};	// �������Դ���1���ַ������������м����
int usart1_r_data_buf_count=0;	// �������Դ���1���ַ����������ֵ
int usart1_i=0;	// for�õ�i
int usart1_flag=0;
int usart1_led_len=0;

// �ض���printf���������������1��
#if 1
#pragma import(__use_no_semihosting)	// ���Թرհ�����ģʽ
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
 
int _sys_exit(int x)  				// ���������ģʽ
{ 
	x = x;
	return 0;
} 

int fputc(int ch, FILE *f)
{
	USART_SendData(USART1, ch);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
	return ch;
}
#endif

void USART1_Init(int baud)
{
	// GPIO������Ϣ�ṹ��
	GPIO_InitTypeDef GPIO_InitStruct;
	USART_InitTypeDef USART_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	
	// ʹ��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);	// ʹ�ܴ���ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);	// ʹ��GPIOӲ��ʱ��
	
	// GPIO����ӳ������
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1);
	
	// ����GPIO�ṹ��
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;	// �������
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;	// ��������
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_9|GPIO_Pin_10;	// ��ӦIO��
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	
	// ����USART�ṹ��
	USART_InitStruct.USART_BaudRate=baud;	// ������
	USART_InitStruct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;	// ��Ӳ������������
	USART_InitStruct.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART_InitStruct.USART_Parity=USART_Parity_No;	// ��żЧ��
	USART_InitStruct.USART_StopBits=USART_StopBits_1;	// 1��ֹͣλ
	USART_InitStruct.USART_WordLength=USART_WordLength_8b;	// 8bit����λ
	USART_Init(USART1,&USART_InitStruct);
	
	USART_Cmd(USART1,ENABLE);	// ����ʹ��
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);	// ʹ���ж�
	
	// ����NVIC�ṹ��
	NVIC_InitStruct.NVIC_IRQChannel=USART1_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStruct);

}

// �ն˷�����
void USART1_IRQHandler(void)
{	
	//uint8_t r_data=0;	// ���յ�������
	//USART_ClearITPendingBit
	if(USART_GetITStatus(USART1,USART_IT_RXNE)==1)	// �жϷ��ͱ�־λ�Ƿ�Ϊ1
	{	
		usart1_r_data_tmp_buf[usart1_r_data_buf_count++]=USART_ReceiveData(USART1);	// �������ݵ�����	eg:'ligoudan\r\n'		
		usart1_led_len=usart1_r_data_buf_count;
		if(usart1_r_data_tmp_buf[usart1_r_data_buf_count-1]=='@' && usart1_r_data_tmp_buf[usart1_r_data_buf_count-2]=='@')	// �жϷ��ַ����Ƿ������
		{
			for(usart1_i=0;usart1_i<usart1_r_data_buf_count-2;usart1_i++)
			{
				usart1_r_data_buf[usart1_i]=usart1_r_data_tmp_buf[usart1_i];
			}
			usart1_flag=1;
			memset(usart1_r_data_tmp_buf,0,sizeof(usart1_r_data_tmp_buf));	// ����ַ���
			usart1_r_data_buf_count=0;	// ����ֵ����
		}
		
		//USART_Led_Speed_Adjust(r_data);	// �����ٶȸı�
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);	// ��������жϱ�־λ
	}
}


// ���͵����ַ�
void USART_Send_word(uint16_t word)
{
	USART_SendData(USART1,word);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
}

/*
// �����ַ���
void USART_Send_words(uint8_t *p)
{
	while((*p)!='\0')
	{
		USART_Send_word(*p);
		p++;
	}
}
*/

void USART_Send_words(char *str)
{
	 unsigned int k=0;
	do
	{
		USART_Send_word(*(str+k));
		k++;
		
	}while(*(str+k)!='\0');
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
}

// ���ڵ���˸�ٶ�
void USART_Led_Speed_Adjust(uint8_t r_data)
{
	r_data=USART_ReceiveData(USART1);	// ��������
	if(r_data=='a')
	{
		LED_Speed(1);	// ����ʱʱ�� ���ٶ�
		USART_Send_word(r_data);	// ���ͻ���Ϣ
		printf(":%dms\n",time);
		
	}else if(r_data=='b'){
		LED_Speed(0);	// ����ʱʱ�� ���ٶ�
		USART_Send_word(r_data);	// ���ͻ���Ϣ
		printf(":%dms\n",time);
	}
}

// ���ڲ���������
void USART_Recv_Data_Do(void)
{	
	int led_num;
	if(strncmp(usart1_r_data_buf,"OpenLed",7)==0)	// ����LED2	�Ƚϴ��ڷ��͹������ַ����Ƿ����
	{	
		
		led_num=atoi(&usart1_r_data_buf[usart1_led_len-3]);
		if(led_arr_flag[led_num-1]==0 && led_arr_flag[led_speed_num-1]==0)
		{
			LED_Open(led_num);
			led_arr_flag[led_num-1]=1;
			printf("LED%d Open\n",led_num);
		}else{
			printf("DO ERRO\n");
		}
	}
	if(strncmp(usart1_r_data_buf,"CloseLed",8)==0&&led_arr_flag[led_speed_num-1]==0)	// �ر�LED2
	{	
		led_num=atoi(&usart1_r_data_buf[usart1_led_len-3]);
		if(led_arr_flag[led_num-1]==1)
		{
			LED_Close(led_num);
			led_arr_flag[led_num-1]=1;
			printf("LED%d Close\n",led_num);
		}else{
			printf("DO ERRO\n");
		}
	}
	if(strncmp(usart1_r_data_buf,"LedFast",7)==0)	// ������˸
	{
		LED_Speed(0);	// ����ʱʱ�� ���ٶ�
		printf("LedSpeed:%dms\n",time);
	}
	if(strncmp(usart1_r_data_buf,"LedLow",6)==0)	// ������˸
	{
		LED_Speed(1);	// ����ʱʱ�� ���ٶ�
		printf("LedSpeed:%dms\n",time);
	}
	if(strncmp(usart1_r_data_buf,"LedShan",7)==0)	// ������˸
	{
		speed_falg=1;
		led_speed_arr_flag[led_speed_num-1]=0;
		led_speed_num=atoi(&usart1_r_data_buf[usart1_led_len-3]);
		if(led_arr_flag[led_speed_num-1]==0)
		{
			led_speed_arr_flag[led_speed_num-1]=1;
			printf("Led%d Shaning...\n",led_speed_num);
		}else{
			printf("DO ERRO\n");
		}
	}
	if(strncmp(usart1_r_data_buf,"LedNotShan",10)==0)	// �ر���˸
	{
		speed_falg=0;
		led_speed_arr_flag[led_speed_num-1]=0;
		if(led_speed_arr_flag[led_speed_num-1]==1)
		{
			printf("LedSpeed:%dms\n",time);
			printf("Led%d Not Shaning...\n",led_speed_num);
		}else{
			printf("DO ERRO\n");
		}
	}
	if(usart1_flag)
	{
		memset(usart1_r_data_buf,0,sizeof(usart1_r_data_tmp_buf));	// ����ַ���
		usart1_flag=0;
	}
}
