#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>




#include <stdio.h>
#include <stdlib.h>
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
	//����һ���ַ�����,��1024Ԫ��
	char *p = malloc(1024);
	memset(p,0,1024);
	strcpy(p,"helloworld");
	free(p);
	free(p);
	//printf("%s\n",p);

	system("pause");
	return 0;
}


int main07()
{
	//int a[10]
	//����һ������,������10��Ԫ��,ÿ��Ԫ��int����
	int *p = (int *)malloc(sizeof(int)*10);
	memset(p,0,sizeof(int )*10);
	*p = 1000;
	*(p + 5) = 2000;
	for (int i = 0; i < 10; i++)
	{
		printf("%d ",*(p+i));
	}

	system("pause");
	return 0;
}


int main06()
{
	char num1[] = { 1,0,3,4,5,6,7 };
	char num2[] = { 1,0,3,6,5,6,7 };
	char str1[] = "dbakf\0afnafa";
	char str2[] = "dbakf\0bfnafa";
	//printf("%d\n", memcmp(num1,num2,7*sizeof(char)));
	//printf("%d\n", strncmp(num1, num2, 7 * sizeof(char)));
	printf("%d\n", memcmp(str1, str2, sizeof(str1)));
	printf("%d\n", strncmp(str1, str2, sizeof(str1)));
	system("pause");
	return 0;
}

int main05()
{
	char str1[128] = "";
	char str2[128] = "abc\0def\0dadfa";
	//memcpy(str1,str2,10*sizeof(char));
	strncpy(str1, str2, 10 * sizeof(char));
	for (int i = 0; i < 10; i++)
	{
		printf("%d ",str1[i]);
	
	}


	system("pause");
	return 0;
}


int main04()
{
	//������a��ǰ5��Ԫ�ؿ���������b��
	int  a[10] = {1,2,3,4,5,6,7,8,9,10};
	int  b[10] = { 0 };
	//a = b;
	memcpy(b,a,sizeof(int)*5);
	for (int i = 0; i < sizeof(b) / sizeof(b[0]); i++)
	{
		printf("%d ",b[i]);
	
	}
	system("pause");
	return 0;
}


int main03()
{
	int  a =10;
	//a = 0;  ->  memset()
	memset(&a,0,sizeof(a));
	//printf("a=%d\n",a);
	char buf[10] = "";
	strcpy(buf,"hello");
	printf("%s\n",buf);
	memset(buf,0,sizeof(buf));
	printf("%s\n", buf);
	//��ǰ9���ַ���Ϊ'a'
	memset(buf,'a',sizeof(buf)-1);
	printf("%s\n", buf);
	system("pause");
	return 0;
}

int e;
static int f;
int g = 10;
static int h = 10;
int main02()
{
	int a;
	int b = 10;
	static int c;
	static int d = 10;
	char *i = "test";
	char *k = NULL;

	printf("&a\t %p\t //�ֲ�δ��ʼ������\n", &a);
	printf("&b\t %p\t //�ֲ���ʼ������\n", &b);

	printf("&c\t %p\t //��̬�ֲ�δ��ʼ������\n", &c);
	printf("&d\t %p\t //��̬�ֲ���ʼ������\n", &d);

	printf("&e\t %p\t //ȫ��δ��ʼ������\n", &e);
	printf("&f\t %p\t //ȫ�־�̬δ��ʼ������\n", &f);

	printf("&g\t %p\t //ȫ�ֳ�ʼ������\n", &g);
	printf("&h\t %p\t //ȫ�־�̬��ʼ������\n", &h);

	printf("i\t %p\t //ֻ������(���ֳ�����)\n", i);

	k = (char *)malloc(10);
	printf("k\t %p\t //��̬������ڴ�\n", k);

	return 0;
}

int num = 0;
void fun()
{
	printf("num1=%d\n", num);
}
//��ͬ���������������
int main01()
{
	fun();
	fun2();
	int num = 10;
	printf("num1=%d\n",num);
	{
		int  num = 100;

	}
	printf("num2=%d\n", num);
	system("pause");
	return 0;
}
