
#ifndef RESOLVESTRING_H
#define RESOLVESTRING_H
#include "stm32f10x.h"


typedef int (*CMDFUNC)(const char*);//引入了CMDFUNC类型作为函数指针的同义字，该函数有一个const char* 类型参数以及一个int类型的返回值

/**********************宏定义*********************************/
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

int dispatch(const char *cmd_line);     //传进来的数组地址，实际也就是buffer

int cmdFunctions(char *s);




#endif
