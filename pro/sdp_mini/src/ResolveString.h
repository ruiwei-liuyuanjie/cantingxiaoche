
#ifndef RESOLVESTRING_H
#define RESOLVESTRING_H
#include "stm32f10x.h"


typedef int (*CMDFUNC)(const char*);//������CMDFUNC������Ϊ����ָ���ͬ���֣��ú�����һ��const char* ���Ͳ����Լ�һ��int���͵ķ���ֵ

/**********************�궨��*********************************/
typedef const char *cstr;
typedef char  *CSTR;
typedef char *str;

#define MAX_ARRAY_LENGTH	(30)
#define MAX_BUFFER_SIZE		(150)
#define EMPTY_CHAR		     ','
#define PROM_STR			     ">"

#define OK							           (	 0	)
#define USER_RETURN_OK				     (	 0	)
#define CANNOT_FIND_AVILID_CMD		 (	-1	)
#define OUT_OF_BUFFER_LENGTH		   (	-2	)
#define OUT_OF_ARRAY_LENTH			   (	-3	)
#define CON_DEBUG	0


typedef struct{
	CSTR name;
	char flagc;
	int (*func)(const char* arg) ;
} command;

typedef struct {
	CSTR name;
	CMDFUNC function;
} CMD_ITEM;


extern command  cmd_list[];

int dispatch(const char *cmd_line);     //�������������ַ��ʵ��Ҳ����buffer

int cmdFunctions(char *s);




#endif
