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
	
	//使能时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOE, ENABLE);	// 使能时钟
	
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;	// 引脚
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN;	// 模式

	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_NOPULL;	// 不拉
	GPIO_InitStruct.GPIO_Speed=GPIO_High_Speed;	// 高速
	
	// 初始化引脚信息，将上述信息写到寄存器中
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;
	GPIO_Init(GPIOE,&GPIO_InitStruct);
	

}

//按键查询
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

//按键扫描
int KEY_Scan(void)
{	
	while(KEY_Check(1)==0&&KEY_Check(2)==0&&KEY_Check(3)==0&&KEY_Check(4)==0);//等待按键按下
	if(KEY_Check(1)==1||KEY_Check(2)==1||KEY_Check(3)==1||KEY_Check(4)==1)
	{
		if(KEY_Check(1)==1){
			delay_ms(20);
			while(KEY_Check(1)==1);	// 等待按键释放
			delay_ms(20);
			//BEEP_Ring(100);
			return 1;
		}
		else if(KEY_Check(2)==1){
			delay_ms(20);
			while(KEY_Check(2)==1);	// 等待按键释放
			delay_ms(20);
			//BEEP_Ring(100);
			return 2;
		}
		else if(KEY_Check(3)==1){
			delay_ms(20);
			while(KEY_Check(3)==1);	// 等待按键释放
			delay_ms(20);
			BEEP_Ring(100);
			return 3;
		}
		else if(KEY_Check(4)==1){
			delay_ms(20);
			while(KEY_Check(4)==1);	// 等待按键释放
			delay_ms(20);
			BEEP_Ring(100);
			return 4;
		}
	}
	return 0;
}

//按键密码
int KEY_Password(void)
{
	int password[10]={2,3,1,3,2};	// 存储密码
	int flag=5;	// 密码位数
	
	int input_pwd[10]={0};	// 输入密码
	int key_i=0;	// 密码计数值
	int key_input_num;	// 按键输入
	int i=0;
	
	
	while(1)
	{	
		key_input_num=KEY_Scan();
		if(key_input_num==4|key_i==flag)//判断是否按下确认，或者已输满密码位数
		{	
			
			if(key_input_num!=4)	// 如果没有按下确认，一直等待按下确认
			{
				while(KEY_Scan()!=4);
			}
			
			for(i=0;i<=flag;i++)	// 判断密码是否正确
			{
				if(password[i]!=input_pwd[i])
				{
					return 0;	// 密码错误
				}
			}
			return 1;
		}
		else
		{
			input_pwd[key_i]=key_input_num;	// 将输入的按键放入数组
			key_i++;
		}	

	}
}
