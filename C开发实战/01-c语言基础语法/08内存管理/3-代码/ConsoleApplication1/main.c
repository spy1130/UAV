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
extern int  num32;//����num32�������ط������
//extern int  num64;//err ��̬ȫ�ֱ����ǲ�������,Ҳ�����������ļ�ʹ��
void fun3()
{
	num32 = 200;
	//num64 = 300;
	printf("num32= %d\n", num32);
}


//2  2
int * fun()
{
	int a;
	static int num=1;//main��������֮ǰ���Ѿ����ٿռ�
	num = num + 1;
	printf("num=%d\n",num);
	//return &a; err
	return  &num;
	//pintf("%d\n", sum); err  sum�����÷�Χ��{}
}

int main03()
{
	int *p = fun();
	//*p = 1000;
	printf("%d\n",*p);
	fun();


	system("pause");
	return 0;
}

//1 ��������֮���ͷ�
//2 ����{}֮��
int main02()
{
	int  a=0;//����ʱ���ٿռ�
	int *p = NULL;
	if (1)
	{
		int  b = 20;
		p = &b;
		printf("%d\n",a);
		
	}
	printf("%d\n",*p);
	*p = 1000;
	printf("%d\n", *p);
	//printf("%d\n", b); err  b�ķ�Χ��if{}֮��������

	system("pause");
	return 0;
}


int main01()
{
	//1  1  4
	//1   2  2
	//1   4   4 
	//2   4   2
	//1   1   4
	int  a[10] = { 2,4,7,2,8,1,3 };
	int *p = a;
	printf("%d\n",(*p)++);//1  *p  *p = *p+1
	printf("%d\n", *(p++));//2  *p  p++
	printf("%d\n", *p++);//4  *p  p++
	printf("%d\n", *p);
	system("pause");
	return 0;
}
