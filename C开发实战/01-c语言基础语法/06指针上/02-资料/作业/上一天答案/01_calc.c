#include <stdio.h>
#include <string.h>

int add(int a, int b)
{
	return a+b;
}

int sub(int a, int b)
{
	return a-b;
}

int mux(int a, int b)
{
	return a*b;
}

int dive(int a, int b)
{
	return a/b;
}

int main()
{
	char cmd[5] = {0};
	char  str[]="add";
	int a = 0;
	int b = 0;
	int i = 0;
	
	while(1)
	{
		printf("please inpt cmd：");
		scanf("%s %d %d", cmd, &a, &b);
		
		if(0 == strcmp(cmd, "add") )
		{
			printf("result = %d\n", add(a, b));
		}
		else if(0 == strcmp(cmd, "sub") )
		{
			printf("result = %d\n", sub(a, b));
		}
		else if(0 == strcmp(cmd, "mux") )
		{
			printf("result = %d\n", mux(a, b));
		}
		else if(0 == strcmp(cmd, "dive") )
		{
			printf("result = %d\n", dive(a, b));
		}
		else if(0 == strcmp(cmd, "exit"))
		{
			exit(0);
			
		}
	}
	
	return 0;
}