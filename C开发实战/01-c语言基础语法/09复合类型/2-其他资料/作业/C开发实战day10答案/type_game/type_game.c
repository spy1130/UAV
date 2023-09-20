//简单的字母输入测试程式
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "mygetch.h"

#define MAX  51 //定义测试字母的最大长度

void help()
{
	printf("\n*******************************************");
	printf("\n* 输入过程中无法退出，输入出错则以 _ 表示!*");
	printf("\n* 按任意键开始测试，按下首字母时开始计时! *");
	printf("\n*******************************************\n\n");
}

void start(char *str)
{
	srand((unsigned int)time(NULL));//随机种子
	int i = 0;
	
	for(i = 0; i < MAX-1; i++)//打印50个英文字符用于测试
	{
		str[i] = rand() % 26 + 'a';
	}
	
	*(str + MAX-1) = '\0';//写完字符后补上结束标志位
}

void on_game(char *str)
{

	char ch;
	int i = 0;
	int count = 0;
	time_t t_start,t_end;
	
	system("cls");	//先清屏
	printf("\n%s\n",str);

	count = 0;
	for(i = 0; i < MAX-1; i++)
	{
		ch = _getch();
		if(i == 0)
		{
			t_start = time(NULL);//取开始时间
		}
		if(ch == *(str+i))
		{
			printf("%c",ch);
			count++;
		}
		else
		{
			printf("_");//打印出错标志
		}
	}
	
	t_end = time(NULL);//取结束时间
	
	printf("\n完成输入!\n用时 %ld s\n", t_end - t_start);
	printf("正确率%lf  %%\n", (count*1.0 / (MAX - 1)) * 100);
	printf("按下Esc退出，任意键继续!\n\n");
}

int main()
{
	char str[MAX] = {0};

	while(1)
	{
		help(); //游戏说明菜单
		
		start(str); //产生随机字母
	
		_getch();//等待用户输入任意按键
		
		on_game(str); //开始游戏
		
		char ch = _getch();//等待用户输入任意按键
			
		if(ch == 27)//Esc的ascii为27
		{
			break;
		}
		
		system("cls");	//先清屏
	}
	
	return 0;
}