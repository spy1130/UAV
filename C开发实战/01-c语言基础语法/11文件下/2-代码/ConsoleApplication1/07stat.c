#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
int main07()
{
	struct stat buf;//buf结构体一定要有空间
	int ret = 0;
	ret = stat("fwrite.txt",&buf);
	if (ret < 0)//如果返回值小于0,代表文件不存在
	{
		printf("file notfound\n");
	}
	printf("%d\n",buf.st_size);//buf.st_size 这个是文件大小
	//remove("fwrite.txt");
	rename("fseek.txt","seek.txt");
	system("pause");
	return 0;
}
