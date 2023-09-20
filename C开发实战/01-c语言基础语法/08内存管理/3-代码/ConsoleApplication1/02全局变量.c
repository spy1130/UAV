#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int  val;
int  val;
int  val;
int  val;


int  num32;//全局变量 ,作用于整个工程
static int  num64;//静态全局

//生命周期  程序执行main函数之前开辟空间,程序结束释放空间
void fun1()
{
	num32 = 10;
	num64 = 100;
}
int main()
{
	//int  a;
	//int  a;
	printf("%d\n",num32);
	printf("%d\n", num64);
	fun1();
	fun3();
	printf("%d\n", num32);
	printf("%d\n", num64);
	system("pause");
	return 0;
}
