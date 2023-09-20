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


int main()
{
	//设置随机数种子
	//获得随机数
	//int  t = time(NULL);//time函数获得当前时间,,s
	srand(time(NULL));//设置种子
	int a = rand();//rand()获得随机数
	printf("a=%d\n",a);
	int b = rand();//rand()获得随机数
	printf("b=%d\n", b);
	system("pause");
	return 0;
}

//字符串追加
int main17()
{
	char str1[128] = "hello";//hello123456
	char str2[128] = "123456";
	int i = 0;
	while (str1[i] != 0)
		i++;//5
	int j = 0;
	while (str2[j] != 0)
	{
		str1[i] = str2[j];
		i++;
		j++;
	
	}
	printf("str1=%s\n",str1);
	system("pause");
	return 0;
}


int main16()
{
	char buf[1024] = "helloworld";
	//printf("%s\n",buf);
	//puts(buf);//数组首元素地址,有换行
	fputs(buf,stdout);//第一个参数,数组首元素地址,stdout标准输出(屏幕)
	system("pause");
	return 0;
}

int main15()
{
	char buf[128] = "helloA";//buf[5]=0;
	//需要找到最后一个字符的下标
	//求的是字符数组有效字符的个数
	int i = 0;
	/*while (buf[i] != '\0')
	{
		i++;
	}
	printf("i=%d\n",i);*/
	i = strlen(buf);//strlen()测字符数组有效字符的个数
	printf("i=%d\n", i);
	buf[i - 1] = '\0';
	printf("%s\n",buf);
	system("pause");
	return 0;
}


int main14()
{
	//fgets会把回车键\n读取
	char buf[1024] = "";
	fgets(buf,sizeof(buf),stdin);//hello\n
	buf[strlen(buf) - 1] = 0;
	printf("%s\n",buf);

	system("pause");
	return 0;
}


int main13()
{
	//gets遇到\n结束.,但是遇到空格不结束读取空格
	//gets也会造成内存污染
	char  num[5] = "";
	gets(num);//()里面的参数要的是存放读取字符串的地址
	printf("num=%s\n",num);

	system("pause");
	return 0;
}

int main12()
{
	char  ch = 0;
	//scanf("%c",&ch);  从键盘读取一个字符
	//读取一个字符串

	char  num[5] = "";
	//%s从键盘获取一个字符串,遇到\n结束
	scanf("%s",num);

	//%s  要的是打印字符数组的首元素地址
	printf("[%s]\n",num);


	system("pause");
	return 0;
}


int main11()
{
	//char  a[128] = "abcd\0def\0";
	//char  a[128] = { 'a','b',cd\0def\0 };
	char a[] = { 'a','b',0,'c' };
	char b[] = { 'a','b','0','c' };
	char c[] = { 'a','b','\0','c' };
	//printf("%d\n",sizeof(a));//128
	printf("%s\n",a);//ab
	printf("%s\n", b);//ab0c.....乱码
	printf("%s\n", c);//ab
	system("pause");
	return 0;
}

int main10()
{
	//"hello"
	//字符数组
	//字符串就是字符数组中有\0字符的数组
	//因为有\0字符的字符数组,操作起来方便
	//char  a[5] = {'a','b','c','d','e'};普通的字符数组
	//char  a[5] = {'a','b','c','d','\0'};//字符数组中含有\0字符的,它也是字符串
	//char  a[5] = "abcd";//定义了一个字符数组,存的是abcd\0
	//char  a[] = "world";//
	//char  a[100] = "abcd";//定义了一个字符数组,有100个元素
	//char  a[100] = "\0";//将数组的第0个元素填\0,其他元素就是\0
	char  a[100] = { 0 };//将一个字符数组清0
	/*for (int i = 0; i < sizeof(a) / sizeof(a[0]); i++)
	{
		printf("%c",a[i]);
	}*/
	printf("%s\n",a);
	printf("\n");
	printf("%s\n","hello");
	system("pause");
	return 0;
}
