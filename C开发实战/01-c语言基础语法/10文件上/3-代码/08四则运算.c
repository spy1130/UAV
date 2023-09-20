#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define CALC_NUM 10
#define FILE_PATH  "calc.txt"
FILE *open_file(char *str)
{
	FILE *fp = fopen(FILE_PATH, str);
	if (fp == NULL)
	{
		perror("");
		return -1;
	}
	return fp;
}
void get_date()
{
	FILE *fp = open_file( "w");
	
	char abb[4] = {'+','-','*','/'};
	srand(time(NULL));
	int  a = 0;
	int b = 0;
	char c = 0;
	char cmd[128] = "";
	for (int i = 0; i < CALC_NUM; i++)
	{
		a = rand()%100+1;
		b = rand() % 100 + 1;
		c = rand() % 4;
		sprintf(cmd,"%d%c%d=\n",a,abb[c],b);
		//printf("%s",cmd);
		fputs(cmd,fp);

	}
	fclose(fp);

}
void read_data()
{
	FILE *fp = open_file("r");
	int  a = 0;
	int b = 0;
	char c = 0;
	char buf[128] = "";
	char cmd[128] = "";
	char buff[100][128] = {0};
	//char *buff[10]={NULL};
	char *p = NULL;

	int len = 0;
	int num = 0;
	int i = 0;
	while (1)
	{
		p = fgets(buf,sizeof(buf),fp);
		if (p == NULL)
			break;
		sscanf(buf,"%d%c%d",&a,&c,&b);//4+3= \n

		switch (c)
		{
			case '+':
				num = a + b;
				break;
			case '-':
				num = a - b;
				break;
			case '*':
				num = a * b;
				break;
			case '/':
				num = a / b;
				break;
		
		}
		
		//buff[i] = malloc(128);
	   sprintf(buff[i]  , "%d%c%d=%d\n", a, c, b, num);//3+4=7\n
		i++;
		//buff[0]
		
		


	}

	fclose(fp);
	fp = open_file("w");
	int j = 0;
	for (j = 0; j < i; j++)
	{
		
		fputs(buff[j],fp);

	}
	fclose(fp);
}
int main()
{
	
	get_date();
	read_data();

	system("pause");
	return 0;
}
