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

#define usart2_baund  57600			//����2�����ʣ�����ָ��ģ�鲨���ʸ���


char door_password[4]={2,3,2,4};	// ��������
char admin_password[4]={2,3,2,2};	// ��������
char password_buf[4]="";	// ��������
int pwd_flag;
int fr_flag=3;
int warming_flag=0;	// ����ְλ1 ��ס
int admin_system_flag=0;	// ����Ա�ж�
extern SysPara AS608Para;					//ָ��ģ��AS608����
extern int  usart1_ps_flag			;		//4��delay�����Ĳ������ı���ʱʱ��(usart.c)(��)

int time=100;	// �����ٶȵ��ڳ�ʼ��ʱֵ
int speed_falg=0;	// ���ƿ��Ʊ�־λ
int led_speed_num=1;	// �������ĸ���
int led_speed_arr_flag[4]={0,0,0,0};	// �������Ƶı�־
int led_arr_flag[4]={0,0,0,0};	// ���޿��Ƶı�־

// ������뻺��
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
	

	//int led_num=3;	// �����ٶȵ��ڵ�
	//int hcsr_distant=0;	// ����������
	
	
	int choose=1; 	// ѡ��С��ͷ

	// ��ʼ������
	LED_Init();	
	KEY_Init();	
	BEEP_Init();
	USART1_Init(9600);
	HC_SR04_Init();
	DHT11_Init();
	OLED_Init();			//��ʼ��OLED  
	usart2_init(usart2_baund);						//��ʼ������2,������ָ��ģ��ͨѶ
	PS_StaGPIO_Init();								//��ʼ��FR��״̬����
	AS608Para.PS_max = 100;
	OLED_Clear();
	
	//LED_Open(2);	// �״�������ָʾ�Ƴ�ʼ��
		

	
	while(1)
	{
				
				
				
		//HC_SR04_Ladar_Open();	//	�״﹦�ܿ���
			
		//DTH11_Get_Print();//��ȡ��ʪ��ģ������

				


//		// ָ��ģ���ʹ��
//		if(usart1_ps_flag == 1)
//		{
//			Add_FR();		//1��¼ָ��
//		}
//		if(usart1_ps_flag == 2)
//		{
//			
//			press_FR();		//2��ˢָ��
//		}
//		
//		if(usart1_ps_flag == 3)
//		{
//		
//			Del_FR();		//3��ɾ��ָ��
//		}

		//����
		DTH11_Get_Print();
		//OLED_Dispaly_Boot();
		delay_ms(2000);
		
		OLED_Dispaly_System();//ˢ��������
		//������
		while(1)
		{
			
			OLED_Dispaly_System_choose(choose);//ˢ��choose
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
			
			// ����key4 ȷ�� ����ϵͳ
			if(KEY_Check(4)==1) // ����key4 ȷ�� ����ϵͳ
			{
				while(KEY_Check(4)==1);
				
				
					if(choose==1)	// ָ�ƽ���ģʽ
					{
						if(warming_flag==5)
						{
							OLED_Dispaly_Warming();
							delay_ms(300);
							choose=1;	// choose ���
							OLED_Dispaly_System();//ˢ��������
						}
						else
						{
						
						OLED_Clear();
						OLED_DrawBMP(0,0,128,8,BMP9);//ָ�ƽ�������
						while(1)
						{
							
							if(KEY_Check(3)==1)
							{
								OLED_Dispaly_System();//ˢ��������
								while(KEY_Check(3)==1);
								break;
							}
				
							fr_flag=press_FR();		// ˢָ��
							
							if(fr_flag==1)
							{
								OLED_Clear();
								OLED_DrawBMP(0,0,128,8,BMP5);
								delay_ms(200);
								
								choose=1;	// choose ���
								re_pwd_buf();// ������뻺��
								OLED_Clear();
								OLED_Dispaly_System();//ˢ��������
								fr_flag=0;
								warming_flag=0;// �����־����
								break;//�˻�������
							}else if(fr_flag==0)//δ��ȡ��
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
									OLED_Dispaly_System();//ˢ��������
									break;
								}
								OLED_DrawBMP(0,0,128,8,BMP9);//ָ�ƽ�������
							}
							
						}
					}
				}
					
					else if(choose==2) // ��������ģʽ
					{
						if(warming_flag==5)
						{
							OLED_Dispaly_Warming();
							delay_ms(300);
							choose=1;	// choose ���
							OLED_Dispaly_System();//ˢ��������
						}
						else
						{
						choose=1;	// choose ���
						
						re_pwd_buf();// ������뻺��
						OLED_Dispaly_System_Pwdmod();// ˢ�������������
						OLED_Dispaly_System_Pwdmod_Pwd();// �������
						
						while(1)
						{
							// �˳�������һ��
							if(KEY_Check(3)==1)
							{
								OLED_Dispaly_System();//ˢ��������
								while(KEY_Check(3)==1);
								break;
							}
							
							OLED_Dispaly_System_Pwdmod_Choose(choose); //ˢ��choose
							if(KEY_Check(1)==1)//����
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
							if(KEY_Check(2)==1)//������
							{
								if(password_buf[choose-1]!=9)
								{
									password_buf[choose-1]++;
								}else{
									password_buf[choose-1]=0;
								}
								OLED_Dispaly_System_Pwdmod_Pwd();// �������
								while(KEY_Check(2)==1);
							}
							if(KEY_Check(4)==1)// ȷ������
							{	
								pwd_flag=pwd_comp();
								if(pwd_flag==1)// �Ŵ�
								{
									OLED_Clear();
									OLED_DrawBMP(0,0,128,8,BMP3);
									delay_ms(200);
									
									choose=1;	// choose ���
									re_pwd_buf();// ������뻺��
									warming_flag=0;// �����־����
									OLED_Dispaly_System();//ˢ��������
									break;
								}
								else// �������
								{
									OLED_Clear();
									OLED_DrawBMP(0,0,128,8,BMP4);
									delay_ms(200);
									warming_flag++;
									choose=1;	// choose ���
									re_pwd_buf();// ������뻺��
									if(warming_flag==5)
									{
										OLED_Dispaly_Warming();
										delay_ms(300);
										OLED_Dispaly_System();//ˢ��������
										break;
									}
									OLED_Dispaly_System_Pwdmod();// ˢ�������������
									OLED_Dispaly_System_Pwdmod_Pwd();// �������
								}
								while(KEY_Check(4)==1);
							}

						}
					}
				}
				
					
					
				
				// ��̨����
				 if(choose==3) // ��̨����
				{
					while(KEY_Check(3)==1);
					// �˳�������һ��
					choose=1;	// choose ���
					
					
					OLED_Dispaly_Admin(); //ˢ�º�̨�������
					OLED_Dispaly_Admin_Choose(choose);//ˢ��choose
					//if()
					while(1)
					{	
						
						// �ɹ�����admin����
						if(admin_system_flag==1)
						{
							if(KEY_Check(3)==1)
							{
								OLED_Dispaly_System();//ˢ��������
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
								
								if(choose==1)// ¼ָ��
								{
									
								}
								else if(choose==2) // ɾ��ָ��
								{
									
								}
								else if(choose==3) // ��������
								{
									choose=1;
									OLED_Dispaly_System_Pwdmod();//�����������
									OLED_Dispaly_System_Pwdmod_Pwd();
									OLED_Dispaly_System_Pwdmod_Choose(choose);//��������ѡ��
									while(1)
									{
										if(KEY_Check(3)==1)
										{
											OLED_Dispaly_Admin();//ˢ�¹���Ա����
											choose=1;
											OLED_Dispaly_Admin_Choose(choose);
											while(KEY_Check(3)==1);
											break;
										}
										
										OLED_Dispaly_System_Pwdmod_Choose(choose); //ˢ��choose
										if(KEY_Check(1)==1)//����
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
										if(KEY_Check(2)==1)//������
										{
											if(password_buf[choose-1]!=9)
											{
												password_buf[choose-1]++;
											}else{
												password_buf[choose-1]=0;
											}
											OLED_Dispaly_System_Pwdmod_Pwd();// �������
											while(KEY_Check(2)==1);
										}
										
										if(KEY_Check(4)==1)// ȷ������
										{	
											while(KEY_Check(4)==1);
											OLED_Clear();
											OLED_ShowCHinese(16,2,43);	//����
											OLED_ShowCHinese(32,2,44);	//�ģ�
											OLED_ShowCHinese(48,2,37);	//�ܣ�37
											OLED_ShowCHinese(64,2,38);	//�룬38
											OLED_ShowCHinese(80,2,27);	//Ϊ��
											OLED_ShowNum(16,5,password_buf[1],1,16);
											OLED_ShowNum(32,5,password_buf[2],1,16);
											OLED_ShowNum(48,5,password_buf[3],1,16);
											OLED_ShowNum(64,5,password_buf[4],1,16);
											pwd_change();	// �޸�����
											warming_flag=0; //�������
											delay_ms(200);
											re_pwd_buf();	// ������뻺��
											
											choose=1;	// choose ���
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
								OLED_Dispaly_System();//ˢ��������
								while(KEY_Check(3)==1);
								break;
							}
							if(KEY_Check(2)==1)
							{
								if(choose==1){
									choose=2;
								}
								OLED_Dispaly_Admin_Choose(choose);//ˢ��choose
								while(KEY_Check(2)==1);
							}
							if(KEY_Check(1)==1)
							{
								if(choose==2){
									choose=1;
								}
								OLED_Dispaly_Admin_Choose(choose);//ˢ��choose
								while(KEY_Check(1)==1);
							}
							if(KEY_Check(4)==1)
							{
								while(KEY_Check(4)==1);
								
								if(choose==2)//��������
								{
									choose=1;	// choose ���
						
									re_pwd_buf();// ������뻺��
									OLED_Dispaly_System_Pwdmod();// ˢ�������������
									OLED_Dispaly_System_Pwdmod_Pwd();// �������
									
									while(1)
									{
										// �˳�������һ��
										if(KEY_Check(3)==1)
										{
											OLED_Clear();
											choose=1;
											OLED_Dispaly_Admin(); //ˢ�º�̨�������
											OLED_Dispaly_Admin_Choose(choose);//ˢ��choose
											while(KEY_Check(3)==1);
											break;
										}
										
										OLED_Dispaly_System_Pwdmod_Choose(choose); //ˢ��choose
										if(KEY_Check(1)==1)//����
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
										if(KEY_Check(2)==1)//������
										{
											if(password_buf[choose-1]!=9)
											{
												password_buf[choose-1]++;
											}else{
												password_buf[choose-1]=0;
											}
											OLED_Dispaly_System_Pwdmod_Pwd();// �������
											while(KEY_Check(2)==1);
										}
										if(KEY_Check(4)==1)// ȷ������
										{	
											pwd_flag=pwd_comp2();
											if(pwd_flag==1)// �Ŵ�
											{
												OLED_Clear();
												OLED_DrawBMP(0,0,128,8,BMP10);// ���ع������
												delay_ms(200);
												
												choose=1;	// choose ���
												re_pwd_buf();// ������뻺��
												
												admin_system_flag=1;
												OLED_Clear();
												OLED_Dispaly_Admin_System();
												OLED_Dispaly_Admin_System_Choose(choose);
												break;
											}
											else// �������
											{
												OLED_Clear();
												OLED_DrawBMP(0,0,128,8,BMP4);
												delay_ms(200);
												
												choose=1;	// choose ���
												re_pwd_buf();// ������뻺��
												OLED_Dispaly_System_Pwdmod();// ˢ�������������
												OLED_Dispaly_System_Pwdmod_Pwd();// �������
											}
										}

									}
								}
								else if(choose==1)//ָ��ʶ��
								{
									choose=1;	// choose ���
									OLED_Clear();
									OLED_DrawBMP(0,0,128,8,BMP9);//ָ�ƽ�������
									while(1)
									{
										
										if(KEY_Check(3)==1)
										{
											choose=1;
											OLED_Dispaly_Admin(); //ˢ�º�̨�������
											OLED_Dispaly_Admin_Choose(choose);//ˢ��choose
											
											while(KEY_Check(3)==1);
											break;
										}
							
										fr_flag=press_FR();		// ˢָ��
										
										if(fr_flag==1)
										{
											OLED_Clear();
											OLED_DrawBMP(0,0,128,8,BMP10);// ���ع������
											delay_ms(200);
											
											choose=1;	// choose ���
											re_pwd_buf();// ������뻺��
											fr_flag=0;
											admin_system_flag=1;//����������
											OLED_Clear();
											OLED_Dispaly_Admin_System();
											OLED_Dispaly_Admin_System_Choose(choose);
											break;
										}else if(fr_flag==0)//δ��ȡ��
										{
											OLED_Clear();
											OLED_DrawBMP(0,0,128,8,BMP4);
											delay_ms(200);
											fr_flag=3;
											OLED_Clear();
											OLED_DrawBMP(0,0,128,8,BMP9);//ָ�ƽ�������
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

