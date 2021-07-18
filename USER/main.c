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
#include "oled.h"
#include "oled_bmp.h"
#include "usart.h"
#include "hc_sr04.h"
#include "dht11.h"
#include "as608_usart2.h"
#include "as608_func.h"
#include "oled_display.h"
#include "delay.h"
//#include <string.h>

#define usart2_baund  57600			//串口2波特率，根据指纹模块波特率更改


char door_password[4]={2,3,2,4};	// 门锁密码
char admin_password[4]={2,3,2,2};	// 门锁密码
char password_buf[4]="";	// 密码设置
int pwd_flag;
int fr_flag=3;
int warming_flag=0;	// 警报职位1 锁住
int admin_system_flag=0;	// 管理员判断
extern SysPara AS608Para;					//指纹模块AS608参数
extern int  usart1_ps_flag			;		//4、delay函数的参数，改变延时时间(usart.c)(三)

int time=100;	// 闪灯速度调节初始延时值
int speed_falg=0;	// 闪灯控制标志位
int led_speed_num=1;	// 控制闪哪个灯
int led_speed_arr_flag[4]={0,0,0,0};	// 有无闪灯的标志
int led_arr_flag[4]={0,0,0,0};	// 有无开灯的标志

// 清空密码缓存
void re_pwd_buf()
{
	int i=0;
	for(i=0;i<4;i++)
	{
		password_buf[i]=NULL;
	}
}

