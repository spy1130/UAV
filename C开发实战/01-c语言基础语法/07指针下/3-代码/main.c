#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>


#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int  strstr_num(char *src, char *dst)
{
	int i = 0;
	char *p = src;
	int n = 0;
	//char src[] = "hdaabcdhaodabcahdaabchdoahdoaabcjdahfaabc";
	//char dst[] = "abc";
	//while (src[i] != 0)
	
	do
	{
		
			p = strstr(p, dst);
		
			//p = strstr(p+strlen(dst), dst);
			if (p != NULL)//������ҷ��صĵ�ַ������NULL,�����ҵ���
			{
				n++;
				p = p + strlen(dst);
			}
		
	} while (p != NULL);
	return n;
}

int main()
{
	char src[] = "hdaabcdhaodabcahdaabchdoahdoaabcjdahfaabc";
	char dst[] = "abc";
	int n = strstr_num(src,dst);
	printf("%d\n",n);
	system("pause");
	return 0;
}

//atoi   ���ַ�ת����
int main15()
{
	//0-9���ַ���+-�žͿ�ʼת,�������+- 0-9���ַ�����
	//���ǰ���пո�,����
	char  num[] = " +1234";
	char str[] = "3.14";

	int  sum = atoi(num);//1234  \r  \n  _  
	printf("%d\n",sum);

	float a = atof(str);
	printf("%f\n",a);
	system("pause");
	return 0;
}

int main14()
{
	char str[] = "15080015225&bangquan#82263&123456";
	char *p[10] = {NULL};//��ʼ��ָ������Ԫ��ȫ��ΪNULL
	//strtok
	//char *p1 = strtok(str,"#");//��str1�н�#�и�,�����и�ǰ����ַ���
	//printf("%s\n",p1);
	//char *p2 = strtok(NULL,"#");
	//printf("%s\n",p2);
	//char *p3 = strtok(NULL, "#");
	//printf("%s\n", p3);
	int i = 0;
	do {
		if(i == 0)
			p[i] = strtok(str, "#&");
		else
			p[i] = strtok(NULL, "#&");
		//i++;
	
	} while ( p[i++] != NULL);//p[i] != NULL   i=i+1 ���strtok�ķ���ֵ����NULL,�����и����
	i = 0;
	while (p[i] != NULL)
	{
		printf("%s\n",p[i++]);
	}
	printf("str=%s\n",str);
	system("pause");

	return 0;
}

char *my_strstr(char *str1, char *str2)
{
	int i = 0;
	while (str1[i] != 0)
	{
		if (str1[i] == str2[0])
		{
			if (0 == strncmp(str1 + i, str2, strlen(str2)))
				return str1 + i;
		
		}
		i++;
	
	}
	if (str1[i] == 0)
		return NULL;
}
int main13()
{
	char str1[] = "helloaabcfhaffjhafafha";
	char str2[] = "abc";
	//��str1�в���str2�ַ����ֵ�λ��
	//����a�ַ�,����ҵ���a�ַ�,�ڱȽ�
	char *p = strstr(str1,str2);
	printf("%s\n",p);


	system("pause");
	return 0;
}

char *my_strchr(char *p, char ch)
{
	int i = 0;
	while (p[i] != 0)
	{
		if (p[i] == ch)
			return &p[i];
		i++;
	}
	if (p[i] == 0)
		return NULL;


}
int main12()
{
	char  str[] = "xixihellogworld";
	char *p = strchr(str,'g');
	//char  *p =my_strchr(str,'g');
	printf("%s\n",p);

	system("pause");
	return 0;
}


int main11()
{
	//%d    0-9���ַ�
	int  year =0 ;
	int  month = 0;
	int day = 0;
	char  buf[1024] = "beijing:2018:t:10:20";
	//scanf("%d:%d:%d",&year,&month,&day);//�Ӽ��̰�����Ӧ�ĸ�ʽ��ȡ����
	sscanf(buf, "beijing:%d:t:%d:%d", &year, &month, &day);//��buf�а���`��Ӧ�ĸ�ʽ��ȡ����
	printf("%d %d %d\n",year,month,day);
	system("pause");
	return 0;
}


int main10()
{
	int  year = 2018;
	int  month = 10;
	int day = 20;
	char buf[1024] = "";
	//printf("year=%d month=%d day=%d \n",year,month,day);
	int len = sprintf(buf,"year=%d %cmonth=%d day=%d \n",year, 0,month, day);
	//printf("%d\n",strlen(buf));
	printf("len=%d\n",len);
	printf("buf=[%s]",buf);

	system("pause");
	return 0;
}


int main09()
{
	char  str1[] = "a\0bcdef";
	char str2[] = "a\0cdrrr";
	//str1�����к�str2�����ó�һ��Ԫ�ؽ��бȽ�,��ȼ�������Ƚ�
	//�Ƚϵ����ַ���asciiֵ
	//���str1> str2  ����ֵ����1
	//���str1==  str2  ����ֵ����0
	//���str1 <str2  ����ֵ���� - 1
	//printf("%d\n",strcmp(str1,str2));
	printf("%d\n", strncmp(str1, str2,3));
	system("pause");
	return 0;
}


