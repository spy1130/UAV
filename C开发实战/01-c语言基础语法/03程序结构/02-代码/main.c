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


int main19()
{
	printf("我爱你\n");
	printf("我爱你\n");
	printf("我爱你\n");
	printf("我爱你\n");

	system("pause");
	return 0;
}

//switch
int main18()
{
	int num = 0;
	int a = 0;
	scanf("%d", &num);
	a = num % 4;//0 1  2  3
	switch (a)//()里面的判断条件只能是整数
	{
		case 0:
			printf("0\n");
			printf("hello\n");
			break;//跳出switch语句
		case 1:
			printf("1\n");
			break;//跳出switch语句
		case 2:
			printf("2\n");
			break;//跳出switch语句
		default://默认
			printf("3\n");
			break;//跳出switch语句
	}

	system("pause");
	return 0;
}

//三目运算符
int main17()
{
	int  a = 10;
	int b = 20;
	int c = 0;
	//求a和b的最大值给c
	//if (a > b)
	//{
	//	c = a;
	//}
	////else
	//{
	//	c = b;
	//}
	c = a > b ? a : b;
	printf("c=%d\n",c);

	system("pause");
	return 0;
}


int main16()
{
	//如果结果有多种但是不确定是哪一种,而且每个结构是互斥的
	int num = 0;
	int a = 0;
	scanf("%d",&num);
	a = num % 4;//0 1  2  3
	if (0 == a)
	{
		printf("余 0\n");
	}
	 else if (1 == a)
	{
		printf("余 1\n");
	}
	else if( 2 == a)
	{
		printf("余 2\n");
	}
	else if(3 == a)
	{
		printf("余 3\n");
	}


	system("pause");
	return 0;
}


int main15()
{
	int a = 1;
	int b = 2;
	if (a > b)
	{
		printf("a>b\n");
	}
	else
	{
		printf("a<=b\n");
	}
		


	system("pause");
	return 0;
}

int main14()
{
	int  a = 2;
	int b = 3;
	//if后面不要加 分号,分号是空语句
	//一般if后面加上{},{}里面的语句都属于if
	//如果if后面不加{},只有if后面的一条语句属于if
	/*if (a == b);
	{
		printf("a==b\n");
	}*/
	if (a != 3)//最好常量写左边
	{
		printf("a==b\n");
		printf("bbbbb\n");
	}
	printf("aaaaaa\n");

	system("pause");
	return 0;
}


int main13()
{
	int  a = 3;
	double b = (double)a;//隐式转换
	//类型的转换  所需要的类型和给的类型不匹配,需要转换
	//强制转换  (需要转的类型)原来的数据类型
	printf("%d\n",(int)3.14);
	printf("%lf\n",(double)a);


	system("pause");
	return 0;
}

int main12()
{
	int a = 1;
	int b = 2;
	//逗号运算符,最终的结果是最后一个表达式的结果
	int c = (a++,b++,a+b,10,200,a+b,1000);
	printf("%d\n",c);

	system("pause");
	return 0;
}


int main11()
{
	int a = 1;
	int b = 2;
	int c = 0;
	//c += a *= 10;//a=a*10  c=c+a
	//printf("c=%d\n",c);
	printf("%d\n",c+++b);//c+b, c=c+1 

	system("pause");
	return 0;
}

int main10()
{
	int a = 0;
	int b = 1;
	int c = 0;
	printf("%d\n",a || b);
	printf("%d\n", a || c);
	printf("%d\n", b || a++);
	printf("a=%d b=%d\n",a,b);
	system("pause");
	return 0;
}

int main09()
{
	//非0 为真
	int  a = 0;
	int b = 1;
	/*printf("%d\n",!a);
	printf("%d\n", !0);
	printf("%d\n", !-1);*/
	//逻辑&&  A && B   必须A和B都为真,整个表达式才为真
	//如果A 表达式为假,B表达式不执行
	printf("%d\n",a && b++);
	printf("a=%d b=%d\n",a,b);


	system("pause");
	return 0;
}


int main08()
{
	printf("%d\n",3==4);
	printf("%d\n", 3 != 4);
	printf("%d\n", 3 > 4);
	printf("%d\n", 3 < 4);
	printf("%d\n", 3 <= 4);
	system("pause");
	return 0;
}

//赋值运算
int main07()
{
	int  a = 1;
	//a = a + 2;  a +=2;
	//a += 2;
	//a -= 5;//a= a-5;
	//a *= 5;//a =a*5
	printf("%d\n",a);

	system("pause");
	return 0;
}


int main06()
{
	// 自加 自减
	//a = a + 1;// a++  ++a
	int  a = 1;
	int b = 0;
	int c = 2;
	//如果a++  和++a单独使用,效果相同 都是a = a+1
	//a++;//a=a+1
	//++a;//a=a+1;
	//b = a++;//  ++在后,先使用,在自加 b=a, a=a+1
	b = ++a;//++在前  先自加,在使用a=a+1, b=a
	printf("b=%d a=%d\n",b, a);
	//printf("c= %d\n",c++);//先打印(使用),在自加
	printf("c= %d\n", ++c);//先自加,在使用
	printf("c= %d\n", c);
	system("pause");
	return 0;
}


int main05()
{
	int  num = 8981234;
	int  a = num % 10;//个位
	int b = num / 10 % 10;//十位
	int c = num / 100 % 10;//百位
	int d = num / 1000 % 10;//千位
	printf("%d %d %d %d\n",d,c,b,a);
	system("pause");
	return 0;
}


int main04()
{
	int  a = 2;
	int b = 3;
	int c = b%a;//
	printf("%d\n",c);

	system("pause");
	return 0;
}

int main03()
{
	int a = 10;
	int b = 20;
	int c = a + b;
	int d = a - b;
	int e = a *b;
	printf("%d %d %d\n",c,d,e);
	//两数相除,如果要得到小数,必须有一个是double类型或float类型
	//double f = a*1.0 / b;//0.5
	//int f = b / a;
	//int f = a / 0;err 除数不能为0

	//printf("%lf\n",f);

	system("pause");
	return 0;
}

int main02()
{
	short a = 0xfffe;//65535  255
	//补码:  1111 1111 1111 1110
	//反码: 1000 0000 0000 0001
	//原码:1000 0000 0000 0010
	printf("%hd\n", a); //输出结果为_____
	printf("%hu\n", a);//1111 1111 1111 1110

	system("pause");
	return 0;
}

int main01()
{
	//如果最高位为1,向前扩展1,如果最高位是0,向前扩展0
	//1111 1111 1111 1111 1111 1111  0000 0001
	//char num = 0x81;
	//8位补码: 1000 0001 ->8位的原码 -> 32位原码->   32位补码  -> 32原码
	//8位的原码: 1111 1111
	//32位原码: 1000 0000 0000 0000 0000 0000 0111 1111 = -127
	//32位的补码: 1111 1111 1111 1111 1111 1111 1000 0001 = ffffff81
	//printf("%d\n",num);//-127
	char num = 0x12;//1000 0010-> 1111 1111 1111 1111 1111 1111 1000 0010
	//0001 0010 -> 0000 0000 0000 0000 0000 0000 0001 0010
	printf("%x\n",num);//4294967169
	system("pause");
	return 0;
}
