#include "oled_display.h"
#include "oled.h"
#include "dht11.h"
#include "hc_sr04.h"

extern char password_buf[];	// ��������
// printf("==================1��¼ָ��===============\r\n");
void OLED_Dispaly_1(void)
{
	OLED_Clear();
//	OLED_ShowChar(25,0,'f',16);
//	OLED_ShowChar(37,0,'h',16);
//	OLED_ShowChar(49,0,'q',16);	

	OLED_ShowCHinese(0,5,10);	//¼��10
	OLED_ShowCHinese(18,5,11);	//ָ��11
	OLED_ShowCHinese(36,5,12);	//�ƣ�12
}

//printf("�밴ָ��\r\n");
void OLED_Dispaly_2(void)
{
	OLED_Clear();	

	OLED_ShowCHinese(0,5,10);	//�룬10
	OLED_ShowCHinese(18,5,11);	//����13
	OLED_ShowCHinese(36,5,11);	//ָ��11
	OLED_ShowCHinese(54,5,12);	//�ƣ�12
}

//printf("ָ������\r\n");
void OLED_Dispaly_3(void)
{
	OLED_Clear();
	
	OLED_ShowCHinese(0,5,11);	//ָ��11
	OLED_ShowCHinese(18,5,12);	//�ƣ�12
	OLED_ShowCHinese(36,5,14);	//����14
	OLED_ShowCHinese(54,5,15);	//����15
}

//printf("�밴�ٰ�һ��ָ��\r\n");
void OLED_Dispaly_4(void)
{
	OLED_Clear();
	OLED_ShowCHinese(0,5,16);	//�룬16
	OLED_ShowCHinese(18,5,17);	//�٣�17
	OLED_ShowCHinese(36,5,13);	//����13
	OLED_ShowCHinese(54,5,18);	//һ��18
	OLED_ShowCHinese(72,5,19);	//�Σ�19
	OLED_ShowCHinese(90,5,11);	//ָ��11
	OLED_ShowCHinese(108,5,12);	//�ƣ�12
}

//printf("�Ա�����ָ��\r\n");;
void OLED_Dispaly_5(void)
{
	OLED_Clear();
	
	OLED_ShowCHinese(0,5,20);	//�ԣ�20
	OLED_ShowCHinese(18,5,21);	//�ȣ�21
	OLED_ShowCHinese(36,5,22);	//����22
	OLED_ShowCHinese(54,5,19);	//�Σ�19
	OLED_ShowCHinese(72,5,11);	//ָ��11
	OLED_ShowCHinese(90,5,12);	//�ƣ�12
}

//printf("�밴�ٰ�һ��ָ��\r\n");
void OLED_Dispaly_6(void)
{
	OLED_Clear();

	OLED_ShowCHinese(0,5,10);	//¼��10
	OLED_ShowCHinese(18,5,11);	//ָ��11
	OLED_ShowCHinese(36,5,12);	//�ƣ�12
}


// �������� �¶�temp_num ʪ��hum_num
void OLED_Dispaly_Boot(void)
{
	int  temp_num;
	int hum_num;
	//��ȡ��ʪ��ģ������
	char dht11_buf[5]={0};			//��ʪ��ģ�����ݴ洢����
	int dht11_ret=0;			//��ʪ�ȷ���ֵ
	temp_num=dht11_buf[2];
	hum_num=dht11_buf[0];
		
	dht11_ret = DHT11_Get_Data(dht11_buf);
	OLED_Clear();
	OLED_ShowCHinese(28,0,3);	//����3
	OLED_ShowCHinese(46,0,4);	//����4
	OLED_ShowCHinese(64,0,5);	//״��5
	OLED_ShowCHinese(82,0,6);	//̬��6
	OLED_ShowChar(100,0,'***',3);

	
	OLED_ShowCHinese(14,3,0);	//�£�0
	OLED_ShowCHinese(32,3,1);	//�ȣ�1
	OLED_ShowNum(50,3,temp_num,3,16);	// ����
	OLED_ShowCHinese(86,3,1);	//�ȣ�1
	
	OLED_ShowCHinese(14,5,2);	//ʪ��2
	OLED_ShowCHinese(32,5,1);	//�ȣ�1
	OLED_ShowNum(50,5,hum_num,3,16);	// ����
	OLED_ShowString(86,5,"SH",16);

}


// ϵͳ������
void OLED_Dispaly_System(void)
{
	OLED_Clear();
	OLED_ShowCHinese(16,0,23);	//�ǣ�23
	OLED_ShowCHinese(32,0,24);	//�ܣ�24
	OLED_ShowCHinese(48,0,25);	//�ţ�25
	OLED_ShowCHinese(64,0,26);	//����26
	OLED_ShowCHinese(80,0,27);	//ϵ��27
	OLED_ShowCHinese(96,0,28);	//ͳ��28
	
	OLED_ShowCHinese(10,2,29);	//ָ��29
	OLED_ShowCHinese(24,2,30);	//�ƣ�30
	OLED_ShowCHinese(38,2,31);	//�⣬31
	OLED_ShowCHinese(52,2,32);	//����32
	OLED_ShowCHinese(66,2,53);	//ģ��53
	OLED_ShowCHinese(80,2,54);	//ʽ��54
	
	OLED_ShowCHinese(10,4,35);	//����35
	OLED_ShowCHinese(24,4,36);	//����36
	OLED_ShowCHinese(38,4,37);	//�ܣ�37
	OLED_ShowCHinese(53,4,38);	//�룬38
	OLED_ShowCHinese(52,4,31);	//�⣬31
	OLED_ShowCHinese(66,4,32);	//����32
	OLED_ShowCHinese(80,4,53);	//ģ��53
	OLED_ShowCHinese(94,4,54);	//ʽ��54
	
	OLED_ShowCHinese(10,6,43);	//��43
	OLED_ShowCHinese(24,6,44);	//̨��44
	OLED_ShowCHinese(38,6,45);	//�ܣ�45
	OLED_ShowCHinese(52,6,46);	//��46
	OLED_ShowCHinese(66,6,47);	//ϵ��47
	OLED_ShowCHinese(80,6,48);	//ͳ��48
	
	
	

}
// ϵͳ������chooseˢ��
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


