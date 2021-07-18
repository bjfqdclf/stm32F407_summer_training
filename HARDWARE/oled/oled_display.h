#ifndef __OLED_DISPLAY_H
#define __OLED_DISPLAY_H

#include "stm32f4xx.h"
#include <stdio.h>
#include <string.h>

// printf("==================1、录指纹===============\r\n");
void OLED_Dispaly_1(void);


//printf("请按指纹\r\n");
void OLED_Dispaly_2(void);

//printf("指纹正常\r\n");
void OLED_Dispaly_3(void);

//printf("请按再按一次指纹\r\n");
void OLED_Dispaly_4(void);

//printf("对比两次指纹\r\n");
void OLED_Dispaly_5(void);


// 开机界面 温度temp_num 湿度hum_num
void OLED_Dispaly_Boot(void);

// 系统主界面 choose 控制选项
void OLED_Dispaly_System(void);
// 系统主界面choose刷新
void OLED_Dispaly_System_choose(int choose);

// 指纹模式界面
void OLED_Dispaly_System_Psmod(void);
// 指纹识别正确
void OLED_Dispaly_System_Psmod_Right(void);
// 指纹错误
void OLED_Dispaly_System_Psmod_False(void);

// 密码模式
void OLED_Dispaly_System_Pwdmod(void);
// 密码模式choose
void OLED_Dispaly_System_Pwdmod_Choose(int choose);
// 密码更新
void OLED_Dispaly_System_Pwdmod_Pwd(void);

// 密码正确
void OLED_Dispaly_System_Pwdmod_Right(void);
// 密码错误
void OLED_Dispaly_System_Pwdmod_False(void);


// 管理员主界面
void OLED_Dispaly_Admin(void);
// 管理员主界面 choose刷新
void OLED_Dispaly_Admin_Choose(int choose);

// 管理员系统主界面
void OLED_Dispaly_Admin_System(void);
// 管理员系统主界面choose刷新
void OLED_Dispaly_Admin_System_Chooose(int choose);

// 密码输入过多警告
void  OLED_Dispaly_Warming(void);
#endif /* __USART_H */