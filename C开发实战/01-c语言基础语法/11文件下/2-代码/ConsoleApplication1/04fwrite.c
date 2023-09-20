#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "type.h"

int main04()
{
	STD num[3] = { {1,"lucy"},{2,"bob"},{3,"peter"} };
	FILE *fp = NULL;
	int cont = 0;
	fp = fopen("fwrite.txt","w");
	if (!fp)
	{
		perror("");
		return -1;
	}
	//fwrite 第二个参数写1 ,是为了返回值刚好是写入文件的字节数
	cont = fwrite(num, 1,sizeof(num),fp);
	//cont = fwrite(num,  sizeof(num), 1,fp);
	printf("cont=%d\n",cont);


	system("pause");
	return 0;
}
