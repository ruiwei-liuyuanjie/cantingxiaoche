/*

文件名：COMMUNPROTO.C
功   能：通讯协议
说明：用于通讯使用

__________________________________________________
总体协议：											 |
字节数：       1Byte    1Byte    N Byte     2Byte    |
            头       版本       数据体      CRC16    |
_____________________________________________________|





__________________________________________________________
版本1：                                                   |
——————————————————————————————————————————————————————————|
                       数据体内容						  |
字节数：      2Byte        2Byte      1Byte     N Byte    |
              序号         长度       命令      参数      |
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
	}else if(pCommuni->Count == 1){      //接收版本号

	}


}









