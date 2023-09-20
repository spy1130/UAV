// hw_1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<stdio.h>

#define N sizeof(a)/sizeof(a[0])
int _tmain(int argc, _TCHAR* argv[])
{
	int a[] = { 100, 100, 32, 45, 21, 67, 32, 68, 41, 99, 13, 71 };		//选择排序
	int i = 0,j =0,b = *a;
	for (i = 0; i < N-1; i++)
	{
		int a1 = b;														//a1存放最大的数字
		int *p_max = a + i;												//假设最大的数为第一位
														/*第一次内层循环*/	
		for (j = i+1; j < N ; j++)											//*(p+j)从第二个元素开始遍历至最后一位元素
			if (*(a+j) > *p_max)											 // 一轮之后必得到最大值将其赋给*p_max
				*p_max = *(a+j);
			b = *p_max;													//b先存放最大的数字然后存放剩余元素中最大的数字（较大的数字）
		if (b < a1)						    						   //直至最大的数字跟较大的数字不一致即找出了第二大的数字，输出其值并退出循环。
		{
			printf("第二大的数字是%d \n", b);						//局限性极大
			break;
		}
	}


	return 0;
}

