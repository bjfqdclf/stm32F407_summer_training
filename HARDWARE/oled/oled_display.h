#ifndef __OLED_DISPLAY_H
#define __OLED_DISPLAY_H

#include "stm32f4xx.h"
#include <stdio.h>
#include <string.h>

// printf("==================1��¼ָ��===============\r\n");
void OLED_Dispaly_1(void);


//printf("�밴ָ��\r\n");
void OLED_Dispaly_2(void);

//printf("ָ������\r\n");
void OLED_Dispaly_3(void);

//printf("�밴�ٰ�һ��ָ��\r\n");
void OLED_Dispaly_4(void);

//printf("�Ա�����ָ��\r\n");
void OLED_Dispaly_5(void);


// �������� �¶�temp_num ʪ��hum_num
void OLED_Dispaly_Boot(void);

// ϵͳ������ choose ����ѡ��
void OLED_Dispaly_System(void);
// ϵͳ������chooseˢ��
void OLED_Dispaly_System_choose(int choose);

// ָ��ģʽ����
void OLED_Dispaly_System_Psmod(void);
// ָ��ʶ����ȷ
void OLED_Dispaly_System_Psmod_Right(void);
// ָ�ƴ���
void OLED_Dispaly_System_Psmod_False(void);

// ����ģʽ
void OLED_Dispaly_System_Pwdmod(void);
// ����ģʽchoose
void OLED_Dispaly_System_Pwdmod_Choose(int choose);
// �������
void OLED_Dispaly_System_Pwdmod_Pwd(void);

// ������ȷ
void OLED_Dispaly_System_Pwdmod_Right(void);
// �������
void OLED_Dispaly_System_Pwdmod_False(void);


// ����Ա������
void OLED_Dispaly_Admin(void);
// ����Ա������ chooseˢ��
void OLED_Dispaly_Admin_Choose(int choose);

// ����Աϵͳ������
void OLED_Dispaly_Admin_System(void);
// ����Աϵͳ������chooseˢ��
void OLED_Dispaly_Admin_System_Chooose(int choose);

// ����������ྯ��
void  OLED_Dispaly_Warming(void);
#endif /* __USART_H */