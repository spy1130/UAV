#include <stdio.h>
#include <stdlib.h>
int main(int argc, char const *argv[])
{
	int x = 0,y = 0,c=0;
	printf("请输入两个数\n");

	scanf("%d %d", &x,&y);

	while(c=x%y)
	{
		x = y;
		y = c;
	}
	printf("最大公约数为%d\n", y);
	system("pause");
	return 0;
}