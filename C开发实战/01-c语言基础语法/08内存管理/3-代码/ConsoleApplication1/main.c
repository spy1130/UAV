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
extern int  num32;//声明num32在其他地方定义过
//extern int  num64;//err 静态全局变量是不能声明,也不能在其他文件使用
void fun3()
{
	num32 = 200;
	//num64 = 300;
	printf("num32= %d\n", num32);
}


//2  2
int * fun()
{
	int a;
	static int num=1;//main函数运行之前就已经开辟空间
	num = num + 1;
	printf("num=%d\n",num);
	//return &a; err
	return  &num;
	//pintf("%d\n", sum); err  sum的作用范围是{}
}

int main03()
{
	int *p = fun();
	//*p = 1000;
	printf("%d\n",*p);
	fun();


	system("pause");
	return 0;
}

//1 函数结束之后释放
//2 跳出{}之后
int main02()
{
	int  a=0;//定义时开辟空间
	int *p = NULL;
	if (1)
	{
		int  b = 20;
		p = &b;
		printf("%d\n",a);
		
	}
	printf("%d\n",*p);
	*p = 1000;
	printf("%d\n", *p);
	//printf("%d\n", b); err  b的范围在if{}之内起作用

	system("pause");
	return 0;
}


int main01()
{
	//1  1  4
	//1   2  2
	//1   4   4 
	//2   4   2
	//1   1   4
	int  a[10] = { 2,4,7,2,8,1,3 };
	int *p = a;
	printf("%d\n",(*p)++);//1  *p  *p = *p+1
	printf("%d\n", *(p++));//2  *p  p++
	printf("%d\n", *p++);//4  *p  p++
	printf("%d\n", *p);
	system("pause");
	return 0;
}
