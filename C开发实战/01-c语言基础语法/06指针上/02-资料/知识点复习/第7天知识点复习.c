一、 如何调用库函数(别人写好的函数)
当调用函数时，需要关心5要素：
	1)头文件：包含指定的头文件，头文件主要包含此函数的声明
	2)函数名字：函数名字必须和头文件声明的名字一样
	3)功能：需要知道此函数能干嘛后才调用
	4)参数：参数类型要匹配
	5)返回值：根据需要接收返回值，也就是说函数的返回值可以不用

二、字符串处理函数
1、字符串输入
	char str[100];
	scanf("%s", str);
	
	//从键盘读取字符串，允许有空格
	//读取的字符串不是给str赋值，给给str所代表的数组拷贝内容
	gets(str);
	
	//从stdin(代表标准输入设备，键盘)读取内容，最大读取大小为sizeof(str)-1
	//换行符也会读取
	fgets(str, sizeof(str), stdin);
	
2、字符串的输出
	char str[] = "hello mike";
	//%s代表打印字符串，从起点(首地址)到终点(字符串结束符'\0')
	printf("str = %s", str);
	
	//在打印时，字符串结尾自动加"\n"
	//只是屏幕视角上换行了，字符串没有改变
	puts(str);
	
	//往标准输出设备stdout(屏幕)输出指定的字符串(str)，和printf类似
	fputs(str, stdout);
	
3、字符串常用处理
1)获取字符串长度(需要使用返回值)
	char str1[] = "abc";
	//sizeof：测数据类型(数组)的大小，不会受数字0影响
	//strlen: 测字符串的长度，遇到数字0和字符'\0'结束
	printf("%lu, %lu\n", sizeof(str1), strlen(str1));
	
2)字符串拷贝
	char dst[100] = "1111111111111";
	char src[] = "hello mike";
	//把src所代表的字符数组的内容，给dst所代表的数组拷贝内容
	strcpy(dst, src); //dst = "hello mike"
	
	//把src所代表的字符数组的内容，指定拷贝的长度n, 给dst所代表的数组拷贝内容
	//strncpy(dst, src, sizeof(src));
	strncpy(dst, src, 5); //dst = "hello111111";
	
3)字符串追加(连接)
	char dst[100] = "abc";
	char src[] = "hello mike";
	
	//把src追加到dst后面
	strcat(dst, src); //dst = "abchello mike";
	
	char dst[100] = "abc";
	char src[] = "hello mike";
	
	//把src的前5个字符追加到dst
	strncat(dst, src, 5); //dst = "abchello";

4)字符串大小比较
	char dst[] = "hello A";
	char src[] = "z";
	//从左往右比较，按字符的ASCII码大小比较
	//相等=0，大于>0，小于<0
	int flag = strcmp(dst, src);
	
	char dst[] = "hello A";
	char src[] = "hello mike";
	//比较前5个字符
	int flag = strncmp(dst, src, 5);

4、格式化字符串
	char dst[100];
	//a放在%d的位置，ch放%c的位置，格式化这么一个字符串
	//这个字符串放在dst所在的数组
	int a = 10;
	char ch = 'a';
	sprintf(dst, "a = %d, ch = %c", a, ch);
	
	char buf[] = "a = 11, b = 22, c = 33";
	int a, b, c;
	//从buf读取内容，并按指定格式提取内容，整型是很容易提取的
	sscanf(buf, "a = %d, b = %d, c = %d", &a, &b, &c);
	printf("a = %d, b = %d, c = %d\n", a, b, c);
	
	char buf3[] = "abc mike jiang";
	char a2[100], b2[100], c2[100];
	sscanf(buf3, "%s %s %s", a2, b2, c2);//如果提取字符串，最好空格分隔
	printf("a2 = %s, b2 = %s, c2 = %s\n", a2, b2, c2);

5、字符串查询(需要使用返回值)
	char buf[] = "abcgdefghi";
	//查找第一个出现'g'的位置
	//如果找到返回元素的地址，没有找到返回NULL
	//NULL就是数字0
	char *p = strchr(buf, 'g');
	if(p != NULL)
	{
		printf("p = %s\n", p);
	}
	
	char buf[] = "bsdjgksdajabcgdefghi";
	//查找第一个出现'abc'的位置
	//如果找到返回元素首地址，没有找到返回NULL
	char *p = strstr(buf, "abc");
	if(p != NULL)
	{
		printf("p = %s\n", p);
	}

6、字符串切割(需要使用返回值)
	char dst[100] = "abc*mike*jiang*hehehe";
	char buf[100];
	strcpy(buf, dst);
	
	char *p = NULL;
	//第一次切割，第一个参数一定要写字符串的首地址
	//以"*"切割，找到第一个"*"，把"*"替换为'\0'
	//如果成功，返回切割后的字符串，如果失败，返回NULL
	p = strtok(buf, "*");
	
	while(p != NULL)
	{
		printf("p = %s\n", p);
		//下一次切割，第一个参数一定要写NULL
		p = strtok(NULL, "*");
	}
	
7、字符串转整型(需要使用返回值)
	char str1[] = "-10";
	int num1 = atoi(str1);
	printf("num1 = %d\n", num1);

	char str2[] = "0.123";
	double num2 = atof(str2);
	printf("num2 = %lf\n", num2);
	
