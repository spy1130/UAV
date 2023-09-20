#include <stdio.h>
#include <stdlib.h>
int main(int argc, char const *argv[])
{
	int sum = 0;
	for (int i = 1; i < 100; ++i)
	{
		if(i%2==0)//偶数
		{
			sum += i;
		}
		else//奇数
		{
			sum -= i;
		}
	}
	printf("sum = %d\n", sum);
	system("pause");
	return 0;
}