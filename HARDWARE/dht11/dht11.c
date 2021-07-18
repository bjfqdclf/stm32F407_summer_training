#include "dht11.h"
#include "usart.h"
#include "oled.h"
//1����ʼ��dhtll����
void DHT11_Init(void)
{
	//0��GPIO������Ϣ�ṹ
	GPIO_InitTypeDef   GPIO_InitStructrue;	
	
	//1��ʹ��Ӳ��ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
	
	//2����ʼ��GPIO��������Ϣ			
	GPIO_InitStructrue.GPIO_Pin		=	GPIO_Pin_9;					//��9������
	GPIO_InitStructrue.GPIO_Mode	=	GPIO_Mode_OUT;				//���ģʽ
	GPIO_InitStructrue.GPIO_OType	=	GPIO_OType_PP;				//����ģʽ���
	GPIO_InitStructrue.GPIO_PuPd	=	GPIO_PuPd_NOPULL;			//������
	GPIO_InitStructrue.GPIO_Speed	=	GPIO_High_Speed;			//������ģʽ
	GPIO_Init(GPIOG, &GPIO_InitStructrue);							//��ʼ��GPIO��������Ϣ
		
	//3���������Ÿߵ͵�ƽֵ
	GPIO_SetBits(GPIOG, GPIO_Pin_9);								//���øߵ�ƽ,����ʪ��ʱ��ͼ�ó���һ��ʼλ�ߵ�ƽ
}


//2����ʪ��ת��ģʽ(���롢���)
void DHT11_Convert_Mode(GPIOMode_TypeDef GPIO_Mode)
{
	//0��GPIO������Ϣ�ṹ
	GPIO_InitTypeDef   GPIO_InitStructrue;	
	
	//2����ʼ��GPIO��������Ϣ			
	GPIO_InitStructrue.GPIO_Pin		=	GPIO_Pin_9;					//��9������
	GPIO_InitStructrue.GPIO_PuPd	=	GPIO_PuPd_NOPULL;			//������
	
	if(GPIO_Mode == GPIO_Mode_OUT)									//���ģʽ
	{
		GPIO_InitStructrue.GPIO_Mode	=	GPIO_Mode_OUT;			//���ģʽ
		GPIO_InitStructrue.GPIO_OType	=	GPIO_OType_PP;			//����ģʽ���
		GPIO_InitStructrue.GPIO_Speed	=	GPIO_High_Speed;		//������ģʽ
	}
	else
	{
		GPIO_InitStructrue.GPIO_Mode	=	GPIO_Mode_IN;			//����ģʽ		
	}
	GPIO_Init(GPIOG, &GPIO_InitStructrue);							//��ʼ��GPIO��������Ϣ
	
}

//3����ȡ��ʪ������
int DHT11_Get_Data(char *buf)
{
	int 		T 			= 0		;		//����ֵ(��ʱֵ)
	int 		i,j					;		//forѭ��ʱ���õ�
	uint32_t 	sum_data			;		//ǰ�ĸ����ݵĺ�
	uint8_t		d			= 0		;		//��λ���ݵ��м�ֵ
	
	//============A����Ƭ�������ź�������ʪ�ȣ����乤��=================//
	//a��PG9����ģʽ��Ϊ���ģʽ
	DHT11_Convert_Mode(GPIO_Mode_OUT);
	
	//b��PG9��Ϊ�͵�ƽ
	GPIO_ResetBits(GPIOG, GPIO_Pin_9);
	
	//c����ʱ20ms
	delay_ms(20);
	
	//d��PG9��Ϊ�ߵ�ƽ
	GPIO_SetBits(GPIOG, GPIO_Pin_9);
	
	//e����ʱ30us
	delay_us(30);
	

	
	//============B����ʪ��ģ����յ������ʼ���������͵�Ƭ��˵��һok==============//
	//a��PG9����ģʽ��Ϊ����ģʽ
	DHT11_Convert_Mode(GPIO_Mode_IN);
	
	//b���ȴ��͵�ƽ�ĵ���
	while(GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_9) == 1);

	//c�����͵�ƽ����ʱ��
	T = 0;
	while(GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_9) == 0)
	{
		delay_us(1);
		T++;
		if(T >= 100)		//��������ʱֵ�������Ƿ�ʱ
			return -1;
	}

	//d�����ߵ�ƽ����ʱ��
	T = 0;
	while(GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_9) == 1)
	{
		delay_us(1);
		T++;
		if(T >= 100)		//��������ʱֵ�������Ƿ�ʱ
			return -2;
	}

	//============C����Ƭ����ȡ��ʪ�ȵ�40������(�ж�40�����ݵ�����1����0)//============//
	
	//a����ʼ��ȡ40������
	for(i=0; i<5; i++)
	{
		d = 0;
		for(j=0; j<8; j++)
		{
			//1���ȴ��ߵ�ƽ�ĳ���
			while(GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_9) == 0);
			//2����ʱ40us
			delay_us(40);
			//3���ж�PG9�����ǲ���1
			if(GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_9) == 1)
			{
				d |=  1<<(7-j);											//ͨ����λ�������
				while(GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_9)==1);		//�ȴ��͵�ƽ����
			}
			
		}
		
		buf[i] =  d;	//ͨ����λ�������
	}
	
	//b����ǰ�ĸ����ݼ���һ�𣬸���һ������
	sum_data = buf[0]+buf[1]+buf[2]+buf[3]; 
	
	//c����У������buf[4]��ȥ��ǰ�ĸ��ֽ�����֮�͵�ĩ8λ����)
	if(buf[4] != (sum_data&0xff))
	{
		return -3;
	}
	
	//d����ʱ80us
	delay_us(80);
	
	return 0;
}


void DTH11_Get_Print(void)
{
		//��ȡ��ʪ��ģ������
	char dht11_buf[5]={0};			//��ʪ��ģ�����ݴ洢����
	int dht11_ret=0;			//��ʪ�ȷ���ֵ
	int temp1,dir1,temp2,dir2;
	dht11_ret = DHT11_Get_Data(dht11_buf);
	temp1=dht11_buf[2];
	dir1=dht11_buf[0];
	temp2=dht11_buf[3];
	dir2=dht11_buf[1];
	if(dht11_ret == 0)
	{
		printf("temp��%d.%d, humi��%d.%d\r\n", dht11_buf[2], dht11_buf[3], dht11_buf[0], dht11_buf[1]);
		OLED_Clear();
		OLED_ShowCHinese(28,0,3);	//����3
		OLED_ShowCHinese(46,0,4);	//����4
		OLED_ShowCHinese(64,0,5);	//״��5
		OLED_ShowCHinese(82,0,6);	//̬��6
		OLED_ShowChar(100,0,'***',3);

		
		OLED_ShowCHinese(14,3,0);	//�£�0
		OLED_ShowCHinese(32,3,1);	//�ȣ�1
		OLED_ShowNum(55,3,temp1,2,16);	// ����

		OLED_ShowNum(75,4,temp2,1,10);	// ����
		OLED_ShowCHinese(90,3,1);	//�ȣ�1
		
		OLED_ShowCHinese(14,5,2);	//ʪ��2
		OLED_ShowCHinese(32,5,1);	//�ȣ�1
		OLED_ShowNum(55,5,dir1,2,16);	// ����

		OLED_ShowNum(75,6,dir2,1,10);	// ����
		OLED_ShowString(90,5,"%SH",16);
	}

}







