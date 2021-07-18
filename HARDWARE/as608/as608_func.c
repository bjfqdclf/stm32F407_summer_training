#include "as608_func.h"
#include "led.h"
#include "oled_display.h"
SysPara AS608Para;					//ָ��ģ��AS608����
u16 ValidN;							//ģ������Чָ�Ƹ���

extern char key_password_num			;		//1��ȫ������(key.c)(��)
extern int  usart1_ps_flag			;		//4��delay�����Ĳ������ı���ʱʱ��(usart.c)(��)

//��ȡ������ֵ
u16 GET_NUM(void)
{
	char 	input_id[4] 		= {0}		;			//2����������(��)
	int  	key_i				=  0        ;			//3���������ֵ(��)
	int  	key_num				=  0        ;			//3���������ֵ(��)
	int  	key_flag			=  0        ;			//4������ȷ�ϱ�־λ(��)
	while(1)
	{
		if((KEY_Check(1)==1) || (KEY_Check(2)==1))			//1��ͬʱ�������������ֵ���Ƿ���
		{
			//BEEP_Open();
			LED_Open(4);
			delay_ms(100);
			BEEP_Close();													//2����������ʾ�Ѱ��°���
			LED_Close(4);
			
			delay_ms(20);												//3����ʱ20ms������(����ȥ)
			key_num++;	
			if(key_num == 10)
			{
				key_num = 0;
			}
			
			printf("key_num = %d\r\n", key_num);
			while((KEY_Check(1)==1) || (KEY_Check(2)==1));		//5����ֹ������һֱ��ס�����¼���ֵkey_iһֱ��
			delay_ms(20);												//6����ʱ20ms������(�ɿ���ʱ��)

		}	
		
		
		
		if((KEY_Check(3)==1))												//8��ȷ�ϼ�����ⰴ��4��ֵ���Ƿ���
		{
			//BEEP_Open();
			LED_Open(4);
			delay_ms(100);		
			BEEP_Close();	//9����������ʾ�Ѱ��°���	
			LED_Close(4);				
			
			delay_ms(20);												//3����ʱ20ms������(����ȥ)
			input_id[key_i++]  = key_num;								//4������ȡ��ֵ��ֵ��������������
			printf("input_id[%d] = %d\r\n", key_i-1, key_num);
			while(KEY_Check(3)==1);
			delay_ms(20);												//3����ʱ20ms������(����ȥ)
		}
		
		
		if((KEY_Check(4)==1))												//8��ȷ�ϼ�����ⰴ��4��ֵ���Ƿ���
		{
			//BEEP_Open();
			LED_Open(4);
			delay_ms(100);		
			BEEP_Close();													//9����������ʾ�Ѱ��°���		
			LED_Close(4);
			
			delay_ms(20);												//3����ʱ20ms������(����ȥ)
			return input_id[0]*10+input_id[1];
		}
	}
}

//��ʾȷ���������Ϣ
void ShowErrMessage(u8 ensure)
{
	//LCD_Fill(0,120,lcddev.width,160,WHITE);
	//Show_Str_Mid(0,120,(u8*)EnsureMessage(ensure),16,240);
	printf("%s\r\n", (u8*)EnsureMessage(ensure));
	
}

