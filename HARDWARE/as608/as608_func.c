#include "as608_func.h"
#include "led.h"
#include "oled_display.h"
SysPara AS608Para;					//指纹模块AS608参数
u16 ValidN;							//模块内有效指纹个数

extern char key_password_num			;		//1、全局声明(key.c)(二)
extern int  usart1_ps_flag			;		//4、delay函数的参数，改变延时时间(usart.c)(三)

//获取键盘数值
u16 GET_NUM(void)
{
	char 	input_id[4] 		= {0}		;			//2、输入密码(二)
	int  	key_i				=  0        ;			//3、密码计数值(二)
	int  	key_num				=  0        ;			//3、密码计数值(二)
	int  	key_flag			=  0        ;			//4、密码确认标志位(二)
	while(1)
	{
		if((KEY_Check(1)==1) || (KEY_Check(2)==1))			//1、同时检测三个按键的值，是否按下
		{
			//BEEP_Open();
			LED_Open(4);
			delay_ms(100);
			BEEP_Close();													//2、蜂鸣器提示已按下按键
			LED_Close(4);
			
			delay_ms(20);												//3、延时20ms，消抖(按下去)
			key_num++;	
			if(key_num == 10)
			{
				key_num = 0;
			}
			
			printf("key_num = %d\r\n", key_num);
			while((KEY_Check(1)==1) || (KEY_Check(2)==1));		//5、防止按键被一直按住，导致计数值key_i一直加
			delay_ms(20);												//6、延时20ms，消抖(松开的时候)

		}	
		
		
		
		if((KEY_Check(3)==1))												//8、确认键，检测按键4的值，是否按下
		{
			//BEEP_Open();
			LED_Open(4);
			delay_ms(100);		
			BEEP_Close();	//9、蜂鸣器提示已按下按键	
			LED_Close(4);				
			
			delay_ms(20);												//3、延时20ms，消抖(按下去)
			input_id[key_i++]  = key_num;								//4、将获取的值赋值给输入密码数组
			printf("input_id[%d] = %d\r\n", key_i-1, key_num);
			while(KEY_Check(3)==1);
			delay_ms(20);												//3、延时20ms，消抖(按下去)
		}
		
		
		if((KEY_Check(4)==1))												//8、确认键，检测按键4的值，是否按下
		{
			//BEEP_Open();
			LED_Open(4);
			delay_ms(100);		
			BEEP_Close();													//9、蜂鸣器提示已按下按键		
			LED_Close(4);
			
			delay_ms(20);												//3、延时20ms，消抖(按下去)
			return input_id[0]*10+input_id[1];
		}
	}
}

//显示确认码错误信息
void ShowErrMessage(u8 ensure)
{
	//LCD_Fill(0,120,lcddev.width,160,WHITE);
	//Show_Str_Mid(0,120,(u8*)EnsureMessage(ensure),16,240);
	printf("%s\r\n", (u8*)EnsureMessage(ensure));
	
}

//录指纹
void Add_FR(void)
{
	
	u8 i,ensure ,processnum=0;
	u16 ID;
	//printf("==================1、录指纹===============\r\n");
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
				//printf("请按指纹\r\n");
				OLED_Dispaly_2();
				ensure=PS_GetImage();
				if(ensure==0x00) 
				{
					//BEEP_Open();
					LED_Open(4);
					ensure=PS_GenChar(CharBuffer1);//生成特征
					BEEP_Close();
					LED_Close(4);
					if(ensure==0x00)
					{
						//LCD_Fill(0,120,lcddev.width,160,WHITE);
						//Show_Str_Mid(0,120,"指纹正常",16,240);
						//printf("指纹正常\r\n");
						OLED_Dispaly_3();
						i=0;
						processnum=1;//跳到第二步						
					}else ShowErrMessage(ensure);				
				}else ShowErrMessage(ensure);						
				break;
			
			case 1:
				i++;
				//LCD_Fill(0,100,lcddev.width,160,WHITE);
				//Show_Str_Mid(0,100,"请按再按一次指纹",16,240);
				//printf("请按再按一次指纹\r\n");
				OLED_Dispaly_4();
				ensure=PS_GetImage();
				if(ensure==0x00) 
				{
					BEEP_Open();
					ensure=PS_GenChar(CharBuffer2);//生成特征
					BEEP_Close();
					if(ensure==0x00)
					{
						//LCD_Fill(0,120,lcddev.width,160,WHITE);
						//Show_Str_Mid(0,120,"指纹正常",16,240);
						//printf("指纹正常\r\n");
						OLED_Dispaly_3();
						i=0;
						processnum=2;//跳到第三步
					}else ShowErrMessage(ensure);	
				}else ShowErrMessage(ensure);		
				break;

			case 2:
				//LCD_Fill(0,100,lcddev.width,160,WHITE);
				//Show_Str_Mid(0,100,"对比两次指纹",16,240);
				//printf("对比两次指纹\r\n");
				OLED_Dispaly_5();
				ensure=PS_Match();
				if(ensure==0x00) 
				{
					//LCD_Fill(0,120,lcddev.width,160,WHITE);
					//Show_Str_Mid(0,120,"对比成功,两次指纹一样",16,240);
					printf("对比成功,两次指纹一样\r\n");
					processnum=3;//跳到第四步
				}
				else 
				{
					//LCD_Fill(0,100,lcddev.width,160,WHITE);
					//Show_Str_Mid(0,100,"对比失败，请重新录入指纹",16,240);
					printf("对比失败，请重新录入指纹\r\n");
					ShowErrMessage(ensure);
					i=0;
					processnum=0;//跳回第一步		
				}
				delay_ms(1200);
				break;

			case 3:
				//LCD_Fill(0,100,lcddev.width,160,WHITE);
				//Show_Str_Mid(0,100,"生成指纹模板",16,240);
				printf("生成指纹模板\r\n");
				ensure=PS_RegModel();
				if(ensure==0x00) 
				{
					//LCD_Fill(0,120,lcddev.width,160,WHITE);
					//Show_Str_Mid(0,120,"生成指纹模板成功",16,240);
					printf("生成指纹模板成功\r\n");
					processnum=4;//跳到第五步
				}else {processnum=0;ShowErrMessage(ensure);}
				delay_ms(1200);
				break;
				
			case 4:	
				//LCD_Fill(0,100,lcddev.width,160,WHITE);
				//Show_Str_Mid(0,100,"请输入储存ID,按Enter保存",16,240);
				//Show_Str_Mid(0,120,"0=< ID <=299",16,240);
				printf("请输入储存ID,按Enter保存\r\n");
				printf("0=< ID <=299\r\n");
				do
				{
					ID=GET_NUM();
					printf("ID == %d\r\n", ID);
				}
					
				while(!(ID<AS608Para.PS_max));//输入ID必须小于模块容量最大的数值
				ensure=PS_StoreChar(CharBuffer2,ID);//储存模板
				if(ensure==0x00) 
				{			
					//LCD_Fill(0,100,lcddev.width,160,WHITE);					
					//Show_Str_Mid(0,120,"录入指纹成功",16,240);
					printf("录入指纹成功\r\n");
					PS_ValidTempleteNum(&ValidN);//读库指纹个数
					//LCD_ShowNum(56,80,AS608Para.PS_max-ValidN,3,16);//显示剩余指纹容量
					delay_ms(1500);
					//LCD_Fill(0,100,240,160,WHITE);
					return ;
				}else {processnum=0;ShowErrMessage(ensure);}					
				break;				
		}
		delay_ms(1000);
		if(i==5)//超过5次没有按手指则退出
		{
			//LCD_Fill(0,100,lcddev.width,160,WHITE);
			break;	
		}				
	}
}

