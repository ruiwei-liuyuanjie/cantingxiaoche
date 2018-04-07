#ifndef TRACTION_H
#define TRACTION_H
#include "stm32f10x.h"



//ǣ������ܽŶ���
//ǣ�����PWM�����ź�
#define TRACTION_PWM_GPIO           GPIOD
#define TRACTION_PWM_PIN            GPIO_Pin_2
#define TRACTION_PWM_ON             GPIO_SetBits(TRACTION_PWM_GPIO, TRACTION_PWM_PIN)
#define TRACTION_PWM_OFF            GPIO_ResetBits(TRACTION_PWM_GPIO, TRACTION_PWM_PIN)

//ǣ���������
#define TRACTION_UP_GPIO            GPIOD
#define TRACTION_UP_PIN             GPIO_Pin_3
#define TRACTION_UP_ON              GPIO_SetBits(TRACTION_UP_GPIO,TRACTION_UP_PIN)
#define TRACTION_UP_OFF             GPIO_ResetBits(TRACTION_UP_GPIO,TRACTION_UP_PIN)



//ǣ������½�
#define TRACTION_DOW_GPIO           GPIOD
#define TRACTION_DOW_PIN            GPIO_Pin_1
#define TRACTION_DOW_ON             GPIO_SetBits(TRACTION_DOW_GPIO,TRACTION_DOW_PIN)
#define TRACTION_DOW_OFF            GPIO_ResetBits(TRACTION_DOW_GPIO,TRACTION_DOW_PIN)




void TractionInit(void);   // ǣ��GPIO��ʼ��
void myFun(void);          //�Լ�����Ĺ���
void myUART4Init(void);    //����4����  ����ǣ��������������


#endif

