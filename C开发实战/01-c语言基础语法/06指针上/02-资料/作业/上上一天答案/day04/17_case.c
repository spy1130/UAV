#include <stdio.h>
#include <stdlib.h>
int main(int argc, char const *argv[])
{
	int num[10] = {0};
	int len = sizeof(num)/sizeof(num[0]);

	printf("������10������\n");
	//�Ӽ��̻�ȡ����
	for (int i = 0; i < len; ++i)
	{
		scanf("%d", &num[i]);
	}

	//����ǰ��������
	for (int i = 0; i < len; ++i)
	{
		printf("%d ", num[i]);
	}
	printf("\n");

	for (int i = 0, j = len-1; i < j; ++i,j--)
	{
		int tmp;
		//����������
		tmp = num[i];
		num[i] = num[j];
		num[j] = tmp;
	}

	//���ú��������
	for (int i = 0; i < len; ++i)
	{
		printf("%d ", num[i]);
	}
	printf("\n");
	
	system("pause");
	return 0;
}