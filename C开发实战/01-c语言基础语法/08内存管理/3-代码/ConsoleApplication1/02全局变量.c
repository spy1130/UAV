#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int  val;
int  val;
int  val;
int  val;


int  num32;//ȫ�ֱ��� ,��������������
static int  num64;//��̬ȫ��

//��������  ����ִ��main����֮ǰ���ٿռ�,��������ͷſռ�
void fun1()
{
	num32 = 10;
	num64 = 100;
}
int main()
{
	//int  a;
	//int  a;
	printf("%d\n",num32);
	printf("%d\n", num64);
	fun1();
	fun3();
	printf("%d\n", num32);
	printf("%d\n", num64);
	system("pause");
	return 0;
}
