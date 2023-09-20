/*猜字游戏(在Linux平台下编写)：
	1)随机函数（产生四个0-9之间的数字，不是产生一个四位数）
	A.srand( (unsigned)time(NULL) ); 以当前时间为准，设置随机种子
	  注意：此函数，在每次开始游戏后调用一次即可
	B.rand();
	  注意：rand()函数，每调用一次，产生一个随机数字
	
	以上所需头文件：*/
	#include <stdlib.h> //srand(),  rand()
	#include <time.h>   //time()
	int main(){
		srand( (unsigned)time(NULL) ); 
		int answer =rand()%10;
		int gus=0;
		do{
			printf("请输入你猜的数：");
			scanf("%d",&gus);
			if(answer>gus){
			printf("小了小了");
			}else if (answer<gus)
			{
				printf("大了大了");
			}else{
				printf("恭喜你答对了");
				break;
			}			
		}while(gus>=0 && gus<=9);
		return 0;
	}
