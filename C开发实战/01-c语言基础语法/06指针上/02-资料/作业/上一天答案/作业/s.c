#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

//比较大小
int my_strcop(char a[], char b[])
{
	//比较结果1、0、-1分别为a大于、等于、小于b
	for (size_t i = 0; i < strlen(a); i++)
	{
		if (a[i] != b[i])
			return a[i] > b[i] ? 1 : -1;
	}
	return 0;
}
//计算
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
		printf("输入的运算符有误！");
		return 400;
	}
}
//将整形数组拼接成对应长度位数的整数
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
	printf("从键盘输入指令及操作数按照此格式，如：\nadd 15 25  计算15+25的值\nsub 25 15  计算25-15的值");
	printf("\nmux 3  5   计算3*5的值\ndive 25 5  计算25/5的值\n");
	char ch[100] = { 0 };
	gets(ch, 100);
	//printf("ch长度=%d",strlen(ch));
	char xm[5] = { 0 };//用于存储用户输入的运算操作符
	char inN_a[20] = { 0 };//用于存储输入的第一个数
	char inN_b[20] = { 0 };//用于存储输入的第二个数
	int isSpace = 0;//找到第几个参数
	int k = 0;//记录操作符的长度
	int j = 0;//记录第一个数的长度
	for (size_t i = 0; i < strlen(ch); i++)//将输入的字符数组分割成3个字符数组
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
	int outNum_;//结果值
	if (my_strcop("add", xm) == 0)//相加
		outNum_ = cala("add", getNum(inN_a), getNum(inN_b));
	else if (my_strcop("sub", xm) == 0)//相减
		outNum_ = cala("sub", getNum(inN_a), getNum(inN_b));
	else if (my_strcop("mux", xm) == 0)//相乘
		outNum_ = cala("mux", getNum(inN_a), getNum(inN_b));
	else if (my_strcop("dive", xm) == 0)//相除
		outNum_ = cala("dive", getNum(inN_a), getNum(inN_b));
	printf("结果为：%d\n", outNum_);
	system("pause");
	return 0;
}