#ifndef COMMUPROTO_H
#define COMMUPROTO_H


typedef struct
{
	char hade;           //头
	char Version;        //版本
	char SourAdd;        //源地址
	char Addr;           //目的地地址
	char Number;         //序号
	char Data[16];       //接收的数据
   short ChenkCRC16;     //校验位
	int  Count;          //接收计数 
	char Cache[23];      //接收缓存
	char temp;           //临时变量
}Communication;         //通讯格式


typedef struct
{
	char CMD;       //命令
	char Len;        //数据长度
	char Data[14];  //数据 
	char flag;      //数据有无标志，如果有数据，这个标志置1，如果没有数据，这个标志置0；
}CommunVersion01;   //版本1


#endif

