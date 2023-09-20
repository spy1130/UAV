#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//空指针
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
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int num = 0;//在函数外面定义的变量叫全局变量,整个工程都可以使用
//整个变量程序启动开辟空间,直到程序结束释放空间
int * getnum()
{
	//{}中定义的变量叫局部变量,局部变量在函数结束之后的空间会被释放
	srand(time(NULL));
	 num = rand();
	return &num;//

}

int main()
{
	int * p = getnum();
	printf("%d\n",*p);


	system("pause");
	return 0;
}

//数组作为函数的形参会退化为指针
//void print_arr(int b[10]) // int  *b
//void print_arr(int b[1000])//int  *b

void print_arr(int *b,int  len)

{
	int  n = sizeof(b) / sizeof(b[0]);  // *(b+0)  == *b
	printf("n=%d\n",n);
	for (int i = 0; i <len; i++)
	{
		printf("%d ",b[i]);
	}
	printf("\n");
}
int main13()
{
	int  a[10] = { 1,2,3,4,5,6,7,8,9,10 };

	print_arr(a,sizeof(a)/sizeof(a[0]));//打印数值的内容//  &a[0]   int *


	system("pause");
	return 0;
}

void swap(int x, int y)
{
	int k = x;
	x = y;
	y = k;
	printf("x=%d y=%d\n",x,y);
	return;
}

void swap2(int*x, int *y)
{
	int  k = *x;
	*x = *y;
	*y = k;
	printf("x=%d y=%d\n", *x, *y);

}
int main12()
{
	int  a = 10;
	int b = 20;
	//swap(a,b);
	swap2(&a, &b);
	printf("a=%d b=%d\n", a, b);

	system("pause");
	return 0;
}


int main11()
{
	int a = 10;
	int b = 20;
	int c = 30;
	// int *p1 = &a  int *p2 = &a  int *p2 = &a
	//需求:  数组中的每一个元素都是指针(地址)

	int *num[3] = {&a,&b,&c};
	//printf("%d\n",sizeof(num));
	////&a  ==  num[0]
	//for(int i=0;i<sizeof(num)/sizeof(num[0]);i++)
	//{
	// printf("%d\n",*num[i]);
	//
	//}
	//定义一个指针用来保存数组num首元素的地址
	// num ==  &num[0] =   &(int *)  == int **
	//num[0]是int *类型,要保持int  *类型的地址,需要比它多一级*
	int **k = num;
	for (int i = 0; i < sizeof(num) / sizeof(num[0]); i++)
	{
		printf("%d ",**(k+i));
	}
	


	system("pause");
	return 0;
}

int main10()
{
	//[] == *()
	int  a[10] = { 1,2,3,4,5,6,7,8,9,10 };
	int *p = a;
	for (int i = 0; i < sizeof(a) / sizeof(a[0]); i++)
	{
		//printf("%d ",a[i]);//a[i] == *(a+i)
		//printf("%d ", *(p+i));
		//printf("%d ", p[i]);// p[i]  == *(p+i)
		printf("%d ", *(a + i));
	}


	system("pause");
	return 0;
}

int main09()
{
	//[]是不是数组的专属
	//int  a[10] = { 1,2,3,4,5,6,7,8,9,10 };
	//  []  ==  *()
	//p[0]   ==  *(p+0)
	int a = 10;
	int *p = &a;
	p[0] = 100;
	//p[1] = 200;
	printf("a=%d\n",a);

	system("pause");
	return 0;
}


int main08()
{
	int  a[10] = {1,2,3,4,5,6,7,8,9,10};
	//sizeof(int [10])
	int *p = a;
	//int  *q = (int *)(&a + 1) - 1;
	int  *q = &a[9];
	printf("%d\n",q-p);//  p+9 ==  q
	printf("%d\n",*(p+3));
	//两指针相加没有意义
	// printf("%d\n", p+q);err

	system("pause");
	return 0;
}


int main07()
{
	//int  a[10] = {1,2,3,4,5,6,7,8,9,10};
	int  a[10] = { 0 };
	//a 数组名,首元素的地址
	int  *p = a;//指针p保存的是首元素的地址
	for (int i=0;i<sizeof(a)/sizeof(a[0]);i++)
	{
		//printf("%d ",a[i]);
		//printf("%d ", *(p+i));
		*(p + i) = i;
	}
	for (int i = 0; i<sizeof(a) / sizeof(a[0]); i++)
	{
		printf("%d ",a[i]);
		//printf("%d ", *(p+i));
		//*(p + i) = i;
	}


	system("pause");
	return 0;
}

//多级指针
int main06()
{	
	int a = 10;

	//*p  int a     int *p
	int *p = &a;

	//*q  int *p   int **q
	int **q = &p;
	//如果*和&相遇,相抵消
	// **q == *(*q) == *(p) ==  a
	//**q == *(*q) == *(&a) ==  a
	printf("%d\n", **q);

	// *k  int **q  int ***k
	int ***k = &q;

	//*符号结合,代表这个k是一个指针变量
	//k是一个变量
	//k的类型,将变量k拖黑,剩下的类型
	//k用来保存谁的地址  将变量k和k最近的*一起拖黑,剩下什么类型
	//就保存什么类型数据的地址

	int *******************g;
	int ********************f = &g;

	system("pause");
	return 0;
}

int main05()
{
	int  a = 10;
	int  b = 20;
	//const修饰的是 * 还是变量p,
	//这里修饰的是*
	
	//const int  *p = &a;//不能通过 *p,改p所指向空间的内容
	//*p = 100; err  因为不能通过p改p所指向空间的内容

	//const修饰的变量p
	//p保存的地址不可以修改
	//int  * const p = &a;
	//p = &b;err  p本身的值不能被更改

	const  int *const p = &a;//p本身的指向不能改变,不能通过*p修改p
	//向那块空间的内容


	system("pause");
	return 0;
}

int main04()
{
   const	int  a = 10;//修饰变量a,不能再通过a修改a内存里面的内容
   int  *p = &a;
   *p = 100;
   printf("%d\n",*p);
   printf("a= %d\n", a);


	system("pause");
	return 0;
}

//万能指针
int main03()
{
	//void b; 不可以定义void类型的变量,因为编译器不知道给变量分配多大的空间
	//但是可以定义void *类型,因为指针都是4个字节
	int  a = 10;
	short b = 10;

	void *p = (void *)&a;//万能指针可以保存任意的地址
	void  *q = (void *)&b;
	//printf("%d\n", *p);//err  p是void*,不知道取几个字节的大小
	printf("%d\n",* (int *)p);// *(  (int *)地址)
	system("pause");
	return 0;
}

int main02()
{
	int  a;
	//将指针的值赋值为0,0x0000000 =  NULL
	int  *p = NULL;//给指针p的内容赋值为0
	
	*p = 200;//err  因为p保存了0x0000的地址,这个地址是不可以使用的,非法
	printf("%d\n",*p);


	system("pause");
	return 0;
}

//野指针
int main01()
{
	//野指针就是没有初始化的指针,指针的指向是随机的,不可以 操作野指针
	//int  a = 0;
	//指针p保存的地址一定是定义过的(向系统申请过的)
	int  *p;//野指针  
	*p = 200;
	printf("%d\n",*p);
	system("pause");
	return 0;
}


