#include<stdio.h>

int main()
{
	int num = 0;
	printf("输入1到7之间的数字: ");
	scanf("%d",&num);
	
	switch(num)
	{
		case 1:
			printf("Today is Monday\n");
			break;
		case 2:
			printf("Today is Tuesday\n");
			break;
		case 3:
			printf("Today is Wednesday\n");
			break;
		case 4:
			printf("Today is Thursday\n");
			break;
		case 5:
			printf("Today is Friday\n");
			break;
		case 6:
			printf("Today is Saturday\n");
			break;
		case 7:
			printf("Today is Sunday\n");
			break;
		default :
			printf("error\n");
			break;
	}
		
	return 0;
}