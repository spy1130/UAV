#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int a = 10;

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void mem_p(char *q)
{
	q = malloc(1024);
	return  q;

}
void mem_p2(char **k)
{
	 *k = malloc(1024);
	return  ;

}
int main04()  
{
	char  *p = NULL;
	// mem_p(p);
	mem_p2(&p);//
	strcpy(p,"hello");
	printf("p=%s\n",p);
	system("pause");
	return 0;
}







char *fun4()
{
	char *q = malloc(100);
	return q;//ok  �����ĵ�ַ�ǿ��Է��ص�,���������������ᱻ�ͷ�
}
int main03()
{
	char *p = fun4();
	//p = "hello";
	strcpy(p,"hello");
	free(p);//err  p��û��ָ�����,����ָ�����ֳ�����"hello"


	system("pause");
	return 0;
}



// �βεı��ʾ��Ǿֲ�����
int *fun2(int sum)
{
	//int sum;
	sum += 100;
	return &sum;//err �����Է����βεĵ�ַ
}
int *fun3(int *k)
{
	int  i = 100;
	*k = *k + i;
	return k;
}
int main02()
{
	int  num = 10;
	//int *p = fun(num);//err �����Է����βεĵ�ַ
	int  *p = fun3(&num);
	*p = 1000;


	system("pause");
	return 0;
}


int * fun()
{
	//int a = 10;
	//static  int  a = 10;
	a *= 10;
	return &a;
}

int main01()
{
	int * p = fun();
	*p = 2000;//  p��ָ��Ŀռ�û���ͷ�(��̬�ֲ�����),����Բ�������ڴ�,
	//�ͷŲ����Բ���(��ͨ�ֲ�)
	printf("%d\n",*p);
	system("pause");
	return 0;
}
