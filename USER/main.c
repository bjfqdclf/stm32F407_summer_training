/**
 *������������������������������+ +
 *�������������������ߩ��������ߩ� + +
 *�������������������������������� ��
 *�������������������������������� ++ + + +
 *������������ ������������������ ��+
 *�������������������������������� +
 *�����������������������ߡ�������
 *�������������������������������� + +
 *��������������������������������
 *��������������������������������������������������
 *���������������������������� + + + +
 *������������������������������Code is far away from bug with the animal protecting��������������
 *���������������������������� + ���ޱ���,����bug����
 *����������������������������
 *��������������������������������+������������������
 *���������������������� �������������� + +
 *�������������������� ��LiGoudan ���ǩ� + +
 *�������������������� ������������������
 *�����������������������������ש����� + + + +
 *�����������������������ϩϡ����ϩ�
 *�����������������������ߩ������ߩ�+ + + +
 */
 
#include "main.h"
#include "led.h"	
#include "key.h"
#include "beep.h"
#include "usart.h"
#include "hc_sr04.h"
#include "delay.h"
//#include <string.h>


int time=100;	// �����ٶȵ��ڳ�ʼ��ʱֵ
int speed_falg=0;	// ���ƿ��Ʊ�־λ
int led_speed_num=1;	// �������ĸ���
int led_speed_arr_flag[4]={0,0,0,0};	// �������Ƶı�־
int led_arr_flag[4]={0,0,0,0};	// ���޿��Ƶı�־

int main(void)
{  	
	

	int led_num=3;	// �����ٶȵ��ڵ�
	//int hcsr_distant=0;	// ����������

	// ��ʼ������
	LED_Init();	
	KEY_Init();	
	BEEP_Init();
	USART1_Init(9600);
	HC_SR04_Init();
	
	LED_Open(2);	// �״�������ָʾ�Ƴ�ʼ��
	
	while(1)
	{


		// ����
//		LED_Water();

//		`

//		if(KEY_Password())
//		{
//			LED_Open(1);
//			while(1);	// ������
//		}
//		else
//		{
//			LED_Open(4);
//			delay_ms(500);
//			LED_Close(4);
//			delay_ms(100);
//		}
//		LED_Flash(led_num,time);	// �����ٶȵ���
//		USART_Recv_Data_Do();	// �ַ����������

//		hcsr_distant=HC_SR04_Get_Distant();
//		HC_SR04_Print(hcsr_distant);
//		ultrasonic_distant = HC_SR04_Get_Distant();
//		if(ultrasonic_distant>20 && ultrasonic_distant<4000)
//		{
//			printf("distant is %dmm\r\n", ultrasonic_distant);
//		}
//		delay_ms(500);
		
		
		
		HC_SR04_Ladar_Open();	//	�״﹦�ܿ���
	}

}

