#include "stm32f10x.h"
#include "traction.h"
#include "stdio.h"
#include <string.h>
#include "resolvestring.h"


/*
������:  void TractionInit(void)
����: ǣ��GPIO��ʼ��  ʹ�õ��� PD1 PD2 PD3

*/
void TractionInit(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
//    GPIO_InitStructure.GPIO_Pin = TRACTION_PWM_PIN| TRACTION_UP_PIN| TRACTION_DOW_PIN;
    GPIO_InitStructure.GPIO_Pin = TRACTION_DOW_PIN;

    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
    GPIO_Init(GPIOD, &GPIO_InitStructure);


}




u8 ReceiveData[100]= {0};    //���ڽ�������
u8 ReceiveOKFlag = 0;


void UART4_IRQHandler(void)
{
    static u8 USART4ReceiveData[100];
    static u8 USART4Count = 0;
    u8 data;
	if(USART_GetFlagStatus(UART4,USART_IT_RXNE)==SET) //��ý��ձ�־λ
	{

            data = USART_ReceiveData(UART4);       //��ý��յ�����
            USART4ReceiveData[USART4Count] = data;

            if((USART4Count == 0 ) & (data != 0x02))   //���ǿ�ͷ
            {
                goto GO;
            }

            if(data == 0)      //������־
            {
                if(USART4ReceiveData[USART4Count-1] != 0x03)  //û���յ�������־
                {
                    USART4Count = 0;
                    goto GO;
                }else{           //�յ���־λ ������������
                    strcpy(ReceiveData,&USART4ReceiveData[1]);
                    USART4Count = 0;
                    ReceiveOKFlag = 1;
                    goto GO;
                }


            }

        USART4Count++;

	}
GO:	if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)
	{
		/* ��������жϱ�־*/
		USART_ClearITPendingBit(UART4, USART_IT_RXNE);
	}
}


/*******************************************************
�� �� ���� uint8_t CheckSum(uint8_t *datatable,uint8_t num)
��    �ܣ� У��
��������� datatable��ҪУ�������  num������
�� �� ֵ�� ��
�޸ļ�¼��
(1)
*******************************************************/
uint8_t CheckSum(uint8_t *datatable,uint8_t num)
{
    uint8_t i,temp;
    temp=datatable[0];
    for(i=1;i<num;i++)
    {
        temp=temp^datatable[i];
    }
    return temp;
}


//�Լ�����Ĺ���
void myFun(void)
{
    if(ReceiveOKFlag == 1)    //����յ���Ч����
    {
        ReceiveOKFlag = 0;
        dispatch(ReceiveData);   //��������
    }

}



void myUART4Init(void)  //����4����  ����ǣ��������������
{
        USART_InitTypeDef USART_InitStructure;
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);

      USART_InitStructure.USART_BaudRate = 115200;
      USART_InitStructure.USART_WordLength = USART_WordLength_8b;
      USART_InitStructure.USART_StopBits = USART_StopBits_1;
      USART_InitStructure.USART_Parity = USART_Parity_No;
      USART_InitStructure.USART_HardwareFlowControl= USART_HardwareFlowControl_None;
      USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
      USART_Init(UART4, &USART_InitStructure);
      USART_Cmd(UART4, ENABLE);
      USART_ITConfig(UART4,USART_IT_RXNE,ENABLE);     //ʹ�ܶ��ж�

}










