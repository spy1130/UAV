#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>


int main02()
{
	int  year = 2018;
	int month = 10;
	int day = 27;
	char buf[1024] = "";
	FILE *fp = NULL;
	fp =  fopen("./fprintf.txt", "wb");
	if (!fp)
	{
		perror("");
		return -1;
	}

	//sprintf(buf,"%04d:%02d:%02d\n",year,month,day);
	//fputs(buf,fp);
	fprintf(fp, "%04d:%02d:%02d\n", year, month, day);
	fclose(fp);
	system("pause");
	return 0;
}
