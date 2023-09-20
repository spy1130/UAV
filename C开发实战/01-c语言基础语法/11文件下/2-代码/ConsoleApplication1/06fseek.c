#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>


int main06()
{
	FILE *fp = NULL;
	fp = fopen("fseek.txt", "w");
	if (!fp)
	{
		perror("");
		return -1;
	}
	fputs("helloworldheihei",fp);
	fseek(fp,0,SEEK_SET);//移动光标到头
	fputs("seek", fp);
	fseek(fp, -5, SEEK_END);//移动光标到头
	fputs("abc", fp);
	//rewind(fp);//光标移动至文件开头
	fseek(fp, 0, SEEK_END);//移动光标到头
	int cont = ftell(fp);
	printf("cont =%d\n",cont);
	fclose(fp);
	system("pause");
	return 0;
}
