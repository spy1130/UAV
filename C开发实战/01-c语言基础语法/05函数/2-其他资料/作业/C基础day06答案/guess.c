#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

int main()
{
	int rand_num[4];  //随机数
	int guess_num[4]; //保存输入数字的每一位
	int num; //输入的数字
	int n = 0;
	int i = 0;

	printf("猜数字：系统会随机产生一个四位数字。\n");
	
	// 以当前时间为准，设置随机种子
	srand( (unsigned int )time(NULL) );

	// 产生四个0-9之间的数字，不是产生一个四位数
	// 每一个数字放在数组中
	for( i = 0; i < 4; i++ )
	{
		rand_num[i] = rand()%10;
	}
	
	while(1)
	{
		printf("\n请输入一个4位数字：");
		scanf("%d", &num);
		
		//把输入的4位数字的每个数字都放在guess_num数组中
		guess_num[0] = (num/1000) % 10;
		guess_num[1] = (num/100) % 10;
		guess_num[2] = (num/10) % 10;
		guess_num[3] = num % 10;
		
		n = 0;
		for(i = 0; i < 4; i++)
		{
			if(guess_num[i] > rand_num[i])
			{
				printf("第%d位大于正确数字。\n", i+1);
			}
			else if(guess_num[i] < rand_num[i])
			{
				printf("第%d位小于正确数字。\n", i+1);
			}
			else
			{
				printf("第%d位正确。\n", i+1);
				n++;
			}
		}
		
		if(4 == n)
		{
			printf("恭喜你，猜对了!!!\n");
			sleep(2);
			return 0; //结束程序
		}
		
	}
		
	return 0;
}