//¼ָ��
void Add_FR(void)
{
	
	u8 i,ensure ,processnum=0;
	u16 ID;
	//printf("==================1��¼ָ��===============\r\n");
	OLED_Dispaly_1();
	
	
	while(1)
	{
		
		if(usart1_ps_flag != 1)
		{
			break;
		}
		switch (processnum)
		{
			case 0:
				i++;
				//LCD_Fill(0,100,lcddev.width,160,WHITE);
				//printf("�밴ָ��\r\n");
				OLED_Dispaly_2();
				ensure=PS_GetImage();
				if(ensure==0x00) 
				{
					//BEEP_Open();
					LED_Open(4);
					ensure=PS_GenChar(CharBuffer1);//��������
					BEEP_Close();
					LED_Close(4);
					if(ensure==0x00)
					{
						//LCD_Fill(0,120,lcddev.width,160,WHITE);
						//Show_Str_Mid(0,120,"ָ������",16,240);
						//printf("ָ������\r\n");
						OLED_Dispaly_3();
						i=0;
						processnum=1;//�����ڶ���						
					}else ShowErrMessage(ensure);				
				}else ShowErrMessage(ensure);						
				break;
			
			case 1:
				i++;
				//LCD_Fill(0,100,lcddev.width,160,WHITE);
				//Show_Str_Mid(0,100,"�밴�ٰ�һ��ָ��",16,240);
				//printf("�밴�ٰ�һ��ָ��\r\n");
				OLED_Dispaly_4();
				ensure=PS_GetImage();
				if(ensure==0x00) 
				{
					BEEP_Open();
					ensure=PS_GenChar(CharBuffer2);//��������
					BEEP_Close();
					if(ensure==0x00)
					{
						//LCD_Fill(0,120,lcddev.width,160,WHITE);
						//Show_Str_Mid(0,120,"ָ������",16,240);
						//printf("ָ������\r\n");
						OLED_Dispaly_3();
						i=0;
						processnum=2;//����������
					}else ShowErrMessage(ensure);	
				}else ShowErrMessage(ensure);		
				break;

			case 2:
				//LCD_Fill(0,100,lcddev.width,160,WHITE);
				//Show_Str_Mid(0,100,"�Ա�����ָ��",16,240);
				//printf("�Ա�����ָ��\r\n");
				OLED_Dispaly_5();
				ensure=PS_Match();
				if(ensure==0x00) 
				{
					//LCD_Fill(0,120,lcddev.width,160,WHITE);
					//Show_Str_Mid(0,120,"�Աȳɹ�,����ָ��һ��",16,240);
					printf("�Աȳɹ�,����ָ��һ��\r\n");
					processnum=3;//�������Ĳ�
				}
				else 
				{
					//LCD_Fill(0,100,lcddev.width,160,WHITE);
					//Show_Str_Mid(0,100,"�Ա�ʧ�ܣ�������¼��ָ��",16,240);
					printf("�Ա�ʧ�ܣ�������¼��ָ��\r\n");
					ShowErrMessage(ensure);
					i=0;
					processnum=0;//���ص�һ��		
				}
				delay_ms(1200);
				break;

			case 3:
				//LCD_Fill(0,100,lcddev.width,160,WHITE);
				//Show_Str_Mid(0,100,"����ָ��ģ��",16,240);
				printf("����ָ��ģ��\r\n");
				ensure=PS_RegModel();
				if(ensure==0x00) 
				{
					//LCD_Fill(0,120,lcddev.width,160,WHITE);
					//Show_Str_Mid(0,120,"����ָ��ģ��ɹ�",16,240);
					printf("����ָ��ģ��ɹ�\r\n");
					processnum=4;//�������岽
				}else {processnum=0;ShowErrMessage(ensure);}
				delay_ms(1200);
				break;
				
			case 4:	
				//LCD_Fill(0,100,lcddev.width,160,WHITE);
				//Show_Str_Mid(0,100,"�����봢��ID,��Enter����",16,240);
				//Show_Str_Mid(0,120,"0=< ID <=299",16,240);
				printf("�����봢��ID,��Enter����\r\n");
				printf("0=< ID <=299\r\n");
				do
				{
					ID=GET_NUM();
					printf("ID == %d\r\n", ID);
				}
					
				while(!(ID<AS608Para.PS_max));//����ID����С��ģ������������ֵ
				ensure=PS_StoreChar(CharBuffer2,ID);//����ģ��
				if(ensure==0x00) 
				{			
					//LCD_Fill(0,100,lcddev.width,160,WHITE);					
					//Show_Str_Mid(0,120,"¼��ָ�Ƴɹ�",16,240);
					printf("¼��ָ�Ƴɹ�\r\n");
					PS_ValidTempleteNum(&ValidN);//����ָ�Ƹ���
					//LCD_ShowNum(56,80,AS608Para.PS_max-ValidN,3,16);//��ʾʣ��ָ������
					delay_ms(1500);
					//LCD_Fill(0,100,240,160,WHITE);
					return ;
				}else {processnum=0;ShowErrMessage(ensure);}					
				break;				
		}
		delay_ms(1000);
		if(i==5)//����5��û�а���ָ���˳�
		{
			//LCD_Fill(0,100,lcddev.width,160,WHITE);
			break;	
		}				
	}
}

