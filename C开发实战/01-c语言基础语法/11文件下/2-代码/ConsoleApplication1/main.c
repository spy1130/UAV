#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>


int main01()
{
	// FILE *stdout
	char buf[] = "hello";
	char buff[128] = "";
	char ch = 0;
	fclose(stdout);//关闭标准输出
//	fputs(buf,stdout);
	printf("hahahha\n");//stdout	//ch = fgetc(stdin);
	//printf("%c",ch);


	system("pause");
	return 0;
}
