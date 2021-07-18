#include "dht11.h"
#include "usart.h"
#include "oled.h"
//1、初始化dhtll函数
void DHT11_Init(void)
{
	//0、GPIO配置信息结构
	GPIO_InitTypeDef   GPIO_InitStructrue;	
	
	//1、使能硬件时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
	
	//2、初始化GPIO的引脚信息			
	GPIO_InitStructrue.GPIO_Pin		=	GPIO_Pin_9;					//第9个引脚
	GPIO_InitStructrue.GPIO_Mode	=	GPIO_Mode_OUT;				//输出模式
	GPIO_InitStructrue.GPIO_OType	=	GPIO_OType_PP;				//推挽模式输出
	GPIO_InitStructrue.GPIO_PuPd	=	GPIO_PuPd_NOPULL;			//不用拉
	GPIO_InitStructrue.GPIO_Speed	=	GPIO_High_Speed;			//高性能模式
	GPIO_Init(GPIOG, &GPIO_InitStructrue);							//初始化GPIO的引脚信息
		
	//3、设置引脚高低电平值
	GPIO_SetBits(GPIOG, GPIO_Pin_9);								//设置高电平,由温湿度时序图得出，一开始位高电平
}


//2、温湿度转换模式(输入、输出)
void DHT11_Convert_Mode(GPIOMode_TypeDef GPIO_Mode)
{
	//0、GPIO配置信息结构
	GPIO_InitTypeDef   GPIO_InitStructrue;	
	
	//2、初始化GPIO的引脚信息			
	GPIO_InitStructrue.GPIO_Pin		=	GPIO_Pin_9;					//第9个引脚
	GPIO_InitStructrue.GPIO_PuPd	=	GPIO_PuPd_NOPULL;			//不用拉
	
	if(GPIO_Mode == GPIO_Mode_OUT)									//输出模式
	{
		GPIO_InitStructrue.GPIO_Mode	=	GPIO_Mode_OUT;			//输出模式
		GPIO_InitStructrue.GPIO_OType	=	GPIO_OType_PP;			//推挽模式输出
		GPIO_InitStructrue.GPIO_Speed	=	GPIO_High_Speed;		//高性能模式
	}
	else
	{
		GPIO_InitStructrue.GPIO_Mode	=	GPIO_Mode_IN;			//输入模式		
	}
	GPIO_Init(GPIOG, &GPIO_InitStructrue);							//初始化GPIO的引脚信息
	
}

//3、获取温湿度数据
int DHT11_Get_Data(char *buf)
{
	int 		T 			= 0		;		//计数值(延时值)
	int 		i,j					;		//for循环时候用的
	uint32_t 	sum_data			;		//前四个数据的和
	uint8_t		d			= 0		;		//移位数据的中间值
	
	//============A、单片机发送信号启动温湿度，让其工作=================//
	//a、PG9引脚模式置为输出模式
	DHT11_Convert_Mode(GPIO_Mode_OUT);
	
	//b、PG9置为低电平
	GPIO_ResetBits(GPIOG, GPIO_Pin_9);
	
	//c、延时20ms
	delay_ms(20);
	
	//d、PG9置为高电平
	GPIO_SetBits(GPIOG, GPIO_Pin_9);
	
	//e、延时30us
	delay_us(30);
	

	
	//============B、温湿度模块接收到命令，开始工作，并和单片机说了一ok==============//
	//a、PG9引脚模式置为输入模式
	DHT11_Convert_Mode(GPIO_Mode_IN);
	
	//b、等待低电平的到来
	while(GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_9) == 1);

	//c、检测低电平持续时间
	T = 0;
	while(GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_9) == 0)
	{
		delay_us(1);
		T++;
		if(T >= 100)		//计数其延时值，看其是否超时
			return -1;
	}

	//d、检测高电平持续时间
	T = 0;
	while(GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_9) == 1)
	{
		delay_us(1);
		T++;
		if(T >= 100)		//计数其延时值，看其是否超时
			return -2;
	}

	//============C、单片机获取温湿度的40个数据(判断40个数据到底是1还是0)//============//
	
	//a、开始获取40个数据
	for(i=0; i<5; i++)
	{
		d = 0;
		for(j=0; j<8; j++)
		{
			//1、等待高电平的出现
			while(GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_9) == 0);
			//2、延时40us
			delay_us(40);
			//3、判断PG9引脚是不是1
			if(GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_9) == 1)
			{
				d |=  1<<(7-j);											//通过移位组成数据
				while(GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_9)==1);		//等待低电平出现
			}
			
		}
		
		buf[i] =  d;	//通过移位组成数据
	}
	
	//b、将前四个数据加在一起，赋给一个变量
	sum_data = buf[0]+buf[1]+buf[2]+buf[3]; 
	
	//c、用校验数据buf[4]，去和前四个字节数据之和的末8位来比)
	if(buf[4] != (sum_data&0xff))
	{
		return -3;
	}
	
	//d、延时80us
	delay_us(80);
	
	return 0;
}


void DTH11_Get_Print(void)
{
		//获取温湿度模块数据
	char dht11_buf[5]={0};			//温湿度模块数据存储数组
	int dht11_ret=0;			//温湿度返回值
	int temp1,dir1,temp2,dir2;
	dht11_ret = DHT11_Get_Data(dht11_buf);
	temp1=dht11_buf[2];
	dir1=dht11_buf[0];
	temp2=dht11_buf[3];
	dir2=dht11_buf[1];
	if(dht11_ret == 0)
	{
		printf("temp：%d.%d, humi：%d.%d\r\n", dht11_buf[2], dht11_buf[3], dht11_buf[0], dht11_buf[1]);
		OLED_Clear();
		OLED_ShowCHinese(28,0,3);	//开，3
		OLED_ShowCHinese(46,0,4);	//机，4
		OLED_ShowCHinese(64,0,5);	//状，5
		OLED_ShowCHinese(82,0,6);	//态，6
		OLED_ShowChar(100,0,'***',3);

		
		OLED_ShowCHinese(14,3,0);	//温，0
		OLED_ShowCHinese(32,3,1);	//度，1
		OLED_ShowNum(55,3,temp1,2,16);	// 数字

		OLED_ShowNum(75,4,temp2,1,10);	// 数字
		OLED_ShowCHinese(90,3,1);	//度，1
		
		OLED_ShowCHinese(14,5,2);	//湿，2
		OLED_ShowCHinese(32,5,1);	//度，1
		OLED_ShowNum(55,5,dir1,2,16);	// 数字

		OLED_ShowNum(75,6,dir2,1,10);	// 数字
		OLED_ShowString(90,5,"%SH",16);
	}

}







