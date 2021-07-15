#include "key.h"
#include "delay.h"
#include "led.h"
#include "beep.h"
/*
	key0	PA0
	key1	PE2
	key2	PE3
	key3	PE4
*/
void KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	//ʹ��ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOE, ENABLE);	// ʹ��ʱ��
	
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;	// ����
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN;	// ģʽ

	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_NOPULL;	// ����
	GPIO_InitStruct.GPIO_Speed=GPIO_High_Speed;	// ����
	
	// ��ʼ��������Ϣ����������Ϣд���Ĵ�����
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;
	GPIO_Init(GPIOE,&GPIO_InitStruct);
	

}

//������ѯ
int KEY_Check(int i)
{
		switch(i){
		case 1:
			return !(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0));

		case 2:
			return !(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2));

		case 3:
			return !(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3));

		case 4:
			return !(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4));
		
		default:
		break;
	}
	return 0;
}

//����ɨ��
int KEY_Scan(void)
{	
	while(KEY_Check(1)==0&&KEY_Check(2)==0&&KEY_Check(3)==0&&KEY_Check(4)==0);//�ȴ���������
	if(KEY_Check(1)==1||KEY_Check(2)==1||KEY_Check(3)==1||KEY_Check(4)==1)
	{
		if(KEY_Check(1)==1){
			delay_ms(20);
			while(KEY_Check(1)==1);	// �ȴ������ͷ�
			delay_ms(20);
			BEEP_Ring(100);
			return 1;
		}
		else if(KEY_Check(2)==1){
			delay_ms(20);
			while(KEY_Check(2)==1);	// �ȴ������ͷ�
			delay_ms(20);
			BEEP_Ring(100);
			return 2;
		}
		else if(KEY_Check(3)==1){
			delay_ms(20);
			while(KEY_Check(3)==1);	// �ȴ������ͷ�
			delay_ms(20);
			BEEP_Ring(100);
			return 3;
		}
		else if(KEY_Check(4)==1){
			delay_ms(20);
			while(KEY_Check(4)==1);	// �ȴ������ͷ�
			delay_ms(20);
			BEEP_Ring(100);
			return 4;
		}
	}
	return 0;
}

//��������
int KEY_Password(void)
{
	int password[10]={2,3,1,3,2};	// �洢����
	int flag=5;	// ����λ��
	
	int input_pwd[10]={0};	// ��������
	int key_i=0;	// �������ֵ
	int key_input_num;	// ��������
	int i=0;
	
	
	while(1)
	{	
		key_input_num=KEY_Scan();
		if(key_input_num==4|key_i==flag)//�ж��Ƿ���ȷ�ϣ���������������λ��
		{	
			
			if(key_input_num!=4)	// ���û�а���ȷ�ϣ�һֱ�ȴ�����ȷ��
			{
				while(KEY_Scan()!=4);
			}
			
			for(i=0;i<=flag;i++)	// �ж������Ƿ���ȷ
			{
				if(password[i]!=input_pwd[i])
				{
					return 0;	// �������
				}
			}
			return 1;
		}
		else
		{
			input_pwd[key_i]=key_input_num;	// ������İ�����������
			key_i++;
		}	

	}
}
