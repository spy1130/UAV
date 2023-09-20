#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//函数的定义不能定义在函数的代码块里,必须在函数的外面定义函数
//符号加()代表这个是一个函数
//如果定义的函数没有形参,可以不填,也可以写void,但是返回值如果没有,需要写void
//  无参无返回值函数
//函数{}是函数体,所有的代码必须放在{}中
//函数结束之前需要返回值
//注意:返回值的类型看函数定义时,所需要的类型
void fun()
{
	printf("hello fun\n");
	printf("hello dfafa\n");
	return;
}

//定义一个有参无返回值函数
//函数定义时()里面的参数叫形参,(因为这个形参只是形式上的参数,定义函数时没有给形参开辟空间)
//形参只有在被调用时才会分配空间
//形参 的定义  类型名+变量名
void  fun2(int  a, int  b)
{
	int c = 0;
	c = a + b;
	printf("a+b=%d\n",c);
	return;
}


int main02()
{
	printf("hello main\n");
	//函数的调用  函数名+()
	//fun();
	//函数调用有参函数时,不可以不传参
	//调用函数时.()里面的参数叫实参,
	//实参的类型和形参的类型必须一致
	//函数调用时,实参的个数应该和形参的个数相同
	//实参为常量,可以为变量,可以为表达式,只要实参的类型和形参的类型匹配即可
	int x = 10;
	int  y = 20;
	//fun2(2,3)
	 fun2(x,y);
	//fun2(x + y, x*y);
	system("pause");
	return 0;
}
