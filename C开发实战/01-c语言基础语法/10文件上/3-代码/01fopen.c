#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>


int main01()
{
	//r ֻ�� ,����ļ�������,������ 
	//w ֻд  ����ļ� ,����ļ�������,�����ļ�
	//r+ �ɶ���д  ����ļ�������,������
	//w+ �ɶ���д����ļ�,  ����ļ�������,�����ļ�
	//a׷��   ����ļ�������,�ᴴ���ļ�
	//b  �������ļ�
	//��һ���ļ�,�ɹ�����FILE�ṹ���ַ,ʧ�ܷ���NULL
	
	FILE *fp = fopen("./a.txt","w");
	if (NULL == fp)
	{
		perror("open");
		return;

	}
	char buf[10] ={97,-1,-2,98,99};
	int i = 0;
	while (buf[i] != 0)
	{
		fputc(buf[i],fp);
		i++;
	}

	fclose(fp);


	system("pause");
	return 0;
}
