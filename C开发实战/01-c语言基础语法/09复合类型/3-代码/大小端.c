#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
union  abc
{
	//char a;
	short b;
	char buf[2];
};

int main22()
{
	union  abc tmp;
	tmp.b = 0x0102;
	if (tmp.buf[0] == 0x01)
	{
		printf("big\n");
	}
	else
	{
		printf("little\n");
	}

	system("pause");
	return 0;
}
