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

//数组的大小
int main()
{
	//num是数组名,代表这个数组
	int  num[10] = { 1,2,3,4,5,6,7,8,9,10 };
	printf("%d\n",sizeof(int [10]));
	printf("%d\n", sizeof(num));
	//求数组元素个数
	int n = sizeof(num) / sizeof(num[0]);
	printf("n=%d\n",n);
	for (int i = 0; i < sizeof(num)/sizeof(num[0]); i++)
	{
		printf("%d ", num[i]);

	}
	system("pause");
	return 0;
}

//数组的初始化
int main29()
{
	
	//int  num[10] = {1,2,3,4,5,6,7,8,9,10};
	//如果数组只初始化部分元素,其他元素被初始化为0
	//int  num[10] = { 1,2 };
	//int num[10] = { 0 };//将数组所有元素初始化为0
	//int  num[10] = {[5]=5};
	//int num[]; err  定义时没有告知有几个元素
	int  num[] = { 1,2,3 };//如果定义时,[]中没有值,这个数组的元素个数由{}里面的元素个数决定
	for (int i = 0; i < 10; i++)
	{
		printf("%d ", num[i]);

	}
	printf("\n");
	system("pause");
	return 0;
}

//数组的定义
int main28()
{
	// 数组名和变量名定义方法一样
	//符号与[]结合代表这个是一个数组
	//数组中的元素的个数由[]里面的数值决定
	//每个元素的类型,数组名前面的类型决定
	//定义数组时,[]里面的值不能为变量,只能为常量
	//使用时,[]里面的值可以为常量也可以是变量
	//数值数组不能整体操作
	//数组的每一个元素都是变量,可以被改变赋值
	int  n = 10;
	int  num[10];
	//num[0] = 100;
	//printf("%d\n",num[0]);
	for (int i = 0; i < 10; i++)
	{
		printf("%d\n", num[i]);
		
	}


	system("pause");
	return 0;
}
