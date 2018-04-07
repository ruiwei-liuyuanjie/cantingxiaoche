/*
文件名：ResolveString.c     //Resolve:解析    String:字符串
功能：  解析字符串，翻译字符串

*/

#include "stm32f10x.h"
#include "ResolveString.h"
#include "stdio.h"
#include "math.h"
#include "stdlib.h"
#include "traction.h"
#include "string.h"






// 牵引动作
int TractionTask(const char *s)
{
    const char *ps = s;

    char *temp;
    ps = strchr(s,':')+1;
    temp = strstr(ps,"UP");
    if(temp != 0)   //如果是上升
    {
        TRACTION_PWM_ON;
        TRACTION_UP_OFF;
        TRACTION_DOW_ON;

    }
    temp = strstr(ps,"DOW");
    if(temp != 0)   //如果是下降
    {


    TRACTION_PWM_ON;
    TRACTION_DOW_OFF;
    TRACTION_UP_ON;


    }
    return 0;
}

CMD_ITEM  ctrl_fun_list[]={

    {"TractionTask",TractionTask},
    {" ",0,},


};



str	sarray[MAX_ARRAY_LENGTH];     //sarray:函数   好像是定义了一个指针行数组
char sbuffer[MAX_BUFFER_SIZE];
typedef int result;
int results[MAX_ARRAY_LENGTH];

static result __strcpy(str des,cstr src)   //des 新的  src 原来
{
	int i= MAX_BUFFER_SIZE;
	while(i-- && (*des++ = *src++)!='\0' );
	if(i) return OK;
	return OUT_OF_BUFFER_LENGTH;
}

int xstrcmp (const char *p1,const char *p2)	//字符串比较函数    第一个是表的内容    第二是传进来的值，和个第一个比较
{
	register const char *s1 = p1;
	register const char *s2 = p2;
	register char c1, c2;
	do{
		c1 =  *s1++;     //表的值
		c2 =  *s2++;     //传进来的值
		if (c1 == '\0'){
			if(c2 == ':')return 0;
			return c1 - c2;
		}
	}while (c1 == c2);
	return c1 - c2;
}

//const char *get_buffer(void)											//获取缓存，只读
//{
	//	return (const  char *)&(ExecutionCache[0][2]);
//}
static int line2array(str cmd,str *a)   //第一个是串口接收到的数组，第二个是指针数组
{
//typedef char *str;
  str pbuffer;
	int count;
	char c,lastc;

	pbuffer = cmd;         //pbuffer 是串口接收的字符串
	count = 0;
	lastc = EMPTY_CHAR;    //lastc是逗号    ','
	while((c=*pbuffer)!=0)    //c的值不是0进入
	{
			if(EMPTY_CHAR == c)   //c的值是 ‘ ，’ 进入
			{
					*pbuffer = '\0';  //将,号换成0
			}
			else                  //c不是  '，' 进入
			{
					if(EMPTY_CHAR == lastc)
					{
							if(count>=MAX_ARRAY_LENGTH)
									return -1;
							a[count++]=pbuffer;
					}
			}
			lastc = c;
			++pbuffer;
	}
	if('\n' == *(--pbuffer))
		*(--pbuffer) = '\0';
	return count;
}

int cmdFunctions(char *s)
{
	const CMD_ITEM *tab = &ctrl_fun_list[0];
	const char *nm;
	while(*(nm=tab->name)){
		if(xstrcmp(nm,s)==0)
			break;
		tab++;
	}
	if(*nm){
		return tab->function(s);
	}
	return 0;
}


int dispatch(const char *cmd_line)     //传进来的数组地址，实际也就是buffer
{
	int i;
	int res,len;
//	const command *cmd;          //定义了一个结构体指针

	char *p = (char*)sbuffer;    //sbuffer:普通的数组

	res = __strcpy(p,cmd_line);				/* copy cmd line string to buffer */  //将buffer的数复制到sbuffer里，可能是怕或坏原来的数吧。
	if(res)	return res;

	len = line2array(p,sarray);				/* convert string buffer to array */
	                                  //难道是将字符串分解后转成字符串指针？？？
	if(len==0)	return CANNOT_FIND_AVILID_CMD;
	if(len<0)	return OUT_OF_ARRAY_LENTH;

	for(i=0;i<len;i++){	/* translate cmd array */
//		res = translate_cmd(sarray[i],&cmd);/* translate a cmd string */
			res = cmdFunctions(sarray[i]);/* translate a cmd string */
		if(res)	return res;

//		results[i] = cmd->func(sarray[i]+1);		/* run a cmd process */
	}
	return len;								/* normol return length of array */
}


