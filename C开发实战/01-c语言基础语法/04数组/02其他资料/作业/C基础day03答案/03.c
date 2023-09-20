#include <stdio.h>
int main()
{
	int num = 0;
	int i;
	
	printf("1-100能被7整除的数值为：\n");
	while( num <= 100 )
	{
		if( num % 7 == 0 )
		{
			printf("%d ",num);
		}
		num++;
	}
	printf("\n");
	
	for(i = 0; i <= 100; i++)
	{
		if( i % 7 == 0 )
		{
			printf("%d ",i);
		}
			
	}
	printf("\n");

	return 0;
}