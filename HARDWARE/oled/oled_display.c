#include "oled_display.h"
#include "oled.h"
#include "dht11.h"
#include "hc_sr04.h"

extern char password_buf[];	// 密码设置
// printf("==================1、录指纹===============\r\n");
void OLED_Dispaly_1(void)
{
	OLED_Clear();
//	OLED_ShowChar(25,0,'f',16);
//	OLED_ShowChar(37,0,'h',16);
//	OLED_ShowChar(49,0,'q',16);	

	OLED_ShowCHinese(0,5,10);	//录，10
	OLED_ShowCHinese(18,5,11);	//指，11
	OLED_ShowCHinese(36,5,12);	//纹，12
}

//printf("请按指纹\r\n");
void OLED_Dispaly_2(void)
{
	OLED_Clear();	

	OLED_ShowCHinese(0,5,10);	//请，10
	OLED_ShowCHinese(18,5,11);	//按，13
	OLED_ShowCHinese(36,5,11);	//指，11
	OLED_ShowCHinese(54,5,12);	//纹，12
}

//printf("指纹正常\r\n");
void OLED_Dispaly_3(void)
{
	OLED_Clear();
	
	OLED_ShowCHinese(0,5,11);	//指，11
	OLED_ShowCHinese(18,5,12);	//纹，12
	OLED_ShowCHinese(36,5,14);	//正，14
	OLED_ShowCHinese(54,5,15);	//常，15
}

//printf("请按再按一次指纹\r\n");
void OLED_Dispaly_4(void)
{
	OLED_Clear();
	OLED_ShowCHinese(0,5,16);	//请，16
	OLED_ShowCHinese(18,5,17);	//再，17
	OLED_ShowCHinese(36,5,13);	//按，13
	OLED_ShowCHinese(54,5,18);	//一，18
	OLED_ShowCHinese(72,5,19);	//次，19
	OLED_ShowCHinese(90,5,11);	//指，11
	OLED_ShowCHinese(108,5,12);	//纹，12
}

//printf("对比两次指纹\r\n");;
void OLED_Dispaly_5(void)
{
	OLED_Clear();
	
	OLED_ShowCHinese(0,5,20);	//对，20
	OLED_ShowCHinese(18,5,21);	//比，21
	OLED_ShowCHinese(36,5,22);	//两，22
	OLED_ShowCHinese(54,5,19);	//次，19
	OLED_ShowCHinese(72,5,11);	//指，11
	OLED_ShowCHinese(90,5,12);	//纹，12
}

//printf("请按再按一次指纹\r\n");
void OLED_Dispaly_6(void)
{
	OLED_Clear();

	OLED_ShowCHinese(0,5,10);	//录，10
	OLED_ShowCHinese(18,5,11);	//指，11
	OLED_ShowCHinese(36,5,12);	//纹，12
}


// 开机界面 温度temp_num 湿度hum_num
void OLED_Dispaly_Boot(void)
{
	int  temp_num;
	int hum_num;
	//获取温湿度模块数据
	char dht11_buf[5]={0};			//温湿度模块数据存储数组
	int dht11_ret=0;			//温湿度返回值
	temp_num=dht11_buf[2];
	hum_num=dht11_buf[0];
		
	dht11_ret = DHT11_Get_Data(dht11_buf);
	OLED_Clear();
	OLED_ShowCHinese(28,0,3);	//开，3
	OLED_ShowCHinese(46,0,4);	//机，4
	OLED_ShowCHinese(64,0,5);	//状，5
	OLED_ShowCHinese(82,0,6);	//态，6
	OLED_ShowChar(100,0,'***',3);

	
	OLED_ShowCHinese(14,3,0);	//温，0
	OLED_ShowCHinese(32,3,1);	//度，1
	OLED_ShowNum(50,3,temp_num,3,16);	// 数字
	OLED_ShowCHinese(86,3,1);	//度，1
	
	OLED_ShowCHinese(14,5,2);	//湿，2
	OLED_ShowCHinese(32,5,1);	//度，1
	OLED_ShowNum(50,5,hum_num,3,16);	// 数字
	OLED_ShowString(86,5,"SH",16);

}


