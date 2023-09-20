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
	return q;//ok  堆区的地址是可以返回的,堆区函数结束不会被释放
}
int main03()
{
	char *p = fun4();
	//p = "hello";
	strcpy(p,"hello");
	free(p);//err  p并没有指向堆区,而是指向文字常量区"hello"


	system("pause");
	return 0;
}



// 形参的本质就是局部变量
int *fun2(int sum)
{
	//int sum;
	sum += 100;
	return &sum;//err 不可以返回形参的地址
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
	//int *p = fun(num);//err 不可以返回形参的地址
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
	*p = 2000;//  p所指向的空间没有释放(静态局部变量),则可以操作这块内存,
	//释放不可以操作(普通局部)
	printf("%d\n",*p);
	system("pause");
	return 0;
}
