#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>


int main05()
{
	//���ļ�,��
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
		if (feof(fp))//feof(fp) ��0 ��ȡ���ļ�ĩβ
			break;
		fputc(ch,stdout);
		//printf("%c",ch);  putchar(ch);
	
	}

	fclose(fp);
	system("pause");
	return 0;
}
