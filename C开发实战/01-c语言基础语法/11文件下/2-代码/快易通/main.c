#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <time.h>
#include <windows.h>
#define LINE_NUM  111102
#define FILENAME  "./dict.txt"
// hello  你好
//world  世界
typedef struct _dict
{
	char *key;
	char *content;

}DICT;
FILE *open_file()
{
	FILE *fp = fopen(FILENAME,"r");
	if (fp == NULL)
	{
		perror("");
		return NULL;
	}
	return fp;

}
void filter_buf(char *buf)
{ 
	int n = strlen(buf) - 1;
	while (buf[n] == ' ' || buf[n] == '\n' || buf[n] == '\r' || buf[n] == '\t')
		n--;
	buf[n + 1] = 0;

}
void dict_init(DICT **tmp,int n)
{
	DICT *p;
	p = malloc(sizeof(DICT) * n);
	char *q = NULL;
	char buf[256] = "";
	int i = 0;
	FILE *fp = open_file();//打开文件dict.txt
	while (1)
	{
		q = fgets(buf,sizeof(buf),fp);//读取一行单词
		if (q == NULL)
			break;
		filter_buf(buf);//过滤掉单词后面的显示不了的字符
		p[i].key = malloc(strlen(buf)+1);//给存储单词开辟空间
		strcpy(p[i].key,buf+1);//将单词#后面的内存拷贝

		q = fgets(buf, sizeof(buf), fp);//读取一行翻译
		if (q == NULL)
			break;
		//filter_buf(buf);
		p[i].content = malloc(strlen(buf) + 1);
		strcpy(p[i].content, buf + 6);
		i++;

	}
	fclose(fp);

	*tmp = p;
}
int search_dict(char *cmd, DICT * dict, int n, char *content)
{
	for (int i = 0; i < n; i++)
	{
		if (strcmp(cmd, dict[i].key) == 0)
		{
			strcpy(content,dict[i].content);
			return 1;
		}
	
	}
	return 0;

}
int get_file_line()
{
	int i = 0;
	char buf[256] = "";
	char *q = NULL;

	FILE *fp = open_file();
	while (1)
	{
		q = fgets(buf, sizeof(buf), fp);//读取一行单词
		if (q == NULL)
			break;

		q = fgets(buf, sizeof(buf), fp);//读取一行单词
		if (q == NULL)
			break;
		i++;


		
	}
	fclose(fp);
	return i;
}
int main()
{
	DICT *dict=NULL;
	int n = 0;
	n = get_file_line();
	printf("n=%d\n",n);
	dict_init(&dict, n);
	char cmd[256] = "";
	char content[256] = "";
	int ret = 0;
	//clock_t start=0, end=0;
	LARGE_INTEGER  lpPerformanceCount;
	QueryPerformanceFrequency(&lpPerformanceCount);
	long long c1, c2;
	while (1)
	{
		printf("请输入需要翻译的单词:");
		fgets(cmd,sizeof(cmd),stdin);
		cmd[strlen(cmd) - 1] = 0;//将最后一个字符去掉\n
		//start = clock();//获取查询开始时间 ,单位是ms
		QueryPerformanceCounter(&lpPerformanceCount);
		c1 = lpPerformanceCount.QuadPart;
		ret = search_dict(cmd,dict, n, content);//查找
		if (ret == 0)
		{
			printf("not trant\n");
		}
		else
		{
			printf("翻译为: %s\n", content);
		}
		QueryPerformanceCounter(&lpPerformanceCount);
		c2 = lpPerformanceCount.QuadPart;
		//end = clock();////获取查询结束时间 ,单位是ms
		printf("%d us\n",c2-c1);
	
	}

	system("pause");
	return 0;
}
