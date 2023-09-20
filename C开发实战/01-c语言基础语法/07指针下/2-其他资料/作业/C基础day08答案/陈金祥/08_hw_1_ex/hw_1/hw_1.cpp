// hw_1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<stdio.h>

#define N sizeof(a)/sizeof(a[0])
void sort_fun(int *a,int n)					//选择排序
{
	int i = 0, j = 0;
	for (i = 0; i < n - 1; i++)
	{
		int *p_max = a + i;							/*第一次内层循环*/	//假设最大的数为第一位
		for (j = i + 1; j < n; j++)					   //j从第二个元素开始遍历至最后一位元素
		{											  //过程中比第一个元素大就交换，结束时，找出最大数置于第一个元素。
			if (*(a + j) > *p_max)					/*第二次内层循环*/	// 找出第二大的数字....
			{
				int t = *(a + j);
				*(a + j) = *p_max;
				*p_max = t;
			}
		}
	}
}
int num( int *a ,int n )						 
{												 //算出数组中不同元素的个数
	int i = 0, j = 0, k = 1;
	sort_fun(a, n);
	for (i = 0; i < n -1; i++)			   
		if (*(a + i) > *(a + i + 1))	   //*(a+i)跟其后的元素作比较故循环n-1次
			k++;
	return k;
}
int _tmain(int argc, _TCHAR* argv[])
{
	int a[] = { 100, 100, 32, 45, 21, 67, 32, 68, 41, 99, 13, 71 };		//选择排序
	printf("请输入要查找第几大的数字[0-%d]:",num(a,N));	  //100 99 71 68 67 45 41 32 21 13
	int find;
	scanf_s("%d", &find);
	if (find < 0 || find > num(a, N))
	{
		printf("你要找的数在外太空！");
		return 0;
	}
	int i = 0,k = 1;
	for (i = 0; i < N -1; i++)
	{
		if (*(a+i) > *(a+i+1))
		{
			k++;
			if (k == find)
			{
				printf("第%d大的数字是：\t\t\t\t**    %d    **\n", find, *(a + i + 1));
				break;
			}
		}

	}

	return 0;
}

