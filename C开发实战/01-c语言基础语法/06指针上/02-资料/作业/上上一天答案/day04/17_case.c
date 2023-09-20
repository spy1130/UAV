#include <stdio.h>
#include <stdlib.h>
int main(int argc, char const *argv[])
{
	int num[10] = {0};
	int len = sizeof(num)/sizeof(num[0]);

	printf("请输入10个整数\n");
	//从键盘获取输入
	for (int i = 0; i < len; ++i)
	{
		scanf("%d", &num[i]);
	}

	//逆置前遍历数组
	for (int i = 0; i < len; ++i)
	{
		printf("%d ", num[i]);
	}
	printf("\n");

	for (int i = 0, j = len-1; i < j; ++i,j--)
	{
		int tmp;
		//两变量交换
		tmp = num[i];
		num[i] = num[j];
		num[j] = tmp;
	}

	//逆置后遍历数组
	for (int i = 0; i < len; ++i)
	{
		printf("%d ", num[i]);
	}
	printf("\n");
	
	system("pause");
	return 0;
}