// ָ��ģʽ����
void OLED_Dispaly_System_Psmod(void)
{
	OLED_Clear();
//	OLED_DrawBMP(0,0,128,8,BMP_Clock);
}

// ָ��ʶ����ȷ
void OLED_Dispaly_System_Psmod_Right(void)
{
	OLED_Clear();
	//OLED_DrawBMP(0,0,128,8,BMP3);
}

// ָ�ƴ���
void OLED_Dispaly_System_Psmod_False(void)
{
	OLED_Clear();
//	OLED_DrawBMP(0,0,128,8,BMP_Clock);
}


// ����ģʽpassword_buf[] 
void OLED_Dispaly_System_Pwdmod(void)
{	
	
	OLED_Clear();
	OLED_ShowCHinese(16,0,35);	//����35
	OLED_ShowCHinese(32,0,36);	//����36
	OLED_ShowCHinese(48,0,37);	//�ܣ�37
	OLED_ShowCHinese(64,0,38);	//�룬38
	OLED_ShowCHinese(80,0,53);	//ģ��53
	OLED_ShowCHinese(96,0,54);	//ʽ��54
	


}
	// ����ģʽchoose
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
// �������
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
// ������ȷ
void OLED_Dispaly_System_Pwdmod_Right(void)
{
	OLED_Clear();
	//OLED_DrawBMP(0,0,128,8,BMP3);
}
// �������
void OLED_Dispaly_System_Pwdmod_False(void)
{
	OLED_Clear();
//	OLED_DrawBMP(0,0,128,8,BMP_Clock);
}

// ����Ա������
void OLED_Dispaly_Admin(void)
{
	OLED_Clear();
	OLED_ShowCHinese(16,0,98);	//��98
	OLED_ShowCHinese(32,0,99);	//̨��99
	OLED_ShowCHinese(48,0,100);	//�ܣ�100
	OLED_ShowCHinese(64,0,101);	//��101
	OLED_ShowCHinese(80,0,27);	//ϵ��27
	OLED_ShowCHinese(96,0,28);	//ͳ��28
	
	OLED_ShowCHinese(10,3,29);	//ָ��29
	OLED_ShowCHinese(24,3,30);	//�ƣ�30
	OLED_ShowCHinese(38,3,31);	//�⣬31
	OLED_ShowCHinese(52,3,32);	//����32
	OLED_ShowCHinese(66,3,37);	//�ܣ�37
	OLED_ShowCHinese(80,3,38);	//�룬38
	
	OLED_ShowCHinese(10,5,35);	//����35
	OLED_ShowCHinese(24,5,36);	//����36
	OLED_ShowCHinese(38,5,37);	//�ܣ�37
	OLED_ShowCHinese(53,5,38);	//�룬38
	OLED_ShowCHinese(52,5,31);	//�⣬31
	OLED_ShowCHinese(66,5,32);	//����32
	OLED_ShowCHinese(80,5,37);	//�ܣ�37
	OLED_ShowCHinese(94,5,38);	//�룬38
	

}
// ����Ա������ chooseˢ��
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

// ����Աϵͳ������
void OLED_Dispaly_Admin_System(void)
{
	OLED_Clear();
	OLED_ShowCHinese(16,0,43);	//��43
	OLED_ShowCHinese(32,0,44);	//̨��44
	OLED_ShowCHinese(48,0,45);	//�ܣ�45
	OLED_ShowCHinese(64,0,46);	//��46
	OLED_ShowCHinese(80,0,27);	//ϵ��27
	OLED_ShowCHinese(96,0,28);	//ͳ��28
	
	OLED_ShowCHinese(10,2,216);	//¼��216
	OLED_ShowCHinese(24,2,29);	//ָ��29
	OLED_ShowCHinese(38,2,30);	//�ƣ�30
	
	OLED_ShowCHinese(10,4,217);	//ɾ��217
	OLED_ShowCHinese(24,4,218);	//����218
	OLED_ShowCHinese(38,4,29);	//ָ��29
	OLED_ShowCHinese(53,4,30);	//�ƣ�30

	
	OLED_ShowCHinese(10,6,219);	//�裬219
	OLED_ShowCHinese(24,6,220);	//�ã�220
	OLED_ShowCHinese(38,6,35);	//����35
	OLED_ShowCHinese(52,6,36);	//����36
	OLED_ShowCHinese(66,6,37);	//�ܣ�37
	OLED_ShowCHinese(80,6,38);	//�룬38	

}
// ����Աϵͳ������chooseˢ��
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

// ����������ྯ��
void  OLED_Dispaly_Warming(void)
{
	OLED_Clear();
	OLED_ShowCHinese(16,3,37);	//�ܣ�37
	OLED_ShowCHinese(32,3,38);	//�룬38
	OLED_ShowCHinese(48,3,221);	//��221
	OLED_ShowCHinese(64,3,222);	//��222
	OLED_ShowCHinese(80,3,223);	//����223
	OLED_ShowCHinese(96,3,224);	//�࣬224
	
}