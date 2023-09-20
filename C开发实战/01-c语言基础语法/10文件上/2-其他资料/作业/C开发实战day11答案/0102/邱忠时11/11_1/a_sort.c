#include "sort.h"



void a_sort(std **p, int n)   //排序
{
	int i = 0;
	int j = 0;
	std *q;

	for (i = 0;i < n - 1;i++)
	{
		for (j = 0;j < n - 1 - i;j++)
		{
			if (p[j]->age > p[j + 1]->age)
			{
				SWAP(p[j], p[j + 1]);  //交换地址
			}

			if (p[j]->age == p[j + 1]->age)
			{
				if (p[j]->score > p[j + 1]->score)
				{
					SWAP(p[j], p[j + 1]);  //交换地址
				}
			}
		}
	}

	printf("按照年龄排序完后：\n");

	for (std **q = p;q < p + n;q++)
		printf("%s %d %f\n", (*q)->name, (*q)->age, (*q)->score);

	for (int i = 0;i < n;i++)
	{
		free(p[i]->name);
		free(p[i]);
	}

		for (int i = 0;i < n;i++)
	{
		p[i] = NULL;
	}

	exit(0);
}