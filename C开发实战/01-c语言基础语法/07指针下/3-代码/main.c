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
int  strstr_num(char *src, char *dst)
{
	int i = 0;
	char *p = src;
	int n = 0;
	//char src[] = "hdaabcdhaodabcahdaabchdoahdoaabcjdahfaabc";
	//char dst[] = "abc";
	//while (src[i] != 0)
	
	do
	{
		
			p = strstr(p, dst);
		
			//p = strstr(p+strlen(dst), dst);
			if (p != NULL)//如果查找返回的地址不等于NULL,代表找到了
			{
				n++;
				p = p + strlen(dst);
			}
		
	} while (p != NULL);
	return n;
}

int main()
{
	char src[] = "hdaabcdhaodabcahdaabchdoahdoaabcjdahfaabc";
	char dst[] = "abc";
	int n = strstr_num(src,dst);
	printf("%d\n",n);
	system("pause");
	return 0;
}

//atoi   将字符转整数
int main15()
{
	//0-9的字符和+-号就开始转,如果不是+- 0-9的字符结束
	//如果前面有空格,跳过
	char  num[] = " +1234";
	char str[] = "3.14";

	int  sum = atoi(num);//1234  \r  \n  _  
	printf("%d\n",sum);

	float a = atof(str);
	printf("%f\n",a);
	system("pause");
	return 0;
}

int main14()
{
	char str[] = "15080015225&bangquan#82263&123456";
	char *p[10] = {NULL};//初始化指针数组元素全部为NULL
	//strtok
	//char *p1 = strtok(str,"#");//在str1中将#切割,返回切割前面的字符串
	//printf("%s\n",p1);
	//char *p2 = strtok(NULL,"#");
	//printf("%s\n",p2);
	//char *p3 = strtok(NULL, "#");
	//printf("%s\n", p3);
	int i = 0;
	do {
		if(i == 0)
			p[i] = strtok(str, "#&");
		else
			p[i] = strtok(NULL, "#&");
		//i++;
	
	} while ( p[i++] != NULL);//p[i] != NULL   i=i+1 如果strtok的返回值等于NULL,代表切割完毕
	i = 0;
	while (p[i] != NULL)
	{
		printf("%s\n",p[i++]);
	}
	printf("str=%s\n",str);
	system("pause");

	return 0;
}

char *my_strstr(char *str1, char *str2)
{
	int i = 0;
	while (str1[i] != 0)
	{
		if (str1[i] == str2[0])
		{
			if (0 == strncmp(str1 + i, str2, strlen(str2)))
				return str1 + i;
		
		}
		i++;
	
	}
	if (str1[i] == 0)
		return NULL;
}
int main13()
{
	char str1[] = "helloaabcfhaffjhafafha";
	char str2[] = "abc";
	//在str1中查找str2字符出现的位置
	//先找a字符,如果找到了a字符,在比较
	char *p = strstr(str1,str2);
	printf("%s\n",p);


	system("pause");
	return 0;
}

char *my_strchr(char *p, char ch)
{
	int i = 0;
	while (p[i] != 0)
	{
		if (p[i] == ch)
			return &p[i];
		i++;
	}
	if (p[i] == 0)
		return NULL;


}
int main12()
{
	char  str[] = "xixihellogworld";
	char *p = strchr(str,'g');
	//char  *p =my_strchr(str,'g');
	printf("%s\n",p);

	system("pause");
	return 0;
}


int main11()
{
	//%d    0-9的字符
	int  year =0 ;
	int  month = 0;
	int day = 0;
	char  buf[1024] = "beijing:2018:t:10:20";
	//scanf("%d:%d:%d",&year,&month,&day);//从键盘按照相应的格式获取数据
	sscanf(buf, "beijing:%d:t:%d:%d", &year, &month, &day);//从buf中按照`相应的格式获取数据
	printf("%d %d %d\n",year,month,day);
	system("pause");
	return 0;
}


int main10()
{
	int  year = 2018;
	int  month = 10;
	int day = 20;
	char buf[1024] = "";
	//printf("year=%d month=%d day=%d \n",year,month,day);
	int len = sprintf(buf,"year=%d %cmonth=%d day=%d \n",year, 0,month, day);
	//printf("%d\n",strlen(buf));
	printf("len=%d\n",len);
	printf("buf=[%s]",buf);

	system("pause");
	return 0;
}


int main09()
{
	char  str1[] = "a\0bcdef";
	char str2[] = "a\0cdrrr";
	//str1数组中和str2数组拿出一个元素进行比较,相等继续往后比较
	//比较的是字符的ascii值
	//如果str1> str2  返回值等于1
	//如果str1==  str2  返回值等于0
	//如果str1 <str2  返回值等于 - 1
	//printf("%d\n",strcmp(str1,str2));
	printf("%d\n", strncmp(str1, str2,3));
	system("pause");
	return 0;
}


