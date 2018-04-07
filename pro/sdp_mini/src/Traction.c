#include "stm32f10x.h"
#include "traction.h"
#include "stdio.h"
#include <string.h>
#include "resolvestring.h"


/*
函数名:  void TractionInit(void)
功能: 牵引GPIO初始化  使用的是 PD1 PD2 PD3

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




u8 ReceiveData[100]= {0};    //串口接收数组
u8 ReceiveOKFlag = 0;


void UART4_IRQHandler(void)
{
    static u8 USART4ReceiveData[100];
    static u8 USART4Count = 0;
    u8 data;
	if(USART_GetFlagStatus(UART4,USART_IT_RXNE)==SET) //获得接收标志位
	{

            data = USART_ReceiveData(UART4);       //获得接收的数据
            USART4ReceiveData[USART4Count] = data;

            if((USART4Count == 0 ) & (data != 0x02))   //不是开头
            {
                goto GO;
            }

            if(data == 0)      //结束标志
            {
                if(USART4ReceiveData[USART4Count-1] != 0x03)  //没有收到结束标志
                {
                    USART4Count = 0;
                    goto GO;
                }else{           //收到标志位 接收数据正常
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
		/* 清除接收中断标志*/
		USART_ClearITPendingBit(UART4, USART_IT_RXNE);
	}
}


/*******************************************************
函 数 名： uint8_t CheckSum(uint8_t *datatable,uint8_t num)
功    能： 校验
输入参数： datatable：要校验的数组  num：数量
返 回 值： 无
修改记录：
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


//自己定义的功能
void myFun(void)
{
    if(ReceiveOKFlag == 1)    //如果收到有效数据
    {
        ReceiveOKFlag = 0;
        dispatch(ReceiveData);   //解析数据
    }

}



void myUART4Init(void)  //串口4配置  用于牵引棒电机命令接收
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
      USART_ITConfig(UART4,USART_IT_RXNE,ENABLE);     //使能读中断

}










