#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct Time
{//表示时间的数据类型
	int year;
	int mon;
	int day;
	int week;
	int hour;
	int minute;
	int second;
}std;

int main()   //偷懒版本
{

	std tme;
	getchar();
	while (1)
	{
		FILE *fp;  //popen 需要FILE 类型的指针
		char buf[100];
		fp = popen("date", "r");   //“r”表示读取
								   //运行终端命令,将指针指向终端输出，并返回该指针；

		fgets(buf, sizeof(buf), fp);//将终端输出的内容放入buf
		pclose(fp);  //与popen配对
					 //时间格式 年（空格）月（空格）日（空格）星期（空格）时间(空格)
					 //例如：2018年 03月 27日 星期二 21:19:49 CST
		for (int i = 0;i < sizeof(buf);i++)
		{
			if (buf[i] == '\n')
				buf[i] = '\0';
		}
		printf("%s", buf);
		fflush(stdout);
		printf("\r");
		sleep(1);
	}
	return 0;
}