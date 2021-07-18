#include "usart.h"
#include "led.h"
#include "delay.h"
//#include <stdio.h>
#include <stdlib.h>
//#include <string.h>
extern int time;	// 更改闪灯速度
extern int speed_falg;	// 闪灯控制标志位
extern int led_speed_num;	// 控制闪哪个灯
extern int led_speed_arr_flag[];	// 有无闪灯的标志
extern int led_arr_flag[];	// 有无开灯的标志

char usart1_r_data_buf[128]={0};	// 接收来自串口1的字符串数组存放区
char usart1_r_data_tmp_buf[128]={0};	// 接收来自串口1的字符串数组存放区中间变量
int usart1_r_data_buf_count=0;	// 接收来自串口1的字符串数组计数值
int usart1_fi=0;	// for用的i
int usart1_fflag=0;
int usart1_led_len=0;



char uart1_buf[128] 		= {0};		//接收来自串口1的字符串的数组存放区
char uart1_temp_buf[128] 	= {0};		//接收来自串口1的字符串的数组存放区，中间值
int  count					=  0 ;		//数据计数值
int  usart1_i				=  0 ;		//for循环用的i数
int  usart1_flag			=  0 ;		//检测是否有字符串进入(开关)
int  usart1_delay_val		= 500;		//delay函数的参数，改变延时数

int  usart1_ps_flag			=  0 ;		//指纹功能控制标志

//// 重定向printf函数，输出至串口1中
//#if 1
//#pragma import(__use_no_semihosting)	// 可以关闭半主机模式
//struct __FILE 
//{ 
//	int handle; 
//}; 

//FILE __stdout;       
// 
//int _sys_exit(int x)  				// 避免半主机模式
//{ 
//	x = x;
//	return 0;
//} 

//int fputc(int ch, FILE *f)
//{
//	USART_SendData(USART1, ch);
//	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
//	return ch;
//}
//#endif


//0、重定向printf函数，输出内容至串口1中
#if 1
#pragma import(__use_no_semihosting) //可以关闭半主机模式
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
 
int _sys_exit(int x)  				//避免半主机模式
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
	// GPIO配置信息结构体
	GPIO_InitTypeDef GPIO_InitStruct;
	USART_InitTypeDef USART_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	
	// 使能时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);	// 使能串口时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);	// 使能GPIO硬件时钟
	
	// GPIO复用映射设置
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1);
	
	// 配置GPIO结构体
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;	// 推挽输出
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;	// 上拉电阻
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_9|GPIO_Pin_10;	// 对应IO口
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	
	// 配置USART结构体
	USART_InitStruct.USART_BaudRate=baud;	// 波特率
	USART_InitStruct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;	// 无硬件数据流控制
	USART_InitStruct.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART_InitStruct.USART_Parity=USART_Parity_No;	// 奇偶效验
	USART_InitStruct.USART_StopBits=USART_StopBits_1;	// 1个停止位
	USART_InitStruct.USART_WordLength=USART_WordLength_8b;	// 8bit数据位
	USART_Init(USART1,&USART_InitStruct);
	
	USART_Cmd(USART1,ENABLE);	// 串口使能
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);	// 使能中断
	
	// 配置NVIC结构体
	NVIC_InitStruct.NVIC_IRQChannel=USART1_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStruct);

}

// 终端服务函数
//void USART1_IRQHandler(void)
//{	
//	//uint8_t r_data=0;	// 接收到的数据
//	//USART_ClearITPendingBit
//	if(USART_GetITStatus(USART1,USART_IT_RXNE)==1)	// 判断发送标志位是否为1
//	{	
//		usart1_r_data_tmp_buf[usart1_r_data_buf_count++]=USART_ReceiveData(USART1);	// 接收数据到数组	eg:'ligoudan\r\n'		
//		usart1_led_len=usart1_r_data_buf_count;
//		if(usart1_r_data_tmp_buf[usart1_r_data_buf_count-1]=='@' && usart1_r_data_tmp_buf[usart1_r_data_buf_count-2]=='@')	// 判断发字符串是否发送完毕
//		{
//			for(usart1_fi=0;usart1_fi<usart1_r_data_buf_count-2;usart1_fi++)
//			{
//				usart1_r_data_buf[usart1_fi]=usart1_r_data_tmp_buf[usart1_fi];
//			}
//			usart1_fflag=1;
//			memset(usart1_r_data_tmp_buf,0,sizeof(usart1_r_data_tmp_buf));	// 清空字符串
//			usart1_r_data_buf_count=0;	// 计数值清零
//		}
//		
//		//USART_Led_Speed_Adjust(r_data);	// 闪灯速度改变
//		USART_ClearITPendingBit(USART1,USART_IT_RXNE);	// 清除串口中断标志位
//	}
//}
void USART1_IRQHandler(void)
{
		
	//三、发送字符命令控制指纹功能
	uint16_t r_data = 0;								//0、定义一个接收值变量
	if(USART_GetITStatus(USART1, USART_IT_RXNE) == 1)	//1、判断中断标志位是否为1
	{
		//USART_SendData();								//2、发送数据
		r_data = USART_ReceiveData(USART1);				//3、接收数据
		if(r_data == '1')
		{
			usart1_ps_flag = 1;
		}
		if(r_data == '2')
		{
			usart1_ps_flag = 2;
		}	
		if(r_data == '3')
		{
			usart1_ps_flag = 3;
		}
		printf("usart1_ps_flag == %d\r\n", usart1_ps_flag);
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);	//8、清楚串口中断标志位，清0
	}	
}

// 发送单个字符
void USART_Send_word(uint16_t word)
{
	USART_SendData(USART1,word);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
}

/*
// 发送字符串
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

// 调节灯闪烁速度
void USART_Led_Speed_Adjust(uint8_t r_data)
{
	r_data=USART_ReceiveData(USART1);	// 接收数据
	if(r_data=='a')
	{
		LED_Speed(1);	// 加延时时间 减速度
		USART_Send_word(r_data);	// 发送回信息
		printf(":%dms\n",time);
		
	}else if(r_data=='b'){
		LED_Speed(0);	// 减延时时间 加速度
		USART_Send_word(r_data);	// 发送回信息
		printf(":%dms\n",time);
	}
}

// 串口操作开发板
void USART_Recv_Data_Do(void)
{	
	int led_num;
	if(strncmp(usart1_r_data_buf,"OpenLed",7)==0)	// 开启LED2	比较串口发送过来的字符串是否相等
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
	if(strncmp(usart1_r_data_buf,"CloseLed",8)==0&&led_arr_flag[led_speed_num-1]==0)	// 关闭LED2
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
	if(strncmp(usart1_r_data_buf,"LedFast",7)==0)	// 加速闪烁
	{
		LED_Speed(0);	// 减延时时间 加速度
		printf("LedSpeed:%dms\n",time);
	}
	if(strncmp(usart1_r_data_buf,"LedLow",6)==0)	// 减慢闪烁
	{
		LED_Speed(1);	// 加延时时间 减速度
		printf("LedSpeed:%dms\n",time);
	}
	if(strncmp(usart1_r_data_buf,"LedShan",7)==0)	// 开启闪烁
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
	if(strncmp(usart1_r_data_buf,"LedNotShan",10)==0)	// 关闭闪烁
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
	if(usart1_fflag)
	{
		memset(usart1_r_data_buf,0,sizeof(usart1_r_data_tmp_buf));	// 清空字符串
		usart1_fflag=0;
	}
}
