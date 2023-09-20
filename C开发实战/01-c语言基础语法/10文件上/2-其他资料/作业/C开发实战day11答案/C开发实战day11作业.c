1、假如有5个学生，按照年龄排序，如果年龄相同，按照成绩排序
struct student
{
	char name[50];//姓名
	unsigned int age;
	int score;//成绩
};


2、利用sleep函数(Linux平台)结合结构体，编写一个模拟时钟
	struct Time
	{//表示时间的数据类型
		int hour;
		int minute;
		int second;
	};
	
	提示：
	1)#include <unistd.h>
	  sleep(1);  //以秒为单位
	  
	2) fflush(stdout); //人为刷新打印缓冲区
	   "\r"，转义字符，跳到句首打印
