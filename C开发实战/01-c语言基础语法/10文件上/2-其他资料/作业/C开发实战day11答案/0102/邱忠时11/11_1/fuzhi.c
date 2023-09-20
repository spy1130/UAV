#include "sort.h"

void fuzhi(std **p, int n)
{
	for (std **q = p;q < p + n;q++)   //无需重复指针+i运算
	{
		char str[50];
		printf("Enter your students name and age and score:");
		scanf("%s %d %f", str, &(*q)->age, &(*q)->score);
		(*q)->name = malloc(sizeof(str));     //不浪费空间
		strcpy((*q)->name, str);
	}

	for (std **q = p;q < p + n;q++)		//无需重复指针+i运算
		printf("%s %d %f\n", (*q)->name, (*q)->age, (*q)->score);

}