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
	//申请一个字符数组,有1024元素
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
	//申请一个数组,数组有10个元素,每个元素int类型
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
	//将数组a中前5个元素拷贝至数组b中
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
	//将前9个字符置为'a'
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

	printf("&a\t %p\t //局部未初始化变量\n", &a);
	printf("&b\t %p\t //局部初始化变量\n", &b);

	printf("&c\t %p\t //静态局部未初始化变量\n", &c);
	printf("&d\t %p\t //静态局部初始化变量\n", &d);

	printf("&e\t %p\t //全局未初始化变量\n", &e);
	printf("&f\t %p\t //全局静态未初始化变量\n", &f);

	printf("&g\t %p\t //全局初始化变量\n", &g);
	printf("&h\t %p\t //全局静态初始化变量\n", &h);

	printf("i\t %p\t //只读数据(文字常量区)\n", i);

	k = (char *)malloc(10);
	printf("k\t %p\t //动态分配的内存\n", k);

	return 0;
}

int num = 0;
void fun()
{
	printf("num1=%d\n", num);
}
//不同的作用域可以重名
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
