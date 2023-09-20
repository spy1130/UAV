猜字游戏：
	1)随机函数（产生四个0-9之间的数字，不是产生一个四位数）
	A.srand( (unsigned)time(NULL) ); 以当前时间为准，设置随机种子
	  注意：此函数，在每次开始游戏后调用一次即可
	B.rand();
	  注意：rand()函数，每调用一次，产生一个随机数字
	
	以上所需头文件：
	#include <stdlib.h> //srand(),  rand()
	#include <time.h>   //time()
	
	2)比较算法