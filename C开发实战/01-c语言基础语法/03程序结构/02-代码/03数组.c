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

//����Ĵ�С
int main()
{
	//num��������,�����������
	int  num[10] = { 1,2,3,4,5,6,7,8,9,10 };
	printf("%d\n",sizeof(int [10]));
	printf("%d\n", sizeof(num));
	//������Ԫ�ظ���
	int n = sizeof(num) / sizeof(num[0]);
	printf("n=%d\n",n);
	for (int i = 0; i < sizeof(num)/sizeof(num[0]); i++)
	{
		printf("%d ", num[i]);

	}
	system("pause");
	return 0;
}

//����ĳ�ʼ��
int main29()
{
	
	//int  num[10] = {1,2,3,4,5,6,7,8,9,10};
	//�������ֻ��ʼ������Ԫ��,����Ԫ�ر���ʼ��Ϊ0
	//int  num[10] = { 1,2 };
	//int num[10] = { 0 };//����������Ԫ�س�ʼ��Ϊ0
	//int  num[10] = {[5]=5};
	//int num[]; err  ����ʱû�и�֪�м���Ԫ��
	int  num[] = { 1,2,3 };//�������ʱ,[]��û��ֵ,��������Ԫ�ظ�����{}�����Ԫ�ظ�������
	for (int i = 0; i < 10; i++)
	{
		printf("%d ", num[i]);

	}
	printf("\n");
	system("pause");
	return 0;
}

//����Ķ���
int main28()
{
	// �������ͱ��������巽��һ��
	//������[]��ϴ��������һ������
	//�����е�Ԫ�صĸ�����[]�������ֵ����
	//ÿ��Ԫ�ص�����,������ǰ������;���
	//��������ʱ,[]�����ֵ����Ϊ����,ֻ��Ϊ����
	//ʹ��ʱ,[]�����ֵ����Ϊ����Ҳ�����Ǳ���
	//��ֵ���鲻���������
	//�����ÿһ��Ԫ�ض��Ǳ���,���Ա��ı丳ֵ
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