三、函数
1、函数的作用
	1)理解公司有部门和没部门的区别，程序比作公司，函数比作部门
	2)减少代码的冗余
	3)代码根据简洁清晰（模块化）
	
2、函数的定义和调用
1)函数定义和调用的关系
	a)函数定义类似于厨房做好的菜，函数调用类似于点菜，只有点菜了做好的菜才有意义
	b)函数只有调用了，才会跳入函数定义的代码

2)无参无返回值的函数
a)函数定义
	//1、如果没有返回值，函数名字的前面用void修饰
	//2、fun就是函数的名字，它就是标示符，函数名字的右边()，函数名字不能同名
	//	 函数的定义和变量的区别，比变量多了一个()
	//3、()里面的元素叫参数，函数定义时，叫形参，函数调用时叫实参
	//4、()没有写东西，代表这个函数是没有参数的，也可以用void关键字修饰
	//5、函数名()下面有{}，{}就是函数体
	//6、函数功能的实现是要根据需求的，把以前在main写的代码换个地方写


	//void fun() //和下面是等级
	//void关键字只能在定义时出现
	void fun(void)
	{
		printf("this is my first function\n");
	}

b)函数调用
	//函数的调用不可能出现void关键字
	//f10, 跳过函数
	//f11, 调入函数内部
	fun();
	
3)有参无返回值的函数
a)函数定义
	//1、如果函数是带参数的，定义参数格式：类型+变量，变量不要赋值
	//2、如果参数有多个，用","分隔
	//3、不同函数的变量是可以同名的，把函数比作房子，虽然同名，但是2个变量没有关系
	//4、函数的变量只能在本函数使用，离开函数无法使用
	//5、尽管在函数内部定义了变量，要在函数调用时，这些变量才会分配空间，函数调用完毕变量自动释放
	void fun(int a)
	{
		int b = 10;
		printf("a = %d, b = %d\n", a, b);
	}

	void fun1(int a, int b, char buf[100])
	{
		printf("a = %d, b = %d, buf = %s\n", a, b, buf);
	}
	
b)函数调用
	//有参函数调用
	//1、函数定义时()参数叫形参，函数调用时()参数叫实参
	//2、如果函数定义是有参数的，那么调用时，必须传匹配类型的实参
	//3、传参的实参，可以是常量、变量、表达式
	//4、传参只能是实参给形参，不能反过来，传参是单向传递
	//5、如果类型不匹配，类型兼容也是可以（内部能自动转换）
	
	fun(11); //常量
	
	int a = 22;
	fun(a); //变量
	
	fun(a = 250); //表达式
	
	fun(1 > 2);
	fun(11.11); //自动转换为int，再传参
	
	fun1(10, 20, "hello mike");
	
4)无参有返回值的函数
a)函数定义
	//1、如果函数有返回值，函数名字的前面写一个返回类型
	//2、函数内部通过return返回
	//3、返回可以是常量，变量，表达式
	//4、return后面跟的常量，变量，表达式类型最好和返回类型匹配，如果不匹配，由函数的返回类型决定
	int fun3()
	{
		return 11.11;
	}

	int fun()
	{
		return 250;
	}

	int fun1()
	{
		int a = 250;
		return a;
	}

	int fun2()
	{
		
		return 1+1;
	}
	
b)函数调用
	//函数的调用
	//1、如果函数有返回值，这个返回值可以不用
	//2、如果要用，一定要定义一个匹配类型的变量接收
	
	//int fun(); //err
	//int = fun(); //err
	
	int a = 0;
	a = fun(); //ok
	printf("a = %d\n", a);
	
	int b = fun(); //ok
	
	double c = fun3();
	printf("c = %lf\n", c);
	
3、return关键字和exit()函数区别
	1)return关键字是中断函数
	2)return中断main()函数程序结束，return中断其它函数，程序不结束
	3)exit()函数功能为中断整个程序
	
4、函数的定义和声明
	1)如果函数的定义没有放在main函数的前面，最好在使用前先声明函数
	2)声明函数的作用告诉编译器，这个函数是有定义的，只是放在别的地方定义
	3)函数的声明是把函数定义的{}去掉，后面加分号";"，函数声明前面加不加extern都一样
	4)函数只能定义一次，但可以声明多次，函数声明时，形参变量名可以不写
	5)我们平时使用库函数，首先需要包含头文件，实际上就是为了函数声明，因为头文件主要放的是函数的声明
	
	void fun(); //函数声明，extern加不加一样
	
	void test(int a, int b);
	void test(int, int); //声明时，形参变量名可以不用写
	
	int main()
	{
		fun();

		return 0;
	}

	void fun() //函数的定义
	{
		printf("this is my function\n");
	}
	
5、分文件(多文件)编程
1）xxx.h
	主要放函数的声明
	
2）xxx.c
	主要放函数的定义
	
3）主函数所在的文件
	#include "xxx.h" //包含头文件，为了函数的声明
	
	int main()
	{
		//使用xxx.c的函数
		
		return 0;
	}
	
6、防止头文件重复包含或嵌套包含
1）
#ifndef __SOMEFILE_H__
#define __SOMEFILE_H__

// 声明语句

#endif

2）
#pragma once

// 声明语句
