#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "mt_math.h"
#include "mt_math.h"
#ifndef _MT_MATH_H_//���û�ж��������,����
#define  _MT_MATH_H_
int my_max(int  a, int b);
int my_min(int  a, int b);
int my_div(int  a, int b);
int my_sub(int  a, int b);
int my_sum(int  a, int b);

#endif

int main()
{
	int a = 10;
	int b = 20;
	//�����ֵ
	printf("max=%d\n",my_max(a,b));
	//����Сֵ
	printf("min=%d\n", my_min(a, b));


	system("pause");
	return 0;
}
