#include "total.h"


int main(void)
{
	int n,sign;   //n 为多少位学生，sign为选择排序方式
	std *p[MAX];

	printf("请输入多少位学生：");
	scanf("%d", &n);

	if (n < 1 || n > MAX)   //防止超过最大人数
		exit(0);
	
	g[0](p, n);  //申请空间
	g[1](p, n);  //赋值
	
	
	printf("1.(英文)姓名升序  2.学生年龄升序  3.学生成绩降序\n");
	printf("你想按照哪种方式排序：");
	scanf("%d", &sign);

	switch (sign) 
	{
		case 1:
			g[2](p, n); //英文姓名排序
			break;
		case 2:
			g[3](p, n);  //年龄排序
			break;
		case 3:
			g[4](p, n);  //成绩排序
			break;
	}		

	//g[5](p,n); //汉字拼音排序  实现不了
	//g[6](p,n);  //汉字笔画排序 实现不了
	
	return 0;

}

