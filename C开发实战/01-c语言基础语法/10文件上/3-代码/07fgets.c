#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>


int main08()
{
	FILE *fp = fopen("./a.txt", "r");
	if (fp == NULL)
	{
		perror("");
		return -1;
	}
	char buf[1024] = "";
	fgets(buf,sizeof(buf),fp);
	printf("buf=%s\n",buf);

	system("pause");
	return 0;
}
