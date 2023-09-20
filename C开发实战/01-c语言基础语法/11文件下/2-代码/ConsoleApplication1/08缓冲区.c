#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>


int main08()
{
	printf("dnaofha");
	FILE *fp = NULL;
	fp = fopen("demo.txt", "w");
	if (!fp)
	{
		perror("");
		return -1;
	}
	char buf[1024];
	for (int i = 0; i < 1024; i++)
	{
		memset(buf,'1',sizeof(buf));
		fwrite(buf,1,sizeof(buf),fp);
		printf("i=%d\n",i);
	}
	//fputs("hellodemo",fp);//不会马上写入文件,先存至缓冲区,
	//fflush(fp);//强制刷新缓冲区的内容至fp文件中
	while (1);

	system("pause");
	return 0;
}
