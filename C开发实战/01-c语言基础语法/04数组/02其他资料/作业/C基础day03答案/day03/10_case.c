#include <stdio.h>
#include <stdlib.h>
int main(int argc, char const *argv[])
{
	int x = 0,y = 0,c=0;
	printf("������������\n");

	scanf("%d %d", &x,&y);

	while(c=x%y)
	{
		x = y;
		y = c;
	}
	printf("���Լ��Ϊ%d\n", y);
	system("pause");
	return 0;
}