int main08()
{
	char  str1[1024] = "123456";//wo\0\0\0      wo\0rl
	char str2[128] = "worldhello";
	//strcat(str1,str2);//将str2的字符串拷贝到str1字符串的后面
	strncat(str1, str2,5);
	printf("%s\n",str1);

	system("pause");
	return 0;
}

int main07()
{
	char  str1[1024] = "";//wo\0\0\0      wo\0rl
	char str2[128] = "wo\0rldhello";
	//strcpy( str1 ,  str2);
	strncpy(str1,str2,5);
//	printf("%s\n",str1);
	for (int i = 0; i < 5; i++)
	{
		printf("%d ",str1[i]);
	}


	system("pause");
	return 0;
}

//.*.exe    hello   123456 
//char *argv[] = { ".*.exe",    "hello"   "123456" };
int main06(int  argc,char *argv[])
{
	/*printf("%d\n",argc);
	printf("%s\n", argv[0]);
	printf("%s\n", argv[1]);
	printf("%s\n", argv[2]);
	printf("%s\n", argv[3]);*/
	for (int i = 0; i < argc; i++)
	{
		printf("%s\n", argv[i]);
	}
	system("pause");
	return 0;
}

//字符指针数组
//是一个数组,每一个元素是字符指针
int main05()
{
	/*char *p1 = "heihei";
	char *p2 = "haha";
	char *p3 = "xixi";*/
	//char *num[3] = { p1,p2,p3};
	char *num[3]={ "heihei" ,"haha","xixi"};
	//定义一个指针保存num数组首元素的地址   &num[0]  num
	char **p = num;
	for (int i = 0; i < 3; i++)
	{
	//	printf("%s\n",*(p+i));
		printf("%s\n", p[i]);
	}
	printf("%c\n",*(*(p+1)+3));// *(p[1]+3)   == p[1][3]
	//for (int i = 0; i < 3; i++)
	//{
	//	printf("%s\n",num[i]);	
	//}
	//printf("%c\n",*num[0]);//
	//printf("%c\n", *(num[1] + 1));
	//printf("%c\n", *(num[2]+2));

	system("pause");
	return 0;
}

int main04()
{
	char  buf[] = "hello";
	char  str[] = "acbg";
	 char const *p = buf;//const修饰指针,不能通过指针修改指针所指向的空间内容
	//*p = 'b';  err  不能通过p指针修改那块空间的内容
	char  * const  k = buf;//指针变量k初始化之后不能改变k指针变量本身的指向
//	k = "world"; err  
//	k = str; err
	system("pause");
	return 0;
}

char * my_strcat(char * src, char *dst)
{
	int n = strlen(src);
	int i = 0;
	while (*(dst + i) !=  0)
	{
		*(src+n+i) =   *(dst + i);
		//src[n+i] = dst[i] ;
		i++;
	
	}
	*(src + n + i) = 0;
	return src;
}

int main03()
{

	char  str1[128] = "hello";//hello123456\0
	char str2[128] = "123456";
	my_strcat(str1,str2);
	printf("%s\n",my_strcat(str1, str2));
	system("pause");
	return 0;
}


int main02()
{
	char  a[] = "helloworld";//定义了一个字符数组,字符数组内容为helloworld
							 //定义一个指针用来保存数组首元素的地址
	char  * p = a;
	p = "abcdef";//字符串常量存文字常量区,""在使用时,取的是字符串首元素的地址
	//文字常量区的内容是不可以改变的
	printf("%s\n",p);

	printf("%d\n",sizeof(p));//4
	printf("%d\n", sizeof("abcdef"));//7

	printf("%d\n", strlen(p));//6
	printf("%d\n", strlen("abcdef"));//6

	*p = 'm';
	printf("%s\n",p);


	system("pause");
	return 0;
}

//Shell   python  lua
int main01()
{
	//指针与字符串
	char  a[] = "helloworld";//定义了一个字符数组,字符数组内容为helloworld\0
	//定义一个指针用来保存数组首元素的地址
	char  * p = a;
	printf("%s\n",p);//%s打印一个字符串,要的是首个字符的地址
	printf("%s\n", p + 2);
	printf("%c\n",*(p+3));
	*p = 'm';
	printf("%s\n", p);
	//a++
	p++;
	*p = 'o';
	printf("%s\n", p);
	//printf("%d\n",sizeof(a));//11
	//printf("%d\n", sizeof(p));//4

	//printf("%d\n", strlen(a));//
	//printf("%d\n", strlen(p));//

	system("pause");
	return 0;
}
