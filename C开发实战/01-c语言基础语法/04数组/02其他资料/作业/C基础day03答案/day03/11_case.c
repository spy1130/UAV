#include <stdio.h>
#include <stdlib.h>
int main(int argc, char const *argv[])
{
	
	int i = 0;
	while(1)
	{
		if((i%2==1) && (i%3==2) &&(i%5==4) && (i%6==5) && (i%7==0))
		{
			break;
		}
		i++;
	}

	printf("Ì¨½×ÊýÎª%d\n", i);
	system("pause");
	return 0;
}