// 系统主界面
void OLED_Dispaly_System(void)
{
	OLED_Clear();
	OLED_ShowCHinese(16,0,23);	//智，23
	OLED_ShowCHinese(32,0,24);	//能，24
	OLED_ShowCHinese(48,0,25);	//门，25
	OLED_ShowCHinese(64,0,26);	//锁，26
	OLED_ShowCHinese(80,0,27);	//系，27
	OLED_ShowCHinese(96,0,28);	//统，28
	
	OLED_ShowCHinese(10,2,29);	//指，29
	OLED_ShowCHinese(24,2,30);	//纹，30
	OLED_ShowCHinese(38,2,31);	//解，31
	OLED_ShowCHinese(52,2,32);	//锁，32
	OLED_ShowCHinese(66,2,53);	//模，53
	OLED_ShowCHinese(80,2,54);	//式，54
	
	OLED_ShowCHinese(10,4,35);	//按，35
	OLED_ShowCHinese(24,4,36);	//键，36
	OLED_ShowCHinese(38,4,37);	//密，37
	OLED_ShowCHinese(53,4,38);	//码，38
	OLED_ShowCHinese(52,4,31);	//解，31
	OLED_ShowCHinese(66,4,32);	//锁，32
	OLED_ShowCHinese(80,4,53);	//模，53
	OLED_ShowCHinese(94,4,54);	//式，54
	
	OLED_ShowCHinese(10,6,43);	//后，43
	OLED_ShowCHinese(24,6,44);	//台，44
	OLED_ShowCHinese(38,6,45);	//管，45
	OLED_ShowCHinese(52,6,46);	//理，46
	OLED_ShowCHinese(66,6,47);	//系，47
	OLED_ShowCHinese(80,6,48);	//统，48
	
	
	

}
// 系统主界面choose刷新
void OLED_Dispaly_System_choose(int choose)
{
	switch(choose){
		case 1:
			OLED_ShowChar(0,2,'>',12);
			OLED_ShowChar(0,4,' ',12);
			OLED_ShowChar(0,6,' ',12);
			break;

		case 2:
			OLED_ShowChar(0,2,' ',12);
			OLED_ShowChar(0,4,'>',12);
			OLED_ShowChar(0,6,' ',12);
			break;

		case 3:
			OLED_ShowChar(0,2,' ',12);
			OLED_ShowChar(0,4,' ',12);
			OLED_ShowChar(0,6,'>',12);
			break;
		
		default:
		break;
	}
}


// 指纹模式界面
void OLED_Dispaly_System_Psmod(void)
{
	OLED_Clear();
//	OLED_DrawBMP(0,0,128,8,BMP_Clock);
}

// 指纹识别正确
void OLED_Dispaly_System_Psmod_Right(void)
{
	OLED_Clear();
	//OLED_DrawBMP(0,0,128,8,BMP3);
}

// 指纹错误
void OLED_Dispaly_System_Psmod_False(void)
{
	OLED_Clear();
//	OLED_DrawBMP(0,0,128,8,BMP_Clock);
}


// 密码模式password_buf[] 
void OLED_Dispaly_System_Pwdmod(void)
{	
	
	OLED_Clear();
	OLED_ShowCHinese(16,0,35);	//按，35
	OLED_ShowCHinese(32,0,36);	//键，36
	OLED_ShowCHinese(48,0,37);	//密，37
	OLED_ShowCHinese(64,0,38);	//码，38
	OLED_ShowCHinese(80,0,53);	//模，53
	OLED_ShowCHinese(96,0,54);	//式，54
	


}
	// 密码模式choose
void OLED_Dispaly_System_Pwdmod_Choose(int choose)
{
		switch(choose){
	case 1:
		OLED_ShowChar(36,6,'^',16);
		OLED_ShowChar(54,6,' ',16);
		OLED_ShowChar(72,6,' ',16);
		OLED_ShowChar(90,6,' ',16);
		break;

	case 2:
		OLED_ShowChar(36,6,' ',16);
		OLED_ShowChar(54,6,'^',16);
		OLED_ShowChar(72,6,' ',16);
		OLED_ShowChar(90,6,' ',16);
		break;

	case 3:
		OLED_ShowChar(36,6,' ',16);
		OLED_ShowChar(54,6,' ',16);
		OLED_ShowChar(72,6,'^',16);
		OLED_ShowChar(90,6,' ',16);
		break;
	case 4:
		OLED_ShowChar(36,6,' ',16);
		OLED_ShowChar(54,6,' ',16);
		OLED_ShowChar(72,6,' ',16);
		OLED_ShowChar(90,6,'^',16);
		break;
	
	default:
	break;
}
}
// 密码更新
void OLED_Dispaly_System_Pwdmod_Pwd(void)
{
	int i=0;
	for(i=0;i<4;i++)
	{
		if(password_buf[i]==NULL){
			OLED_ShowChar(36+i*18,4,'-',16);
		}else{
			OLED_ShowNum(36+i*18,4,password_buf[i],1,16);
		}
	}	
}
// 密码正确
void OLED_Dispaly_System_Pwdmod_Right(void)
{
	OLED_Clear();
	//OLED_DrawBMP(0,0,128,8,BMP3);
}
// 密码错误
void OLED_Dispaly_System_Pwdmod_False(void)
{
	OLED_Clear();
//	OLED_DrawBMP(0,0,128,8,BMP_Clock);
}

