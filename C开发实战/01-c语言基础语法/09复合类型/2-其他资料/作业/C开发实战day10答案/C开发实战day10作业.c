1、输入字符无需按回车键
	a)如果是Linux平台，拷贝mygetch.h和mygetch.c到所写代码目录中
	#include "mygetch.h"
	char ch = mygetch(); //mygetch()在mygetch.c内部实现，不是标准函数
	
	b)如果是Windows平台，WINAPI自带类似功能函数
	char ch = _getch(); //需要头文件#include <conio.h>
	
	
2、清屏函数
	system("clear"); //Linux平台
	system("cls");   //Windows平台
	

3、随机数相关函数
	//所需头文件：
	#include <stdlib.h> //srand(), rand()
	#include <time.h> //time()

	srand((unsigned int)time(NULL)); //随机种子
	rand();	//随机数
	
	总共有26个字母，如何产生26个随机字母？
	
	
4、计算耗时
	获取当前系统时间：
	time_t start_time = time(NULL); //需要头文件#include <time.h>
	
	
5、要求适当封装函数，不要所有代码都写在main()函数中

	