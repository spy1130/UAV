// hw_1.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<stdio.h>

#define N sizeof(a)/sizeof(a[0])
void sort_fun(int *a,int n)					//ѡ������
{
	int i = 0, j = 0;
	for (i = 0; i < n - 1; i++)
	{
		int *p_max = a + i;							/*��һ���ڲ�ѭ��*/	//����������Ϊ��һλ
		for (j = i + 1; j < n; j++)					   //j�ӵڶ���Ԫ�ؿ�ʼ���������һλԪ��
		{											  //�����бȵ�һ��Ԫ�ش�ͽ���������ʱ���ҳ���������ڵ�һ��Ԫ�ء�
			if (*(a + j) > *p_max)					/*�ڶ����ڲ�ѭ��*/	// �ҳ��ڶ��������....
			{
				int t = *(a + j);
				*(a + j) = *p_max;
				*p_max = t;
			}
		}
	}
}
int num( int *a ,int n )						 
{												 //��������в�ͬԪ�صĸ���
	int i = 0, j = 0, k = 1;
	sort_fun(a, n);
	for (i = 0; i < n -1; i++)			   
		if (*(a + i) > *(a + i + 1))	   //*(a+i)������Ԫ�����ȽϹ�ѭ��n-1��
			k++;
	return k;
}
int _tmain(int argc, _TCHAR* argv[])
{
	int a[] = { 100, 100, 32, 45, 21, 67, 32, 68, 41, 99, 13, 71 };		//ѡ������
	printf("������Ҫ���ҵڼ��������[0-%d]:",num(a,N));	  //100 99 71 68 67 45 41 32 21 13
	int find;
	scanf_s("%d", &find);
	if (find < 0 || find > num(a, N))
	{
		printf("��Ҫ�ҵ�������̫�գ�");
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
				printf("��%d��������ǣ�\t\t\t\t**    %d    **\n", find, *(a + i + 1));
				break;
			}
		}

	}

	return 0;
}

