#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
/*#define SUN 0
#define RAIN 1
#define SNOW 2 */ 

enum ab { SUN  , RAIN, SNOW};

int main23()
{
	enum ab tmp = SNOW;
	printf("%d %d %d\n",SUN,RAIN,SNOW);
	int  a = 0;
	scanf("%d",&a);
	if (SUN == a)
	{
		printf("sleep\n");
	}
	else if(RAIN == a)
	{
		printf("music\n");
	}
	else if (SNOW == a)
	{
		printf("game\n");
	}


	system("pause");
	return 0;
}


//bool
//#include <stdbool.h>
enum BOLL { false , true};
//给类型取别名
typedef enum BOLL bool;
int main24()
{
	bool a;
	a = false;
	printf("%d\n", a);
	printf("%d\n", false);
	printf("%d\n", true);


	system("pause");
	return 0;
}
