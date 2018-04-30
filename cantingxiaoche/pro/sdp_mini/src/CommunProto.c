/*

文件名：COMMUNPROTO.C
功   能：通讯协议
说明：用于通讯使用

___________________________________________________________________________
通讯底层协议：											                          |
字节数：       1Byte    1Byte    1Byte    1Byte    1Byte  16Byte     2Byte    |
            头       版本      源地址       目的地       序号     数据        CRC16    |
__________________________________________________________________________|





__________________________________________________________
版本1：                                                   |
——————————————————————————————————————————————————————————|
                       数据体内容						  |
字节数：        1Byte      1Byte     N Byte    |
                                          |
——————————————————————————————————————————————————————————|


*/

#include "communproto.h"

CommunVersion01  CommunVer01;






/*
函数名：int ReceiveData(char *pdata)
功   能：接收到一帧数据 16个数据
*/
static int ReceiveData(char *pdata)
{
		int i;
		CommunVer01.CMD =  pdata[0];
		CommunVer01.Len =  pdata[1];
		for(i = 0;i < 16;i++)
			{
				CommunVer01.Data[i] = pdata[i+2];
			}
		CommunVer01.flag = 1;   //将这个标志置1
}

/*
函数名：int  ReadOneByte(char data)
功能：接收到一个字节后对其进行处理
参数： data,接收到的数据，                  pCommuni:接收结构体
*/
int  ReadOneByte(char data,Communication * pCommuni)
{
	if(pCommuni->Count == 0 )            //接收头部分
	{
		if (data == 0xaa)    //判断是否为头
			{
				pCommuni->Count++;
			}
		else{
				pCommuni->Count = 0;
			}
	}else if(pCommuni->Count > 0 & pCommuni->Count < 23) //接收数据，先将所有数据缓存起来
	{
		pCommuni->Cache[pCommuni->Count]=data;
		pCommuni->Count++;
	}
	if(pCommuni->Count == 22)  //数据接收完后先进行校验，校验完后再进行数据处理
		{
			//在此校验数据     从数组1到数组20 数组0是开始  数组21 22是校验值   
			if(1)//校验正确
				{
					pCommuni->Count = 0;
					pCommuni->Version = pCommuni->Cache[1];
					pCommuni->Addr = pCommuni->Cache[3];
					pCommuni->ChenkCRC16 = pCommuni->Cache[21] << 8 | pCommuni->Cache[22];
					if(pCommuni->Addr != 1 & pCommuni->Addr != 0)   // 不等于本地地址与不等于广播地址 说明不是给本机传的
						{
							
							return -1;
						}
 					else {          //是传给本地的
							pCommuni->SourAdd = pCommuni->Cache[2];
							pCommuni->Number = pCommuni->Cache[4];
					        for(pCommuni->temp = 0;pCommuni->temp < 16;pCommuni->temp++)
					        	{
									pCommuni->Data[pCommuni->temp] = pCommuni->Cache[pCommuni->temp+5];
					        	}
						}
					ReceiveData(&pCommuni->Data);    //将收到的数据传递给另一个函数。
				}
			else {   //教研失败
							return -1;
				}
		}

#if 0
		else if(pCommuni->Count == 1){      //接收版本号
		pCommuni->Version = data;
		pCommuni->Count++;
	}else if(pCommuni->Count ==	2)
	{
		pCommuni->SourAdd = data;
		pCommuni->Count++;
	}else if(pCommuni->Count == 3)
	{
		pCommuni->Addr = data;
		pCommuni->Count++;

	}else if(pCommuni->Count == 4)
	{
		pCommuni->Number = data;
		pCommuni->Count++;
	}else if(pCommuni->Count > 4 & pCommuni->Count < 21)        //接收数据体
	{
	    pCommuni->Count++;
		switch (pCommuni->Version)
		{
			case 0x01:    //版本1
			{
				 pCommuni->Data[pCommuni->Count - 3 ] = data;
				 


			
				break;
			}
			
			
		}
		
	}
#endif

}









