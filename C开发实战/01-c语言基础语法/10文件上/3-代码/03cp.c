#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>


int main04()
{
	//��src(���������ļ�)�ļ�
	FILE *src = fopen("a.txt","rb");
	if (NULL == src)
	{
		perror("");
		return -1;
	}
	//��dst(���������ļ�)�ļ�
	FILE *dst = fopen("c.txt", "wb");
	if (NULL == dst)
	{
		perror("");
		return -1;
	}
	char ch = 0;
	char buf[1024 ]= "";
	char *p = NULL;
	while (1)
	{
	//��ȡsrcһ�� �ַ�
		//ch = fgetc(src);
		memset(buf,0,sizeof(buf));
		p = fgets(buf, sizeof(buf), src);
		if (p == NULL)
			break;
		/*if (feof(src))
			break;*/
		//д��dst�ļ�
		//fputc(ch,dst);
		fputs(buf,dst);
	
	}
	//fclose(src);
	//fclose(dst);

	system("pause");
	return 0;
}
