#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char const *argv[])
{
	printf("比较两字符串的大小\n");
	printf("请输入字符串1：");
	char str1[64] = "";
	fgets(str1,sizeof(str1), stdin);
	str1[strlen(str1)-1] = 0;//去掉字符中回车
	
	printf("请输入字符串2：");
	char str2[64] = "";
	fgets(str2,sizeof(str2), stdin);
	str2[strlen(str2)-1] = 0;//去掉字符中回车

	int flag = 0;
	for (int i = 0; (str1[i] !=0) || (str2[i] !=0); ++i)
	{
		if(str1[i] < str2[i])
		{
			printf("字符串1小于字符串2\n");
			flag = 1;
			break;
		}
		else if(str1[i] > str2[i])
		{
			printf("字符串1大于字符串2\n");	
			flag = 1;
			break;
		}
	}

	if(flag == 0)
	{
		printf("字符串1等于字符串2\n");
	}
	return 0;
}