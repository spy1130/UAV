#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//有参有返回值
int  fun3(int  a, int b)
{
	int c = a + b;
	return c;
	//return  a + b;

}
//声明的作用就是告诉编译器这个东西在其他地方定义
//函数的声明,把函数的定义形式放在调用之前
//没有函数体就是函数的声明,有函数体就是函数的定义
//函数声明不用写函数体
//声明函数时需要加分号
//函数的声明不加extern 也是可以的
//extern  用来声明
//extern void swap(int  a, int  b);
//void swap(int a , int  b);
//void swap(int , int  );
int main()
{
	//exit(0);
	//return 0;
	int  x = 10;
	int  y = 20;
	int  sum = 0;
	//调用有返回值函数时,可以不接返回值,也可以接
	//注意  返回的类型和所接收返回值的变量的类型需要相同
	//参数的传递,只能是单向传递(实参传给形参)
	//sum = fun3(x, y);
	//printf("sum=%d\n",fun3(x,y));//将函数调用的返回值作为其他函数的参数
	void swap(int a, int  b);
	swap(x,y);
	printf("x=%d   y=%d\n",x,y);
	system("pause");
	return 0;
}

void swap(int  a, int  b)
{
	exit(0);
	//return;
	int  c = a;
	a = b;
	b = c;
	printf("a=%d  b=%d\n", a, b);
	return;
}