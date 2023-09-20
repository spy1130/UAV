#include <stdio.h>

int main()
{
	char ch = '!';
	int score = 0;
	printf("请输入学生分数:");
	scanf("%d",&score);
	
	if(score<0 || score >100)
	{
		printf("你所输入的信息有错\n");
	}
	else if( score<60)
	{
		ch = 'E';
	}
	else if ( score < 70 )
	{
		ch = 'D';
	}
	else if ( score < 80 )
	{
		ch = 'C';
	}
	else if ( score < 90 )
	{
		ch = 'B';
	}
	else
	{
		ch = 'A';
	}
	
	printf("成绩评定为：%c\n",ch);
	
	return 0;
}