// 管理员主界面
void OLED_Dispaly_Admin(void)
{
	OLED_Clear();
	OLED_ShowCHinese(16,0,98);	//后，98
	OLED_ShowCHinese(32,0,99);	//台，99
	OLED_ShowCHinese(48,0,100);	//管，100
	OLED_ShowCHinese(64,0,101);	//理，101
	OLED_ShowCHinese(80,0,27);	//系，27
	OLED_ShowCHinese(96,0,28);	//统，28
	
	OLED_ShowCHinese(10,3,29);	//指，29
	OLED_ShowCHinese(24,3,30);	//纹，30
	OLED_ShowCHinese(38,3,31);	//解，31
	OLED_ShowCHinese(52,3,32);	//锁，32
	OLED_ShowCHinese(66,3,37);	//密，37
	OLED_ShowCHinese(80,3,38);	//码，38
	
	OLED_ShowCHinese(10,5,35);	//按，35
	OLED_ShowCHinese(24,5,36);	//键，36
	OLED_ShowCHinese(38,5,37);	//密，37
	OLED_ShowCHinese(53,5,38);	//码，38
	OLED_ShowCHinese(52,5,31);	//解，31
	OLED_ShowCHinese(66,5,32);	//锁，32
	OLED_ShowCHinese(80,5,37);	//密，37
	OLED_ShowCHinese(94,5,38);	//码，38
	

}
// 管理员主界面 choose刷新
void OLED_Dispaly_Admin_Choose(int choose)
{
		switch(choose){
		case 1:
			OLED_ShowChar(0,3,'>',12);
			OLED_ShowChar(0,5,' ',12);
			break;

		case 2:
			OLED_ShowChar(0,3,' ',12);
			OLED_ShowChar(0,5,'>',12);
			break;
		
		default:
		break;
	}
}

// 管理员系统主界面
void OLED_Dispaly_Admin_System(void)
{
	OLED_Clear();
	OLED_ShowCHinese(16,0,43);	//后，43
	OLED_ShowCHinese(32,0,44);	//台，44
	OLED_ShowCHinese(48,0,45);	//管，45
	OLED_ShowCHinese(64,0,46);	//理，46
	OLED_ShowCHinese(80,0,27);	//系，27
	OLED_ShowCHinese(96,0,28);	//统，28
	
	OLED_ShowCHinese(10,2,216);	//录，216
	OLED_ShowCHinese(24,2,29);	//指，29
	OLED_ShowCHinese(38,2,30);	//纹，30
	
	OLED_ShowCHinese(10,4,217);	//删，217
	OLED_ShowCHinese(24,4,218);	//除，218
	OLED_ShowCHinese(38,4,29);	//指，29
	OLED_ShowCHinese(53,4,30);	//纹，30

	
	OLED_ShowCHinese(10,6,219);	//设，219
	OLED_ShowCHinese(24,6,220);	//置，220
	OLED_ShowCHinese(38,6,35);	//按，35
	OLED_ShowCHinese(52,6,36);	//键，36
	OLED_ShowCHinese(66,6,37);	//密，37
	OLED_ShowCHinese(80,6,38);	//码，38	

}
// 管理员系统主界面choose刷新
void OLED_Dispaly_Admin_System_Choose(int choose)
{
	switch(choose){
		case 1:
			OLED_ShowChar(0,2,'>',12);
			OLED_ShowChar(0,4,' ',12);
			OLED_ShowChar(0,6,' ',12);
			break;

		case 2:
			OLED_ShowChar(0,2,' ',12);
			OLED_ShowChar(0,4,'>',12);
			OLED_ShowChar(0,6,' ',12);
			break;

		case 3:
			OLED_ShowChar(0,2,' ',12);
			OLED_ShowChar(0,4,' ',12);
			OLED_ShowChar(0,6,'>',12);
			break;
		
		default:
		break;
	}
}

// 密码输入过多警告
void  OLED_Dispaly_Warming(void)
{
	OLED_Clear();
	OLED_ShowCHinese(16,3,37);	//密，37
	OLED_ShowCHinese(32,3,38);	//码，38
	OLED_ShowCHinese(48,3,221);	//错，221
	OLED_ShowCHinese(64,3,222);	//误222
	OLED_ShowCHinese(80,3,223);	//过，223
	OLED_ShowCHinese(96,3,224);	//多，224
	
}