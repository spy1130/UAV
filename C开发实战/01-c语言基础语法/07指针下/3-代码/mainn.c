#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>


int main()
{
	char buf[] = "    hello world     ";//hello world
	char num[128] = "";

	char * start = buf;
	char *end = &buf[strlen(buf) - 1];//end指向最后一个字符
	//找到第一个不是空格的位置
	while (*start == ' ' &&  *start != 0)
	{
		start++;
	}
	while (*end == ' '  &&  end != start)
	{
		end--;

	}
	printf("%d\n",end-start+1);
	strncpy(num,start,end-start+1);
	printf("num=%s\n",num);
	system("pause");
	return 0;
}

int  strstr_num(char *src, char *dst)
{
	int i = 0;
	char *p = src;
	int n = 0;

	do
	{

		p = strstr(p, dst);

		//p = strstr(p+strlen(dst), dst);
		if (p != NULL)//如果查找返回的地址不等于NULL,代表找到了
		{
			n++;
			p = p + strlen(dst);
		}

	} while (p != NULL);
	return n;
}

int main01()
{
	char src[] = "hdaabcdhaodabcahdaabchdoahdoaabcjdahfaabc";
	char dst[] = "abc";
	int n = strstr_num(src, dst);
	printf("%d\n", n);
	system("pause");
	return 0;
}