int main08()
{
	char  str1[1024] = "123456";//wo\0\0\0      wo\0rl
	char str2[128] = "worldhello";
	//strcat(str1,str2);//��str2���ַ���������str1�ַ����ĺ���
	strncat(str1, str2,5);
	printf("%s\n",str1);

	system("pause");
	return 0;
}

int main07()
{
	char  str1[1024] = "";//wo\0\0\0      wo\0rl
	char str2[128] = "wo\0rldhello";
	//strcpy( str1 ,  str2);
	strncpy(str1,str2,5);
//	printf("%s\n",str1);
	for (int i = 0; i < 5; i++)
	{
		printf("%d ",str1[i]);
	}


	system("pause");
	return 0;
}

//.*.exe    hello   123456 
//char *argv[] = { ".*.exe",    "hello"   "123456" };
int main06(int  argc,char *argv[])
{
	/*printf("%d\n",argc);
	printf("%s\n", argv[0]);
	printf("%s\n", argv[1]);
	printf("%s\n", argv[2]);
	printf("%s\n", argv[3]);*/
	for (int i = 0; i < argc; i++)
	{
		printf("%s\n", argv[i]);
	}
	system("pause");
	return 0;
}

//�ַ�ָ������
//��һ������,ÿһ��Ԫ�����ַ�ָ��
int main05()
{
	/*char *p1 = "heihei";
	char *p2 = "haha";
	char *p3 = "xixi";*/
	//char *num[3] = { p1,p2,p3};
	char *num[3]={ "heihei" ,"haha","xixi"};
	//����һ��ָ�뱣��num������Ԫ�صĵ�ַ   &num[0]  num
	char **p = num;
	for (int i = 0; i < 3; i++)
	{
	//	printf("%s\n",*(p+i));
		printf("%s\n", p[i]);
	}
	printf("%c\n",*(*(p+1)+3));// *(p[1]+3)   == p[1][3]
	//for (int i = 0; i < 3; i++)
	//{
	//	printf("%s\n",num[i]);	
	//}
	//printf("%c\n",*num[0]);//
	//printf("%c\n", *(num[1] + 1));
	//printf("%c\n", *(num[2]+2));

	system("pause");
	return 0;
}

int main04()
{
	char  buf[] = "hello";
	char  str[] = "acbg";
	 char const *p = buf;//const����ָ��,����ͨ��ָ���޸�ָ����ָ��Ŀռ�����
	//*p = 'b';  err  ����ͨ��pָ���޸��ǿ�ռ������
	char  * const  k = buf;//ָ�����k��ʼ��֮���ܸı�kָ����������ָ��
//	k = "world"; err  
//	k = str; err
	system("pause");
	return 0;
}

char * my_strcat(char * src, char *dst)
{
	int n = strlen(src);
	int i = 0;
	while (*(dst + i) !=  0)
	{
		*(src+n+i) =   *(dst + i);
		//src[n+i] = dst[i] ;
		i++;
	
	}
	*(src + n + i) = 0;
	return src;
}

int main03()
{

	char  str1[128] = "hello";//hello123456\0
	char str2[128] = "123456";
	my_strcat(str1,str2);
	printf("%s\n",my_strcat(str1, str2));
	system("pause");
	return 0;
}


int main02()
{
	char  a[] = "helloworld";//������һ���ַ�����,�ַ���������Ϊhelloworld
							 //����һ��ָ����������������Ԫ�صĵ�ַ
	char  * p = a;
	p = "abcdef";//�ַ������������ֳ�����,""��ʹ��ʱ,ȡ�����ַ�����Ԫ�صĵ�ַ
	//���ֳ������������ǲ����Ըı��
	printf("%s\n",p);

	printf("%d\n",sizeof(p));//4
	printf("%d\n", sizeof("abcdef"));//7

	printf("%d\n", strlen(p));//6
	printf("%d\n", strlen("abcdef"));//6

	*p = 'm';
	printf("%s\n",p);


	system("pause");
	return 0;
}

//Shell   python  lua
int main01()
{
	//ָ�����ַ���
	char  a[] = "helloworld";//������һ���ַ�����,�ַ���������Ϊhelloworld\0
	//����һ��ָ����������������Ԫ�صĵ�ַ
	char  * p = a;
	printf("%s\n",p);//%s��ӡһ���ַ���,Ҫ�����׸��ַ��ĵ�ַ
	printf("%s\n", p + 2);
	printf("%c\n",*(p+3));
	*p = 'm';
	printf("%s\n", p);
	//a++
	p++;
	*p = 'o';
	printf("%s\n", p);
	//printf("%d\n",sizeof(a));//11
	//printf("%d\n", sizeof(p));//4

	//printf("%d\n", strlen(a));//
	//printf("%d\n", strlen(p));//

	system("pause");
	return 0;
}
