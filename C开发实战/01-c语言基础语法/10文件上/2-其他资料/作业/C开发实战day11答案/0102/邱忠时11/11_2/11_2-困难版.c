#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


void run(int year, int mon, int day, int hour, int min, int sec);
int findweek(int year, int mon, int day);

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


int main()   //完美实现了时钟
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

		char *p[5];
		p[0] = strtok(buf, " ");

		for (int i = 1;i < 5;i++)
		{
			p[i] = strtok(NULL, " ");
		}

		//p[4]就是小时:分钟:秒 
		sscanf(p[0], "%d", &tme.year);  //获取年
		sscanf(p[1], "%d", &tme.mon);	  //获取月
		sscanf(p[2], "%d", &tme.day);	  //获取日


		sscanf(p[4], "%02d:%02d:%02d", &tme.hour, &tme.minute, &tme.second);
		//按照格式读取并赋值给结构体成员	


		run(tme.year, tme.mon, tme.day, tme.hour, tme.minute, tme.second);
	}
	return 0;
}



int findweek(int year, int mon, int day)
{
	short a[12] = { 6,2,2,5,0,3,5,1,4,6,2,4 };//非闰年月份代码
	short b[12] = { 5,1,2,5,0,3,5,1,4,6,2,4 };//闰年月份代码

	short c[2] = { year % 10,((year / 10) % 10) * 10 };
	int y_num = c[0] + c[1];   //取年份后两位数

	int d = (y_num / 4 + y_num) % 7;  //算出年份代码

	int week;

	if ((((year % 4) == 0) && (year % 100) != 0) || (year % 400) == 0)  //判断是否是润年
		week = (day + b[mon - 1] + d) % 7;   //求出星期几，0～6
	else
		week = (day + a[mon - 1] + d) % 7;
	return week;
}

void run(int year, int mon, int day, int hour, int min, int sec)
{
	int sign = 0;
	int week = 0;
	int mona[12] = { 31,29,31,30,31,30,31,31,30,31,30,31 };  //闰年
	int monb[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 }; //非闰年

	if ((((year % 4) == 0) && (year % 100) != 0) || (year % 400) == 0)  //判断是否是润年
		sign = mona[mon - 1];
	else
		sign = monb[mon - 1];

	for (; year < 2999; year++)
	{
		for (; mon < 12; mon++)
		{
			if ((((year % 4) == 0) && (year % 100) != 0) || (year % 400) == 0)  //判断是否是润年
				sign = mona[mon - 1];
			else
				sign = monb[mon - 1];

			for (; day < sign; day++)
			{
				week = findweek(year, mon, day);
				for (; hour < 24; hour++)
				{
					for (;min < 60; min++)
					{
						for (; sec < 60; sec++)
						{
							switch (week)
							{
							case 1:
								printf("%d年 %d月 %d日 星期一 %02d:%02d:%02d", year,mon, day, hour, min,sec);
								break;
							case 2:
								printf("%d年%d月%d日 星期二 %02d:%02d:%02d", year,mon, day, hour, min,sec);
								break;
							case 3:
								printf("%d年%d月%d日 星期三 %02d:%02d:%02d", year,mon, day, hour, min,sec);
								break;
							case 4:
								printf("%d年%d月%d日 星期四 %02d:%02d:%02d", year,mon, day, hour, min,sec);
								break;
							case 5:
								printf("%d年%d月%d日 星期五 %02d:%02d:%02d", year,mon, day, hour, min,sec);
								break;
							case 6:
								printf("%d年%d月%d日 星期六 %02d:%02d:%02d", year,mon, day, hour, min,sec);
								break;
							case 0:
								printf("%d年%d月%d日 星期天 %02d:%02d:%02d", year,mon, day, hour, min,sec);
								break;
							default:
								break;
							}
							fflush(stdout);
							printf("\r");
							sleep(1);
						}

						sec = 0;
					}
					min = 0;
				}
				hour = 0;
			}
			day = 1;
		}
		mon = 1;
	}
}