//ˢָ��
int press_FR(void)
{
	
	
	SearchResult seach;
	u8 ensure;
	char *str;
	printf("==================2��ˢָ��===============\r\n");
	ensure=PS_GetImage();
	if(ensure==0x00)//��ȡͼ��ɹ� 
	{	
		LED_Open(4);
		//BEEP_Open();//�򿪷�����	
		ensure=PS_GenChar(CharBuffer1);
		if(ensure==0x00) //���������ɹ�
		{		
			BEEP_Close();//�رշ�����
			LED_Close(4);			
			ensure=PS_HighSpeedSearch(CharBuffer1,0,AS608Para.PS_max,&seach);
			if(ensure==0x00)//�����ɹ�
			{				
				//LCD_Fill(0,100,lcddev.width,160,WHITE);
				//Show_Str_Mid(0,100,"ˢָ�Ƴɹ�",16,240);	
				//printf("ˢָ�Ƴɹ�\r\n");				
				//str=mymalloc(SRAMIN,2000);
				//sprintf(str,"ȷ�д���,ID:%d  ƥ��÷�:%d",seach.pageID,seach.mathscore);
				//Show_Str_Mid(0,140,(u8*)str,16,240);
				//printf("ȷ�д���,ID:%d  ƥ��÷�:%d",seach.pageID,seach.mathscore);
				//myfree(SRAMIN,str);
				return 1;
			}
			else 
				//ShowErrMessage(ensure);
				return 0;			
	  }
		else
			//ShowErrMessage(ensure);
			return 3;	
	 BEEP_Close();//�رշ�����
	 delay_ms(600);
	 //LCD_Fill(0,100,lcddev.width,160,WHITE);
	}
	else
		return 3;
		
}

//ɾ��ָ��
void Del_FR(void)
{
	u8  ensure;
	u16 num;
	//LCD_Fill(0,100,lcddev.width,160,WHITE);

	//Show_Str_Mid(0,100,"ɾ��ָ��",16,240);
	//Show_Str_Mid(0,120,"������ָ��ID��Enter����",16,240);
	//Show_Str_Mid(0,140,"0=< ID <=299",16,240);
	printf("ɾ��ָ��\r\n");
	printf("������ָ��ID��key4����\r\n");
	printf("0=< ID <=299\r\n");
	delay_ms(50);
	
	
	
	//AS608_load_keyboard(0,170,(u8**)kbd_delFR);
	num=GET_NUM();//��ȡ���ص���ֵ
	if(num==0xFFFF)
		goto MENU ; //������ҳ��
	else if(num==0xFF00)
		ensure=PS_Empty();//���ָ�ƿ�
	else 
		ensure=PS_DeletChar(num,1);//ɾ������ָ��
	if(ensure==0)
	{
		//LCD_Fill(0,120,lcddev.width,160,WHITE);
		//Show_Str_Mid(0,140,"ɾ��ָ�Ƴɹ�",16,240);		
		printf("ɾ��ָ�Ƴɹ�\r\n");

	}
  else
		ShowErrMessage(ensure);	
	delay_ms(1200);
	PS_ValidTempleteNum(&ValidN);//����ָ�Ƹ���
	//LCD_ShowNum(56,80,AS608Para.PS_max-ValidN,3,16);
MENU:	
	//LCD_Fill(0,100,lcddev.width,160,WHITE);
	delay_ms(50);
	//AS608_load_keyboard(0,170,(u8**)kbd_menu);
}
