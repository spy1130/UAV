#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define  MAX  10//������һ���꣨������  ֵΪ10
int main04()
{
	//����ȡ��   ����Ϊ�ؼ���  
	//����ı��������ڴ濪�ٿռ䣬������ռ�ȡ��
	//���������ʱ  �������������ַ����»��߿�ͷ�����������ֿ�ͷ
	//��ʼ����  �ڶ���ʱ��ֵ
	int  num =200;//����������ҳ�ʼ��
	// int  8fg;  err
	char   abc_def;
	//extern   ���߱��������������������û�ж��壩 ����
	extern  short SUM;//��������SUM ��û�п��ٿռ�
	// SUM = 200000; err
//	num = 100;
	printf("num=%d\n",num);
	//MAX = 100;  MAX��һ�����������������Ա�����

	system("pause");
	return 0;
}

//const���εı���
int main()
{
	//const ���εı������ܱ�����
	//const int   a;//const���εı���a, ����ͨ��������aȥ�޸ı���a������
	 // a = 10; 
	//printf("a=%d\n",a);

	int  a = 0123;


	system("pause");
	return 0;
}