//刷指纹
int press_FR(void)
{
	
	
	SearchResult seach;
	u8 ensure;
	char *str;
	printf("==================2、刷指纹===============\r\n");
	ensure=PS_GetImage();
	if(ensure==0x00)//获取图像成功 
	{	
		LED_Open(4);
		//BEEP_Open();//打开蜂鸣器	
		ensure=PS_GenChar(CharBuffer1);
		if(ensure==0x00) //生成特征成功
		{		
			BEEP_Close();//关闭蜂鸣器
			LED_Close(4);			
			ensure=PS_HighSpeedSearch(CharBuffer1,0,AS608Para.PS_max,&seach);
			if(ensure==0x00)//搜索成功
			{				
				//LCD_Fill(0,100,lcddev.width,160,WHITE);
				//Show_Str_Mid(0,100,"刷指纹成功",16,240);	
				//printf("刷指纹成功\r\n");				
				//str=mymalloc(SRAMIN,2000);
				//sprintf(str,"确有此人,ID:%d  匹配得分:%d",seach.pageID,seach.mathscore);
				//Show_Str_Mid(0,140,(u8*)str,16,240);
				//printf("确有此人,ID:%d  匹配得分:%d",seach.pageID,seach.mathscore);
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
	 BEEP_Close();//关闭蜂鸣器
	 delay_ms(600);
	 //LCD_Fill(0,100,lcddev.width,160,WHITE);
	}
	else
		return 3;
		
}

//删除指纹
void Del_FR(void)
{
	u8  ensure;
	u16 num;
	//LCD_Fill(0,100,lcddev.width,160,WHITE);

	//Show_Str_Mid(0,100,"删除指纹",16,240);
	//Show_Str_Mid(0,120,"请输入指纹ID按Enter发送",16,240);
	//Show_Str_Mid(0,140,"0=< ID <=299",16,240);
	printf("删除指纹\r\n");
	printf("请输入指纹ID按key4发送\r\n");
	printf("0=< ID <=299\r\n");
	delay_ms(50);
	
	
	
	//AS608_load_keyboard(0,170,(u8**)kbd_delFR);
	num=GET_NUM();//获取返回的数值
	if(num==0xFFFF)
		goto MENU ; //返回主页面
	else if(num==0xFF00)
		ensure=PS_Empty();//清空指纹库
	else 
		ensure=PS_DeletChar(num,1);//删除单个指纹
	if(ensure==0)
	{
		//LCD_Fill(0,120,lcddev.width,160,WHITE);
		//Show_Str_Mid(0,140,"删除指纹成功",16,240);		
		printf("删除指纹成功\r\n");

	}
  else
		ShowErrMessage(ensure);	
	delay_ms(1200);
	PS_ValidTempleteNum(&ValidN);//读库指纹个数
	//LCD_ShowNum(56,80,AS608Para.PS_max-ValidN,3,16);
MENU:	
	//LCD_Fill(0,100,lcddev.width,160,WHITE);
	delay_ms(50);
	//AS608_load_keyboard(0,170,(u8**)kbd_menu);
}
