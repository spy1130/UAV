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




int main()
{
	int  num = 0x01020304;
	char  *p1 = (char *)&num;//int *
	short *p2 = (short *)&num;
	int *p3 = &num;
	//通过*取指针变量所指向那块空间内容时,取的内存的宽度和指针变量本身的类型有关

	/*printf("%x\n",*p1);
	printf("%x\n", *p2);
	printf("%x\n", *p3);*/
	printf("%u\n",p1);
	printf("%u\n", p2);
	printf("%u\n", p3);

	printf("%u\n", p1+1);
	printf("%u\n", p2+1);
	printf("%u\n", p3+1);
	system("pause");
	return 0;
}


int main02()
{
	char  *p1;
	short *p2;
	int *p3;
	int **p4;//p4也是一个指针变量  int **

	printf("%d\n",sizeof(p1));
	printf("%d\n", sizeof(p2));
	printf("%d\n", sizeof(p3));
	printf("%d\n", sizeof(p4));
	system("pause");
	return 0;
}

int main01()
{
	// 在使用时,对一个表达式取*,就会对表达式减一级*,如果对表达式取&,就会加一级*
	int  a = 10;
	//定义指针的三步骤
	//1  *与符号结合代表是一个指针变量  2 要保存谁的地址,将他的定义形式放在此处
	//3 用*p替换掉定义的变量
	//*p
	int  *p;
	p = &a;
	//分析
	//1与*结合代表这个一个指针变量
	//2p是变量,p的类型是将变量p本身拖黑,剩下的类型就是指针变量的类型  int   *
	//3指针变量p用来保存什么类型数据的地址 ,将指针变量p和指针变量p最近的*一起拖黑,
	//剩下什么类型就保存什么类型数据的地址
	//p = &a;

	*p = 100;// 在使用时,*与p结合代表,取p指针所指向那块空间的内容
	printf("a=%d\n",a);
	int  b = 200;
	p = &b;

	system("pause");
	return 0;
}

