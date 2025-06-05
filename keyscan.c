#include <REGX52.H>
#include <delay.h>
#include <string.h>
#include <keyscan.h>
#include <math.h>
#include <stdlib.h>
#include <LCD1602.h>
//double myatof(char *read_in)
//{
//    int i,len,how_lone;
//    double replace_float=0;
//    len=strlen(read_in);
//    for(i=0;i<len;i++)
//    {
//        if(read_in[i]=='.')
//        {
//            how_lone=i;
//            continue;
//        }
//        replace_float=replace_float*10+read_in[i]-'0';
//        
//    }
//    return replace_float;
//}

int myisdigit (char a)
{
	  if (a>='0'&&a<='9'||a=='.')
		return 1;
		else return 0;
}



int isfuhao (char a)
{
	if (a=='+'||a=='-'||a=='*'||a=='/'||a==' ')
		  return 1;
			else return 0;	
}

void float2char(float slope,char*buffer,int n)  //�����������洢���ַ����飬�ַ�����ĳ���
{
    char temp,i,j;
    if(slope>=0)//�ж��Ƿ����0
        buffer[0] = '+';
    else
    {
        buffer[0] = '-';
        slope = -slope;
    }
    temp = (int)slope;//ȡ��������
    for(i=0;temp!=0;i++)//�����������ֵ�λ��
        temp /=10;
    temp =(int)slope;
    for(j=i;j>0;j--)//����������ת�����ַ�����
    {
        buffer[j] = temp%10+'0';
        temp /=10;
    }
    buffer[i+1] = '.';
    slope -=(int)slope;
    for(i=i+2;i<n-1;i++)//��С������ת�����ַ�����
    {
        slope*=10;
        buffer[i]=(int)slope+'0';
        slope-=(int)slope;
    }
    buffer[n-1] = '\0';
}
int my_strlen(const char* str)
{
	char count = 0;//count������¼�ַ������ַ�����
	 while(*str != '\0')//������Ԫ�ص�ַ��ʼһ����������'\0',����¼�ҵ����ַ�����
	{
		count++;
		str++;
	}
	return count;
}

float jisuan(char *temp)  
{
	double e=2.71828182;
	double num=0;
	char temp1[16]={""};
	char temp2[16]={""};
	char temp3[16]={""};
	float zhi1,zhi2;
	char i,m,biaozhi,w1,w2,top;
	char len=0;
	char fuhao='+';
	char lastfuhao='+';
	double stk[10];
	double result=0;
	top=0;
	len=my_strlen(temp);
	result=0;
	for(i=0;i<10;i++)
	{
		stk[i]=0;
	}
	for(i=0;i<len;i++)
	{		
	if (myisdigit(temp[i])) //ת����������
		{
			if(temp[i]>='0'&&temp[i]<='9')
			num = num * 10 + (int)(temp[i] - '0');		
		  if(temp[i]=='.')
			{m=i;biaozhi=1;continue;}					
		}
	if(!myisdigit(temp[i])||i==len-1||temp[i]=='\0') //ɨ��ֹͣ�ж�
	{		
		
		if(temp[i]=='(')   //�������⴦���ж�
	{
		w1=i;
		for(i;i<len;i++)
		{
			if(temp[i]==')')			
			{w2=i;break;}
		}
		strncpy(temp1, temp+w1+1, w2-w1-1);
		num=jisuan1(temp1);
	}	
        if(biaozhi)   //ת��С��
		{
		if(isfuhao(temp[i]))
		num=num*pow(0.1,i-m-1);
		else
		num=num*pow(0.1,i-m);
		biaozhi=0;
		}	
	  switch(fuhao)
		{
		case '+':stk[top]=num;top++;break;
		case '-':stk[top]=-num;top++;break;
		case '*':stk[top-1]*=num;break;
		case '/':stk[top-1]/=num;break;		         
		}
		num=0;
		lastfuhao=fuhao;
		fuhao=temp[i];
	}		
	}
	for(i=0;i<top;i++)
	{
		result+=stk[i];
	}	
	LCD_ShowNum(2,8,result,5);
		return result;
}

float jisuan1(char *temp)
{
	double num=0;
	char i,len,m,biaozhi;
	char fuhao='+';
	char lastfuhao='-';
	char top;
	double stk1[5];
	double result=0;
	top=0;
	len=strlen(temp);
	for(i=0;i<len;i++)
	{
	if (myisdigit(temp[i]))
		{
			if(temp[i]>='0'&&temp[i]<='9')
			num = num * 10 + (int)(temp[i] - '0');		
		  if(temp[i]=='.')
			{m=i;biaozhi=1;continue;}					
		}
	if(!myisdigit(temp[i])||i==len-1||temp[i]=='\0')
	{		
		if(biaozhi)
		{
		if(isfuhao(temp[i]))
		num=num*pow(0.1,i-m-1);
		else
		num=num*pow(0.1,i-m);
		biaozhi=0;
		}	
	  switch(fuhao)
		{
		case '+':stk1[top]=num;top++;break;
		case '-':stk1[top]=-num;top++;break;
		case '*':stk1[top-1]*=num;break;
		case '/':stk1[top-1]/=num;break;
		
		}
		num=0;
		lastfuhao=fuhao;
		fuhao=temp[i];
	}		
	}
	for(i=0;i<top;i++)
	{
		result+=stk1[i];
	}	
		return result;
}

