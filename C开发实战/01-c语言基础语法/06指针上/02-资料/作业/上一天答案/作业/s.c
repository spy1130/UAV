#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

//�Ƚϴ�С
int my_strcop(char a[], char b[])
{
	//�ȽϽ��1��0��-1�ֱ�Ϊa���ڡ����ڡ�С��b
	for (size_t i = 0; i < strlen(a); i++)
	{
		if (a[i] != b[i])
			return a[i] > b[i] ? 1 : -1;
	}
	return 0;
}
//����
int cala(char y[], int a, int b)
{
	if (my_strcop("add", y) == 0)
		return a + b;
	else if (my_strcop("sub", y) == 0)
		return a - b;
	else if (my_strcop("mux", y) == 0)
		return a * b;
	else if (my_strcop("dive", y) == 0)
		return a / b;
	else {
		printf("��������������");
		return 400;
	}
}
//����������ƴ�ӳɶ�Ӧ����λ��������
int getNum(char a[]) {
	int num = 0;
	for (size_t i = strlen(a); i > 0; i--)
	{
		num += (a[strlen(a) - i] - 48) * pow(10, i - 1);
	}
	return num;
}
int main() {
	printf("a%d b%d", a, b);
	printf("�Ӽ�������ָ����������մ˸�ʽ���磺\nadd 15 25  ����15+25��ֵ\nsub 25 15  ����25-15��ֵ");
	printf("\nmux 3  5   ����3*5��ֵ\ndive 25 5  ����25/5��ֵ\n");
	char ch[100] = { 0 };
	gets(ch, 100);
	//printf("ch����=%d",strlen(ch));
	char xm[5] = { 0 };//���ڴ洢�û���������������
	char inN_a[20] = { 0 };//���ڴ洢����ĵ�һ����
	char inN_b[20] = { 0 };//���ڴ洢����ĵڶ�����
	int isSpace = 0;//�ҵ��ڼ�������
	int k = 0;//��¼�������ĳ���
	int j = 0;//��¼��һ�����ĳ���
	for (size_t i = 0; i < strlen(ch); i++)//��������ַ�����ָ��3���ַ�����
	{
		if (ch[i] != 32 && isSpace == 0)
		{
			xm[i] = ch[i];
			k++;
		}
		else if (ch[i] == 32)
		{
			k++;
			isSpace++;
			continue;
		}
		else if (ch[i] != 32 && isSpace == 1)
		{
			inN_a[i - k] = ch[i];
			j++;
		}
		else if (ch[i] != 32 && isSpace == 2)
			inN_b[i - k - j] = ch[i];
		else if (isSpace > 2)
			break;
	}
	int outNum_;//���ֵ
	if (my_strcop("add", xm) == 0)//���
		outNum_ = cala("add", getNum(inN_a), getNum(inN_b));
	else if (my_strcop("sub", xm) == 0)//���
		outNum_ = cala("sub", getNum(inN_a), getNum(inN_b));
	else if (my_strcop("mux", xm) == 0)//���
		outNum_ = cala("mux", getNum(inN_a), getNum(inN_b));
	else if (my_strcop("dive", xm) == 0)//���
		outNum_ = cala("dive", getNum(inN_a), getNum(inN_b));
	printf("���Ϊ��%d\n", outNum_);
	system("pause");
	return 0;
}