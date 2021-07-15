/**
 *　　　　　　　　┏┓　　　┏┓+ +
 *　　　　　　　┏┛┻━━━┛┻┓ + +
 *　　　　　　　┃　　　　　　　┃ 　
 *　　　　　　　┃　　　━　　　┃ ++ + + +
 *　　　　　　 ████━████ ┃+
 *　　　　　　　┃　　　　　　　┃ +
 *　　　　　　　┃　　　┻　　　┃
 *　　　　　　　┃　　　　　　　┃ + +
 *　　　　　　　┗━┓　　　┏━┛
 *　　　　　　　　　┃　　　┃　　　　　　　　　　　
 *　　　　　　　　　┃　　　┃ + + + +
 *　　　　　　　　　┃　　　┃　Code is far away from bug with the animal protecting　　　　　　　
 *　　　　　　　　　┃　　　┃ + 神兽保佑,永无bug　　
 *　　　　　　　　　┃　　　┃
 *　　　　　　　　　┃　　　┃　　+　　　　　　　　　
 *　　　　　　　　　┃　 　　┗━━━┓ + +
 *　　　　　　　　　┃ 　LiGoudan 　┣┓ + +
 *　　　　　　　　　┃ 　　　　　　　┏┛
 *　　　　　　　　　┗┓┓┏━┳┓┏┛ + + + +
 *　　　　　　　　　　┃┫┫　┃┫┫
 *　　　　　　　　　　┗┻┛　┗┻┛+ + + +
 */
 
#include "main.h"
#include "led.h"	
#include "key.h"
#include "beep.h"
#include "usart.h"
#include "hc_sr04.h"
#include "delay.h"
//#include <string.h>


int time=100;	// 闪灯速度调节初始延时值
int speed_falg=0;	// 闪灯控制标志位
int led_speed_num=1;	// 控制闪哪个灯
int led_speed_arr_flag[4]={0,0,0,0};	// 有无闪灯的标志
int led_arr_flag[4]={0,0,0,0};	// 有无开灯的标志

int main(void)
{  	
	

	int led_num=3;	// 闪灯速度调节灯
	//int hcsr_distant=0;	// 超声波距离

	// 初始化函数
	LED_Init();	
	KEY_Init();	
	BEEP_Init();
	USART1_Init(9600);
	HC_SR04_Init();
	
	LED_Open(2);	// 雷达灵敏度指示灯初始化
	
	while(1)
	{


		// 按键
//		LED_Water();

//		`

//		if(KEY_Password())
//		{
//			LED_Open(1);
//			while(1);	// 主程序
//		}
//		else
//		{
//			LED_Open(4);
//			delay_ms(500);
//			LED_Close(4);
//			delay_ms(100);
//		}
//		LED_Flash(led_num,time);	// 闪灯速度调节
//		USART_Recv_Data_Do();	// 字符串操作点灯

//		hcsr_distant=HC_SR04_Get_Distant();
//		HC_SR04_Print(hcsr_distant);
//		ultrasonic_distant = HC_SR04_Get_Distant();
//		if(ultrasonic_distant>20 && ultrasonic_distant<4000)
//		{
//			printf("distant is %dmm\r\n", ultrasonic_distant);
//		}
//		delay_ms(500);
		
		
		
		HC_SR04_Ladar_Open();	//	雷达功能开启
	}

}

