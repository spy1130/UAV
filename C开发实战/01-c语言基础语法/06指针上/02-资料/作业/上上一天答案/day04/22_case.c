#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char const *argv[])
{
	printf("�Ƚ����ַ����Ĵ�С\n");
	printf("�������ַ���1��");
	char str1[64] = "";
	fgets(str1,sizeof(str1), stdin);
	str1[strlen(str1)-1] = 0;//ȥ���ַ��лس�
	
	printf("�������ַ���2��");
	char str2[64] = "";
	fgets(str2,sizeof(str2), stdin);
	str2[strlen(str2)-1] = 0;//ȥ���ַ��лس�

	int flag = 0;
	for (int i = 0; (str1[i] !=0) || (str2[i] !=0); ++i)
	{
		if(str1[i] < str2[i])
		{
			printf("�ַ���1С���ַ���2\n");
			flag = 1;
			break;
		}
		else if(str1[i] > str2[i])
		{
			printf("�ַ���1�����ַ���2\n");	
			flag = 1;
			break;
		}
	}

	if(flag == 0)
	{
		printf("�ַ���1�����ַ���2\n");
	}
	return 0;
}