// copy_string.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
void my_strcpy(char dst[], char src[])
{
	int i = 0;
	while (*(dst + i) = *(src + i++))
		;
}

int _tmain(int argc, _TCHAR* argv[])
{
	char src[100] = "hello";
	char dst[100];
	my_strcpy(dst, src);
	printf("%s\n", dst);
	return 0;
}

