#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>


int main05()
{
	//打开文件,读
	FILE *fp = fopen("./03cp.c","r");
	if (NULL == fp)
	{
		perror("");
		return -1;
	}
	char ch = 0;
	while (1)
	{
		ch = fgetc(fp);
		if (feof(fp))//feof(fp) 非0 读取到文件末尾
			break;
		fputc(ch,stdout);
		//printf("%c",ch);  putchar(ch);
	
	}

	fclose(fp);
	system("pause");
	return 0;
}
