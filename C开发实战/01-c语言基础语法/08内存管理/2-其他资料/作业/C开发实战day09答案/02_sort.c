#include <string.h>
#include <stdio.h>

//%s方式打印数组的元素
void print_word(char *words[], int n) //n代表数组元素个数
{
	int i = 0;
	for(i = 0; i < n; i++)
	{
		printf("%s ", words[i]);
	}
	printf("\n");
}

//冒泡排序
void sort_word(char *words[], int n)
{
	int i = 0;
	int j = 0;
	char *tmp;
	for(i = 0; i < n-1; i++)
	{
		for(j = 0; j < n-1-i; j++)
		{
			if(strcmp(words[j], words[j+1]) > 0 )
			{
				tmp = words[j];
				words[j] = words[j+1];
				words[j+1] = tmp;
			}
		}
	}
}

int main()
{
	char *words[] = {"city", "student", "tree", "bee"};
	
	int n = sizeof(words)/sizeof(words[0]);
	
	//排序前，city student tree bee
	print_word(words, n);
	
	//冒泡排序
	sort_word(words, n);
	
	//排序后，bee city student tree
	print_word(words, n);
	

	return 0;
}