int pwd_comp()
{
	int i=0;
	for(i=0;i<4;i++)
	{
		if (password_buf[i]!=door_password[i])
		{
			return 0;
		}	
	}
	return 1;
}
int pwd_comp2()
{
	int i=0;
	for(i=0;i<4;i++)
	{
		if (password_buf[i]!=admin_password[i])
		{
			return 0;
		}	
	}
	return 1;
}
void pwd_change()
{
	int i=0;
	for(i=0;i<4;i++)
	{
		door_password[i]=password_buf[i];	
	}
}
int main(void)
{  	
	

	//int led_num=3;	// 闪灯速度调节灯
	//int hcsr_distant=0;	// 超声波距离
	
	
	int choose=1; 	// 选项小箭头

	// 初始化函数
	LED_Init();	
	KEY_Init();	
	BEEP_Init();
	USART1_Init(9600);
	HC_SR04_Init();
	DHT11_Init();
	OLED_Init();			//初始化OLED  
	usart2_init(usart2_baund);						//初始化串口2,用于与指纹模块通讯
	PS_StaGPIO_Init();								//初始化FR读状态引脚
	AS608Para.PS_max = 100;
	OLED_Clear();
	
	//LED_Open(2);	// 雷达灵敏度指示灯初始化
		

	
	while(1)
	{
				
				
				
		//HC_SR04_Ladar_Open();	//	雷达功能开启
			
		//DTH11_Get_Print();//获取温湿度模块数据

				


//		// 指纹模块的使用
//		if(usart1_ps_flag == 1)
//		{
//			Add_FR();		//1、录指纹
//		}
//		if(usart1_ps_flag == 2)
//		{
//			
//			press_FR();		//2、刷指纹
//		}
//		
//		if(usart1_ps_flag == 3)
//		{
//		
//			Del_FR();		//3、删除指纹
//		}

		//开机
		DTH11_Get_Print();
		//OLED_Dispaly_Boot();
		delay_ms(2000);
		
		OLED_Dispaly_System();//刷新主界面
		//主界面
		while(1)
		{
			
			OLED_Dispaly_System_choose(choose);//刷新choose
			if(KEY_Check(2)==1)
			{
				if(choose<3)
				{
				choose++;
				OLED_Dispaly_System_choose(choose);
				while(KEY_Check(2)==1);
				}
			}
		
			
			if(KEY_Check(1)==1)
			{
				if(choose>1)
				{
					choose--;
					OLED_Dispaly_System_choose(choose);
					while(KEY_Check(1)==1);
				}
			}
			
			// 按下key4 确认 进入系统
			if(KEY_Check(4)==1) // 按下key4 确认 进入系统
			{
				while(KEY_Check(4)==1);
				
				
					if(choose==1)	// 指纹解锁模式
					{
						if(warming_flag==5)
						{
							OLED_Dispaly_Warming();
							delay_ms(300);
							choose=1;	// choose 清除
							OLED_Dispaly_System();//刷新主界面
						}
						else
						{
						
						OLED_Clear();
						OLED_DrawBMP(0,0,128,8,BMP9);//指纹解锁界面
						while(1)
						{
							
							if(KEY_Check(3)==1)
							{
								OLED_Dispaly_System();//刷新主界面
								while(KEY_Check(3)==1);
								break;
							}
				
							fr_flag=press_FR();		// 刷指纹
							
							if(fr_flag==1)
							{
								OLED_Clear();
								OLED_DrawBMP(0,0,128,8,BMP5);
								delay_ms(200);
								
								choose=1;	// choose 清除
								re_pwd_buf();// 清空密码缓存
								OLED_Clear();
								OLED_Dispaly_System();//刷新主界面
								fr_flag=0;
								warming_flag=0;// 警告标志重置
								break;//退回主界面
							}else if(fr_flag==0)//未获取到
							{
								OLED_Clear();
								OLED_DrawBMP(0,0,128,8,BMP4);
								delay_ms(200);
								fr_flag=3;
								warming_flag++;
								OLED_Clear();
								if(warming_flag==5)
								{
									OLED_Dispaly_Warming();
									delay_ms(300);
									OLED_Dispaly_System();//刷新主界面
									break;
								}
								OLED_DrawBMP(0,0,128,8,BMP9);//指纹解锁界面
							}
							
						}
					}
				}
					
					else if(choose==2) // 按键密码模式
					{
						if(warming_flag==5)
						{
							OLED_Dispaly_Warming();
							delay_ms(300);
							choose=1;	// choose 清除
							OLED_Dispaly_System();//刷新主界面
						}
						else
						{
						choose=1;	// choose 清除
						
						re_pwd_buf();// 清空密码缓存
						OLED_Dispaly_System_Pwdmod();// 刷新密码解锁界面
						OLED_Dispaly_System_Pwdmod_Pwd();// 密码更新
						
						while(1)
						{
							// 退出返回上一级
							if(KEY_Check(3)==1)
							{
								OLED_Dispaly_System();//刷新主界面
								while(KEY_Check(3)==1);
								break;
							}
							
							OLED_Dispaly_System_Pwdmod_Choose(choose); //刷新choose
							if(KEY_Check(1)==1)//右移
							{
								if(choose!=4)
								{
									choose++;
								}
								else{
									choose=1;
								}
								OLED_Dispaly_System_Pwdmod_Choose(choose);
								while(KEY_Check(1)==1);
							}
							if(KEY_Check(2)==1)//变数字
							{
								if(password_buf[choose-1]!=9)
								{
									password_buf[choose-1]++;
								}else{
									password_buf[choose-1]=0;
								}
								OLED_Dispaly_System_Pwdmod_Pwd();// 密码更新
								while(KEY_Check(2)==1);
							}
							if(KEY_Check(4)==1)// 确认密码
							{	
								pwd_flag=pwd_comp();
								if(pwd_flag==1)// 门打开
								{
									OLED_Clear();
									OLED_DrawBMP(0,0,128,8,BMP3);
									delay_ms(200);
									
									choose=1;	// choose 清除
									re_pwd_buf();// 清空密码缓存
									warming_flag=0;// 警告标志重置
									OLED_Dispaly_System();//刷新主界面
									break;
								}
								else// 密码错误
								{
									OLED_Clear();
									OLED_DrawBMP(0,0,128,8,BMP4);
									delay_ms(200);
									warming_flag++;
									choose=1;	// choose 清除
									re_pwd_buf();// 清空密码缓存
									if(warming_flag==5)
									{
										OLED_Dispaly_Warming();
										delay_ms(300);
										OLED_Dispaly_System();//刷新主界面
										break;
									}
									OLED_Dispaly_System_Pwdmod();// 刷新密码解锁界面
									OLED_Dispaly_System_Pwdmod_Pwd();// 密码更新
								}
								while(KEY_Check(4)==1);
							}

						}
					}
				}
				
					
					
				
				// 后台管理
				 if(choose==3) // 后台管理
				{
					while(KEY_Check(3)==1);
					// 退出返回上一级
					choose=1;	// choose 清除
					
					
					OLED_Dispaly_Admin(); //刷新后台管理界面
					OLED_Dispaly_Admin_Choose(choose);//刷新choose
					//if()
					while(1)
					{	
						
						// 成功进入admin界面
						if(admin_system_flag==1)
						{
							if(KEY_Check(3)==1)
							{
								OLED_Dispaly_System();//刷新主界面
								while(KEY_Check(3)==1);
								break;
							}
							if(KEY_Check(2)==1)
							{
								if(choose<3)
								{
								choose++;
								OLED_Dispaly_System_choose(choose);
								while(KEY_Check(2)==1);
								}
							}
							if(KEY_Check(1)==1)
							{
								if(choose>1)
								{
									choose--;
									OLED_Dispaly_System_choose(choose);
									while(KEY_Check(1)==1);
								}
							}
							if(KEY_Check(4)==1)
							{
								while(KEY_Check(4)==1);
								
								if(choose==1)// 录指纹
								{
									
								}
								else if(choose==2) // 删除指纹
								{
									
								}
								else if(choose==3) // 更改密码
								{
									choose=1;
									OLED_Dispaly_System_Pwdmod();//加载密码界面
									OLED_Dispaly_System_Pwdmod_Pwd();
									OLED_Dispaly_System_Pwdmod_Choose(choose);//加载密码选择
									while(1)
									{
										if(KEY_Check(3)==1)
										{
											OLED_Dispaly_Admin();//刷新管理员界面
											choose=1;
											OLED_Dispaly_Admin_Choose(choose);
											while(KEY_Check(3)==1);
											break;
										}
										
										OLED_Dispaly_System_Pwdmod_Choose(choose); //刷新choose
										if(KEY_Check(1)==1)//右移
										{
											if(choose!=4)
											{
												choose++;
											}
											else{
												choose=1;
											}
											OLED_Dispaly_System_Pwdmod_Choose(choose);
											while(KEY_Check(1)==1);
										}
										if(KEY_Check(2)==1)//变数字
										{
											if(password_buf[choose-1]!=9)
											{
												password_buf[choose-1]++;
											}else{
												password_buf[choose-1]=0;
											}
											OLED_Dispaly_System_Pwdmod_Pwd();// 密码更新
											while(KEY_Check(2)==1);
										}
										
										if(KEY_Check(4)==1)// 确认密码
										{	
											while(KEY_Check(4)==1);
											OLED_Clear();
											OLED_ShowCHinese(16,2,43);	//更，
											OLED_ShowCHinese(32,2,44);	//改，
											OLED_ShowCHinese(48,2,37);	//密，37
											OLED_ShowCHinese(64,2,38);	//码，38
											OLED_ShowCHinese(80,2,27);	//为，
											OLED_ShowNum(16,5,password_buf[1],1,16);
											OLED_ShowNum(32,5,password_buf[2],1,16);
											OLED_ShowNum(48,5,password_buf[3],1,16);
											OLED_ShowNum(64,5,password_buf[4],1,16);
											pwd_change();	// 修改密码
											warming_flag=0; //警报解除
											delay_ms(200);
											re_pwd_buf();	// 清除密码缓存
											
											choose=1;	// choose 清除
											OLED_Dispaly_Admin_System();
											OLED_Dispaly_Admin_System_Choose(choose);
											break;
										}
									}
								}
							}
							
							
						}
						else
						{	
							if(KEY_Check(3)==1)
							{
								OLED_Dispaly_System();//刷新主界面
								while(KEY_Check(3)==1);
								break;
							}
							if(KEY_Check(2)==1)
							{
								if(choose==1){
									choose=2;
								}
								OLED_Dispaly_Admin_Choose(choose);//刷新choose
								while(KEY_Check(2)==1);
							}
							if(KEY_Check(1)==1)
							{
								if(choose==2){
									choose=1;
								}
								OLED_Dispaly_Admin_Choose(choose);//刷新choose
								while(KEY_Check(1)==1);
							}
							if(KEY_Check(4)==1)
							{
								while(KEY_Check(4)==1);
								
								if(choose==2)//按键密码
								{
									choose=1;	// choose 清除
						
									re_pwd_buf();// 清空密码缓存
									OLED_Dispaly_System_Pwdmod();// 刷新密码解锁界面
									OLED_Dispaly_System_Pwdmod_Pwd();// 密码更新
									
									while(1)
									{
										// 退出返回上一级
										if(KEY_Check(3)==1)
										{
											OLED_Clear();
											choose=1;
											OLED_Dispaly_Admin(); //刷新后台管理界面
											OLED_Dispaly_Admin_Choose(choose);//刷新choose
											while(KEY_Check(3)==1);
											break;
										}
										
										OLED_Dispaly_System_Pwdmod_Choose(choose); //刷新choose
										if(KEY_Check(1)==1)//右移
										{
											if(choose!=4)
											{
												choose++;
											}
											else{
												choose=1;
											}
											OLED_Dispaly_System_Pwdmod_Choose(choose);
											while(KEY_Check(1)==1);
										}
										if(KEY_Check(2)==1)//变数字
										{
											if(password_buf[choose-1]!=9)
											{
												password_buf[choose-1]++;
											}else{
												password_buf[choose-1]=0;
											}
											OLED_Dispaly_System_Pwdmod_Pwd();// 密码更新
											while(KEY_Check(2)==1);
										}
										if(KEY_Check(4)==1)// 确认密码
										{	
											pwd_flag=pwd_comp2();
											if(pwd_flag==1)// 门打开
											{
												OLED_Clear();
												OLED_DrawBMP(0,0,128,8,BMP10);// 加载管理界面
												delay_ms(200);
												
												choose=1;	// choose 清除
												re_pwd_buf();// 清空密码缓存
												
												admin_system_flag=1;
												OLED_Clear();
												OLED_Dispaly_Admin_System();
												OLED_Dispaly_Admin_System_Choose(choose);
												break;
											}
											else// 密码错误
											{
												OLED_Clear();
												OLED_DrawBMP(0,0,128,8,BMP4);
												delay_ms(200);
												
												choose=1;	// choose 清除
												re_pwd_buf();// 清空密码缓存
												OLED_Dispaly_System_Pwdmod();// 刷新密码解锁界面
												OLED_Dispaly_System_Pwdmod_Pwd();// 密码更新
											}
										}

									}
								}
								else if(choose==1)//指纹识别
								{
									choose=1;	// choose 清除
									OLED_Clear();
									OLED_DrawBMP(0,0,128,8,BMP9);//指纹解锁界面
									while(1)
									{
										
										if(KEY_Check(3)==1)
										{
											choose=1;
											OLED_Dispaly_Admin(); //刷新后台管理界面
											OLED_Dispaly_Admin_Choose(choose);//刷新choose
											
											while(KEY_Check(3)==1);
											break;
										}
							
										fr_flag=press_FR();		// 刷指纹
										
										if(fr_flag==1)
										{
											OLED_Clear();
											OLED_DrawBMP(0,0,128,8,BMP10);// 加载管理界面
											delay_ms(200);
											
											choose=1;	// choose 清除
											re_pwd_buf();// 清空密码缓存
											fr_flag=0;
											admin_system_flag=1;//进入管理界面
											OLED_Clear();
											OLED_Dispaly_Admin_System();
											OLED_Dispaly_Admin_System_Choose(choose);
											break;
										}else if(fr_flag==0)//未获取到
										{
											OLED_Clear();
											OLED_DrawBMP(0,0,128,8,BMP4);
											delay_ms(200);
											fr_flag=3;
											OLED_Clear();
											OLED_DrawBMP(0,0,128,8,BMP9);//指纹解锁界面
										}
										
									}
									
								}
								
								
								
							}

						}
					
					}
					
				}
			}
		}

	
	}

}

