#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>


int main01()
{
	//r 只读 ,如果文件不存在,不创建 
	//w 只写  清空文件 ,如果文件不存在,创建文件
	//r+ 可读可写  如果文件不存在,不创建
	//w+ 可读可写清空文件,  如果文件不存在,创建文件
	//a追加   如果文件不存在,会创建文件
	//b  二进制文件
	//打开一个文件,成功返回FILE结构体地址,失败返回NULL
	
	FILE *fp = fopen("./a.txt","w");
	if (NULL == fp)
	{
		perror("open");
		return;

	}
	char buf[10] ={97,-1,-2,98,99};
	int i = 0;
	while (buf[i] != 0)
	{
		fputc(buf[i],fp);
		i++;
	}

	fclose(fp);


	system("pause");
	return 0;
}
