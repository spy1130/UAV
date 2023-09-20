#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "type.h"

int main05()
{
	STD num[3];
	memset(num,0,sizeof(num));
	FILE *fp = NULL;
	int cont = 0;
	fp = fopen("fwrite.txt", "r");
	if (!fp)
	{
		perror("");
		return -1;
	}
	fread(num,1,sizeof(num),fp);
	for (int i = 0; i < 3; i++)
	{
		//cont = fread( &num[i] ,1,sizeof(STD),fp );
		//printf("cont =%d\n",cont);
		printf("%d %s\n",num[i].id,num[i].name);
	
	}
	fclose(fp);
	system("pause");
	return 0;
}
