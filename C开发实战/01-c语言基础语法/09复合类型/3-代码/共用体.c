#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct mim
{
	char  a;
	short b;
	int   c;
};
union mi
{
	char  a;
	short b;
	int   c;
};

int main21()
{
	union mi  tmp;
	//tmp.a = 0x01;
	//tmp.c = 0x01020304;
	//tmp.b = 0x0a0b;
	//printf("%x\n",tmp.b);
	//printf("%x\n", tmp.a);
	//printf("%x\n", tmp.c);

	printf("%d\n",sizeof(tmp));
	printf("%d\n",sizeof(struct mim));
	system("pause");
	return 0;
}
