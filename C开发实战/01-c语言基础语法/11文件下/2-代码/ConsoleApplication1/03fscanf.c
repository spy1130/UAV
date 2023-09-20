#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>


int main03()
{
	int year = 0,month=0,day=0;

	FILE *fp = NULL;
	fp = fopen("./fprintf.txt", "r");
	if (!fp)
	{
		perror("");
		return -1;
	}
	fscanf(fp,"%d:%d:%d\n",&year,&month,&day);

	printf("%d  %d %d \n",year,month,day);
	system("pause");
	return 0;
}
