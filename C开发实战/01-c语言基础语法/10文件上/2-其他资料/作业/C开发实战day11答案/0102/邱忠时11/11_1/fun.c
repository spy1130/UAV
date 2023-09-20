#include "sort.h"


void fun(std **p, int n)
{
	for (std **q = p;q < p +n;q++)
	{
		*q = (std*)malloc(sizeof(std));
		if (*q == NULL)
		{
			printf("没有多余的空间\n");
			exit(0)
		}
	}
	getchar();  //读取回车
}