#include <stdio.h>
#include <stdlib.h>
int main(int argc, char const *argv[])
{
	int m = 0, n=0;
	printf("«Î ‰»Îm”În÷Æ\n");
	scanf("%d %d", &m, &n);

	int sum = 0;
	for (int i = m; i <= n; ++i)
	{
		if((i%7!=0) && (i%5!=0))
		{
			sum += i;
		}
	}
	printf("sum = %d\n", sum);
	system("pause");
	return 0;
}