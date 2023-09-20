#include <stdio.h>

int my_strcmp(char s1[], char s2[])
{
	int i = 0;
	//如果没有到结束符，同时，两字符相等
	while( s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i] )
	{
		i++;
	}
	
	//return s1[i] - s2[i];
	if(s1[i] == s2[i]) //都为'\0'
	{
		return 0;
	}
	else if(s1[i] > s2[i])
	{
		return 1;
	}
	else
	{
		return -1;
	}

	return 0;
}

int main()
{
	char s1[] = "hello world";
	char s2[] = "hello abc";

	int flag = my_strcmp(s1, s2);
	if(flag == 0)
	{
		printf("%s 等于 %s\n", s1, s2);
	}
	else if(flag > 0)
	{
		printf("%s 大于 %s\n", s1, s2);
	}
	else
	{
		printf("%s 小于 %s\n", s1, s2);
	}

	return 0;
}

