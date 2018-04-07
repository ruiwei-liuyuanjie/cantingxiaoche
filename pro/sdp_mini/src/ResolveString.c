/*
�ļ�����ResolveString.c     //Resolve:����    String:�ַ���
���ܣ�  �����ַ����������ַ���

*/

#include "stm32f10x.h"
#include "ResolveString.h"
#include "stdio.h"
#include "math.h"
#include "stdlib.h"
#include "traction.h"
#include "string.h"






// ǣ������
int TractionTask(const char *s)
{
    const char *ps = s;

    char *temp;
    ps = strchr(s,':')+1;
    temp = strstr(ps,"UP");
    if(temp != 0)   //���������
    {
        TRACTION_PWM_ON;
        TRACTION_UP_OFF;
        TRACTION_DOW_ON;

    }
    temp = strstr(ps,"DOW");
    if(temp != 0)   //������½�
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



str	sarray[MAX_ARRAY_LENGTH];     //sarray:����   �����Ƕ�����һ��ָ��������
char sbuffer[MAX_BUFFER_SIZE];
typedef int result;
int results[MAX_ARRAY_LENGTH];

static result __strcpy(str des,cstr src)   //des �µ�  src ԭ��
{
	int i= MAX_BUFFER_SIZE;
	while(i-- && (*des++ = *src++)!='\0' );
	if(i) return OK;
	return OUT_OF_BUFFER_LENGTH;
}

int xstrcmp (const char *p1,const char *p2)	//�ַ����ȽϺ���    ��һ���Ǳ������    �ڶ��Ǵ�������ֵ���͸���һ���Ƚ�
{
	register const char *s1 = p1;
	register const char *s2 = p2;
	register char c1, c2;
	do{
		c1 =  *s1++;     //���ֵ
		c2 =  *s2++;     //��������ֵ
		if (c1 == '\0'){
			if(c2 == ':')return 0;
			return c1 - c2;
		}
	}while (c1 == c2);
	return c1 - c2;
}

//const char *get_buffer(void)											//��ȡ���棬ֻ��
//{
	//	return (const  char *)&(ExecutionCache[0][2]);
//}
static int line2array(str cmd,str *a)   //��һ���Ǵ��ڽ��յ������飬�ڶ�����ָ������
{
//typedef char *str;
  str pbuffer;
	int count;
	char c,lastc;

	pbuffer = cmd;         //pbuffer �Ǵ��ڽ��յ��ַ���
	count = 0;
	lastc = EMPTY_CHAR;    //lastc�Ƕ���    ','
	while((c=*pbuffer)!=0)    //c��ֵ����0����
	{
			if(EMPTY_CHAR == c)   //c��ֵ�� �� ���� ����
			{
					*pbuffer = '\0';  //��,�Ż���0
			}
			else                  //c����  '��' ����
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


int dispatch(const char *cmd_line)     //�������������ַ��ʵ��Ҳ����buffer
{
	int i;
	int res,len;
//	const command *cmd;          //������һ���ṹ��ָ��

	char *p = (char*)sbuffer;    //sbuffer:��ͨ������

	res = __strcpy(p,cmd_line);				/* copy cmd line string to buffer */  //��buffer�������Ƶ�sbuffer��������»�ԭ�������ɡ�
	if(res)	return res;

	len = line2array(p,sarray);				/* convert string buffer to array */
	                                  //�ѵ��ǽ��ַ����ֽ��ת���ַ���ָ�룿����
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


