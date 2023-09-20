#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>


int main01()
{
	char str1[128] = "";//hello
	char str2[128] = "";//hdad
	printf("ÇëÊäÈëÁ½¸ö×Ö·û´®:\n");
	fgets(str1,sizeof(str1),stdin);
	fgets(str2, sizeof(str2), stdin);
	str1[strlen(str1) - 1] = 0;
	str2[strlen(str2)-1] = 0;

	printf("%s\n",str1);
	printf("%s\n", str2);
	int i = 0;
	//hello
	//heffg
	while (str1[i] != 0 && str2[i] != 0 && str1[i] == str2[i])
	i++;

	if (str1[i] > str2[i])
	{
		printf("str1 > str2\n");
	}
	else if(str1[i] < str2[i])
	{
		printf("str1 < str2\n");
	}
	else
	{
		printf("str1 ==  str2\n");
	}

	system("pause");
	return 0;
}
