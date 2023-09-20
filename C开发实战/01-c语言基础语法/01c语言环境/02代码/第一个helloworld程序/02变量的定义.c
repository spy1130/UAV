#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define  MAX  10//定义了一个宏（常量）  值为10
int main04()
{
	//变量取名   不能为关键字  
	//定义的本质是在内存开辟空间，给这个空间取名
	//定义变量名时  变量名必须以字符和下划线开头，不能以数字开头
	//初始化：  在定义时赋值
	int  num =200;//定义变量并且初始化
	// int  8fg;  err
	char   abc_def;
	//extern   告诉编译器我有这个变量，（没有定义） 声明
	extern  short SUM;//声明变量SUM 并没有开辟空间
	// SUM = 200000; err
//	num = 100;
	printf("num=%d\n",num);
	//MAX = 100;  MAX是一个常量，常量不可以被更改

	system("pause");
	return 0;
}

//const修饰的变量
int main()
{
	//const 修饰的变量不能被更改
	//const int   a;//const修饰的变量a, 不能通过变量名a去修改变量a的内容
	 // a = 10; 
	//printf("a=%d\n",a);

	int  a = 0123;


	system("pause");
	return 0;
}
