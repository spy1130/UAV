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
	fseek(fp,0,SEEK_SET);//�ƶ���굽ͷ
	fputs("seek", fp);
	fseek(fp, -5, SEEK_END);//�ƶ���굽ͷ
	fputs("abc", fp);
	//rewind(fp);//����ƶ����ļ���ͷ
	fseek(fp, 0, SEEK_END);//�ƶ���굽ͷ
	int cont = ftell(fp);
	printf("cont =%d\n",cont);
	fclose(fp);
	system("pause");
	return 0;
}
