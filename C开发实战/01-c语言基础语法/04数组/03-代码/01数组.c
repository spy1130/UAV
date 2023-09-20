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


int main09()
{
	float a[5][3] = { { 80, 75, 56 },{ 59, 65, 71 },
	{ 59, 63, 70 },{ 85, 45, 90 },{ 76, 77, 45 } };
	float sum = 0.0;
	float aver[3] = {0};
	int num[3] = { 0 };
	for (int i = 0; i < 3; i++)
	{
		sum = 0.0;//每一次sum的值都需要清0
		for (int j = 0; j < 5; j++)
		{
			sum += a[j][i];
			if (a[j][i] < 60)
			{
				num[i]++;
			}
		}
		aver[i] = sum / 5;
	
	}
	for (int i = 0; i < 3; i++)
	{
		printf("%f\n", aver[i]);
	}
	for (int i = 0; i < 3; i++)
	{
		printf("%d\n", num[i]);
	}

	system("pause");
	return 0;
}


int main08()
{
	int  a[3][4];
	printf("%u\n",&a[0][0]);
	printf("%u\n", a[0]);
	printf("%u\n", &a[0]);
	printf("%u\n", a);
	printf("%u\n", &a);

	printf("%u\n", &a[0][0]+1);
	printf("%u\n", a[0]+1);
	printf("%u\n", &a[0]+1);
	printf("%u\n", a+1);
	printf("%u\n", &a+1);

	system("pause");
	return 0;
}


int main07()
{
	int  a[3][4] = {1,2,3};
	int n = sizeof(a) / sizeof(a[0][0]);//元素的个数
	int line = sizeof(a) / sizeof(a[0]);//行数  = 二维数组总大小除以 一行的大小
	int clu = sizeof(a[0]) / sizeof(a[0][0]);//列 = 行大小除以 一个元素的大小 
	printf("%d %d %d\n",n,line,clu);
	system("pause");
	return 0;
}


int main06()
{
	//给二维数组部分元素初始化,其他元素为0
	//int a[3][4] = { {1,2,3,4},{5,6,7,8},{9,10,11,12} };
	//int a[3][4] = { 1,2,3,4 , 5,6,7,8 , 9,10,11,12  };
	//int a[3][4] = {1,2,3};
	//二维数组定义时,不能省略列的下标,可以省略行的下标
	int  a[][3] = { 1,2,3,4,5 };
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			printf("%d ", a[i][j]);
		}
		printf("\n");
	}

	system("pause");
	return 0;
}


int main05()
{
	//e二维数组a的类型是  int   [3][4]
	int a[3][4];//定义一个3行4列的二维数组,
	//二维数组的每一个元素也是一个 变量
	printf("%d\n", sizeof(int [3][4]));
	printf("%d\n",sizeof(a));
	a[1][1] = 10;
	a[2][3] = 20;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			printf("%d ",a[i][j]);
		}
		printf("\n");
	}


	system("pause");
	return 0;
}

//数组的排序 - 冒泡排序
int main04()
{
	int   a[5] = {2,5,6,3,-1};
	int n = sizeof(a) / sizeof(a[0]);
	for (int i = 0; i < n - 1; i++)//比较的轮数
	{
		//因为每次比较的次数都要减1,刚好i每次加1,所以每一轮 比较的次数是n-1-i
		for (int j = 0; j < n-1-i;j++ )//每一轮需要比较的次数
		{
			if (a[j] > a[j + 1])//如果前面的元素比后面的元素大,则交换位置
			{
				int tmp = a[j + 1];
				a[j + 1] = a[j];
				a[j] = tmp;
			}
			
		}
	}
	for (int i = 0; i < n; i++)
	{
		printf("%d ",a[i]);
	}
	printf("\n");
	system("pause");
	return 0;
}

//数组的逆置
int main03()
{
	int  a[10] = { 1,2,3,4,5,6,7,8,9,10};
	int i = 0;
	int j = sizeof(a) / sizeof(a[0]) - 1;
	int tmp = 0;
	while (i<j)
	{
		//前后交换
		tmp = a[i];
		a[i] = a[j];
		a[j] = tmp;
		//移动位置
		i++;
		j--;
	}


	system("pause");
	return 0;
}

//求数组最大值
int main02()
{
	int  a[10] = {2,5,1,67,34,67,34,56,2,3};
	int  max = a[0];//2
	for (int i = 1; i < 10; i++)
	{
		if (max < a[i])
			max = a[i];
	}
	printf("%d\n",max);
	system("pause");
	return 0;
}


int main01()
{
	int  a[5];
	printf("%u\n",&a[0]);
	printf("%u\n", a);
	printf("%u\n", &a);

	printf("%u\n", &a[0]+1);
	printf("%u\n", a+1);
	printf("%u\n", &a+1);


	system("pause");
	return 0;
}
