#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
int main07()
{
	struct stat buf;//buf�ṹ��һ��Ҫ�пռ�
	int ret = 0;
	ret = stat("fwrite.txt",&buf);
	if (ret < 0)//�������ֵС��0,�����ļ�������
	{
		printf("file notfound\n");
	}
	printf("%d\n",buf.st_size);//buf.st_size ������ļ���С
	//remove("fwrite.txt");
	rename("fseek.txt","seek.txt");
	system("pause");
	return 0;
}
