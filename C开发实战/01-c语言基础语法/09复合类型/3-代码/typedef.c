#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <windows.h>
#define  MAX  3+4
#define  CHAR   char *
typedef char*  CHAR32;
int main()
{
	printf("------------\n");
	Sleep(3000);
	CHAR x,y;//char *x,y;
	CHAR32 j,k;//

	printf("%d %d\n",sizeof(x),sizeof(y));
	printf("%d %d\n", sizeof(j), sizeof(k));
	/*a = 10;
	b = 20;
	printf("%d\n",sizeof(a));
	printf("%d\n", sizeof(b));*/


	system("pause");
	return 0;
}










typedef int u32;
struct stt {
	int  id;
	int age;

};
typedef struct stt TT;
typedef struct stt BB;
int main25()
{
	int  a = 10;
	u32  b = 20;
	printf("%d %d\n",sizeof(a),sizeof(b));
	TT tmp;
	BB p;
	tmp.id = 10;
	tmp.age = 20;
	system("pause");
	return 0;
}



