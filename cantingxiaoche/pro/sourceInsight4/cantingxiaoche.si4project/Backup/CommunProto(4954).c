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
	}else if(pCommuni->Count > 22)  //数据接收完后先进行校验，校验完后再进行数据处理
		{
			//在此校验数据     从数组1到数组20 数组0是开始  数组21 22是校验值   
			if(1)//校验正确
				{
					
				}
			else {   //教研失败
			
				}
		}


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


}









