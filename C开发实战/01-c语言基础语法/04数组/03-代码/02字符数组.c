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


int main()
{
	//�������������
	//��������
	//int  t = time(NULL);//time������õ�ǰʱ��,,s
	srand(time(NULL));//��������
	int a = rand();//rand()��������
	printf("a=%d\n",a);
	int b = rand();//rand()��������
	printf("b=%d\n", b);
	system("pause");
	return 0;
}

//�ַ���׷��
int main17()
{
	char str1[128] = "hello";//hello123456
	char str2[128] = "123456";
	int i = 0;
	while (str1[i] != 0)
		i++;//5
	int j = 0;
	while (str2[j] != 0)
	{
		str1[i] = str2[j];
		i++;
		j++;
	
	}
	printf("str1=%s\n",str1);
	system("pause");
	return 0;
}


int main16()
{
	char buf[1024] = "helloworld";
	//printf("%s\n",buf);
	//puts(buf);//������Ԫ�ص�ַ,�л���
	fputs(buf,stdout);//��һ������,������Ԫ�ص�ַ,stdout��׼���(��Ļ)
	system("pause");
	return 0;
}

int main15()
{
	char buf[128] = "helloA";//buf[5]=0;
	//��Ҫ�ҵ����һ���ַ����±�
	//������ַ�������Ч�ַ��ĸ���
	int i = 0;
	/*while (buf[i] != '\0')
	{
		i++;
	}
	printf("i=%d\n",i);*/
	i = strlen(buf);//strlen()���ַ�������Ч�ַ��ĸ���
	printf("i=%d\n", i);
	buf[i - 1] = '\0';
	printf("%s\n",buf);
	system("pause");
	return 0;
}


int main14()
{
	//fgets��ѻس���\n��ȡ
	char buf[1024] = "";
	fgets(buf,sizeof(buf),stdin);//hello\n
	buf[strlen(buf) - 1] = 0;
	printf("%s\n",buf);

	system("pause");
	return 0;
}


int main13()
{
	//gets����\n����.,���������ո񲻽�����ȡ�ո�
	//getsҲ������ڴ���Ⱦ
	char  num[5] = "";
	gets(num);//()����Ĳ���Ҫ���Ǵ�Ŷ�ȡ�ַ����ĵ�ַ
	printf("num=%s\n",num);

	system("pause");
	return 0;
}

int main12()
{
	char  ch = 0;
	//scanf("%c",&ch);  �Ӽ��̶�ȡһ���ַ�
	//��ȡһ���ַ���

	char  num[5] = "";
	//%s�Ӽ��̻�ȡһ���ַ���,����\n����
	scanf("%s",num);

	//%s  Ҫ���Ǵ�ӡ�ַ��������Ԫ�ص�ַ
	printf("[%s]\n",num);


	system("pause");
	return 0;
}


int main11()
{
	//char  a[128] = "abcd\0def\0";
	//char  a[128] = { 'a','b',cd\0def\0 };
	char a[] = { 'a','b',0,'c' };
	char b[] = { 'a','b','0','c' };
	char c[] = { 'a','b','\0','c' };
	//printf("%d\n",sizeof(a));//128
	printf("%s\n",a);//ab
	printf("%s\n", b);//ab0c.....����
	printf("%s\n", c);//ab
	system("pause");
	return 0;
}

int main10()
{
	//"hello"
	//�ַ�����
	//�ַ��������ַ���������\0�ַ�������
	//��Ϊ��\0�ַ����ַ�����,������������
	//char  a[5] = {'a','b','c','d','e'};��ͨ���ַ�����
	//char  a[5] = {'a','b','c','d','\0'};//�ַ������к���\0�ַ���,��Ҳ���ַ���
	//char  a[5] = "abcd";//������һ���ַ�����,�����abcd\0
	//char  a[] = "world";//
	//char  a[100] = "abcd";//������һ���ַ�����,��100��Ԫ��
	//char  a[100] = "\0";//������ĵ�0��Ԫ����\0,����Ԫ�ؾ���\0
	char  a[100] = { 0 };//��һ���ַ�������0
	/*for (int i = 0; i < sizeof(a) / sizeof(a[0]); i++)
	{
		printf("%c",a[i]);
	}*/
	printf("%s\n",a);
	printf("\n");
	printf("%s\n","hello");
	system("pause");
	return 0;
}
