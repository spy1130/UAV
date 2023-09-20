#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>


int main04()
{
	//打开src(待拷贝的文件)文件
	FILE *src = fopen("a.txt","rb");
	if (NULL == src)
	{
		perror("");
		return -1;
	}
	//打开dst(拷贝的新文件)文件
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
	//读取src一个 字符
		//ch = fgetc(src);
		memset(buf,0,sizeof(buf));
		p = fgets(buf, sizeof(buf), src);
		if (p == NULL)
			break;
		/*if (feof(src))
			break;*/
		//写到dst文件
		//fputc(ch,dst);
		fputs(buf,dst);
	
	}
	//fclose(src);
	//fclose(dst);

	system("pause");
	return 0;
}
