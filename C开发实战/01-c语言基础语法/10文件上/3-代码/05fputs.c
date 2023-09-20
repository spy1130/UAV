#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>


int main06xx()
{
	FILE *fp = fopen("./a.txt","w");
	if (fp == NULL)
	{
		perror("");
		return -1;
	}
	char buf[] = "hello\nworld";
	//Óöµ½\0½áÊø
	fputs( buf,fp );
	system("pause");
	return 0;
}
