#ifndef TRACTION_H
#define TRACTION_H
#include "stm32f10x.h"



//牵引电机管脚定义
//牵引电机PWM控制信号
#define TRACTION_PWM_GPIO           GPIOD
#define TRACTION_PWM_PIN            GPIO_Pin_2
#define TRACTION_PWM_ON             GPIO_SetBits(TRACTION_PWM_GPIO, TRACTION_PWM_PIN)
#define TRACTION_PWM_OFF            GPIO_ResetBits(TRACTION_PWM_GPIO, TRACTION_PWM_PIN)

//牵引电机上升
#define TRACTION_UP_GPIO            GPIOD
#define TRACTION_UP_PIN             GPIO_Pin_3
#define TRACTION_UP_ON              GPIO_SetBits(TRACTION_UP_GPIO,TRACTION_UP_PIN)
#define TRACTION_UP_OFF             GPIO_ResetBits(TRACTION_UP_GPIO,TRACTION_UP_PIN)



//牵引电机下降
#define TRACTION_DOW_GPIO           GPIOD
#define TRACTION_DOW_PIN            GPIO_Pin_1
#define TRACTION_DOW_ON             GPIO_SetBits(TRACTION_DOW_GPIO,TRACTION_DOW_PIN)
#define TRACTION_DOW_OFF            GPIO_ResetBits(TRACTION_DOW_GPIO,TRACTION_DOW_PIN)




void TractionInit(void);   // 牵引GPIO初始化
void myFun(void);          //自己定义的功能
void myUART4Init(void);    //串口4配置  用于牵引棒电机命令接收


#endif

