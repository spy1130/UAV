#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void start_game(void);
void game_cmd(void)
{
	printf("按1 进入游戏\n");
	printf("按2 查看游戏规则\n");
	printf("按0 退出游戏\n");
}
void game_rule(void)
{
	printf("猜数字:系统会随机产生一个四位数，在不同难度\n");
	printf("下你有相应的次数去猜测这个数字。系统会给提示\n");
	printf("信息，在规定次数内猜对即获胜。\n");

	int cmd=0;
	printf("按1 进入游戏\n");
	printf("按0 退出游戏\n");
	scanf("%d", &cmd);
	getchar();

	switch(cmd)
	{
		case 1:
			start_game();
			break;
		case 0:
			exit(-1);
	}
}
void start_game(void)
{
	//四位随机数
	int dst[4] = {0};
	int lev[3] = {10,7,5};
	for (int i = 0; i < sizeof(dst)/sizeof(dst[0]); ++i)
	{
		dst[i] = rand()%10;//获取一位数 123%10==3
	}

	printf("请选择游戏难度级别：1(10次)、2(7次)、3(5次)\n");
	int level = 0;
	scanf("%d", &level);
	getchar();

	printf("Lev.%d\n", level);
	printf("开始游戏，请输入数值:\n");

	
	for (int i = 0; i < lev[level-1]; ++i)
	{
		int flag = 0;
		int data = 0;
		scanf("%d", &data);
		getchar();

		//提取输入数据的每个位
		int src[4] = {0};
		for (int j = sizeof(src)/sizeof(src[0]) -1; j >= 0 ; --j)
		{
			src[j] = data%10;
			data = data/10;
		}

		//src与dst逐位比较
		for (int j=0; j < sizeof(src)/sizeof(src[0]); ++j)
		{
			if(src[j] == dst[j])
			{
				printf("第%d位相等\n", j+1);
				flag ++;
			}
			else if(src[j] < dst[j])
			{
				printf("第%d位小于正确数\n", j+1);
			}
			else if(src[j] > dst[j])
			{
				printf("第%d位大于正确数\n", j+1);
			}

		}

		if(flag == 4)//正确
		{
			printf("你输入正确，任意键退出\n");
			getchar();
			exit(-1);
		}
		if(i+1<lev[level-1])
			printf("再次输入数据\n");

	}


	printf("失败了\n");
	return;

}
int main(int argc, char const *argv[])
{

	//设置随机数种子
	srand(time(NULL));
	while(1)
	{
		game_cmd();
		int cmd = 0;
		scanf("%d",&cmd);
		getchar();//去掉回车

		switch(cmd)
		{
			case 0:
				return 0;
			case 1:
				//进入游戏
				start_game();
				break;
			case 2:
				game_rule();
				break;
		}
	}
	
	return 0;
}