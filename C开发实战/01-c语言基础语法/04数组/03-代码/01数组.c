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
		sum = 0.0;//ÿһ��sum��ֵ����Ҫ��0
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
	int n = sizeof(a) / sizeof(a[0][0]);//Ԫ�صĸ���
	int line = sizeof(a) / sizeof(a[0]);//����  = ��ά�����ܴ�С���� һ�еĴ�С
	int clu = sizeof(a[0]) / sizeof(a[0][0]);//�� = �д�С���� һ��Ԫ�صĴ�С 
	printf("%d %d %d\n",n,line,clu);
	system("pause");
	return 0;
}


int main06()
{
	//����ά���鲿��Ԫ�س�ʼ��,����Ԫ��Ϊ0
	//int a[3][4] = { {1,2,3,4},{5,6,7,8},{9,10,11,12} };
	//int a[3][4] = { 1,2,3,4 , 5,6,7,8 , 9,10,11,12  };
	//int a[3][4] = {1,2,3};
	//��ά���鶨��ʱ,����ʡ���е��±�,����ʡ���е��±�
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
	//e��ά����a��������  int   [3][4]
	int a[3][4];//����һ��3��4�еĶ�ά����,
	//��ά�����ÿһ��Ԫ��Ҳ��һ�� ����
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

//��������� - ð������
int main04()
{
	int   a[5] = {2,5,6,3,-1};
	int n = sizeof(a) / sizeof(a[0]);
	for (int i = 0; i < n - 1; i++)//�Ƚϵ�����
	{
		//��Ϊÿ�αȽϵĴ�����Ҫ��1,�պ�iÿ�μ�1,����ÿһ�� �ȽϵĴ�����n-1-i
		for (int j = 0; j < n-1-i;j++ )//ÿһ����Ҫ�ȽϵĴ���
		{
			if (a[j] > a[j + 1])//���ǰ���Ԫ�رȺ����Ԫ�ش�,�򽻻�λ��
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

//���������
int main03()
{
	int  a[10] = { 1,2,3,4,5,6,7,8,9,10};
	int i = 0;
	int j = sizeof(a) / sizeof(a[0]) - 1;
	int tmp = 0;
	while (i<j)
	{
		//ǰ�󽻻�
		tmp = a[i];
		a[i] = a[j];
		a[j] = tmp;
		//�ƶ�λ��
		i++;
		j--;
	}


	system("pause");
	return 0;
}

//���������ֵ
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
