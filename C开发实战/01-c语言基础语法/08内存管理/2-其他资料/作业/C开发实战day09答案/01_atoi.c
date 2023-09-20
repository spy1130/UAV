#include <stdio.h>

int my_atoi(char * str)
{
	char *tmp = str;
	int flag = 0;//0代表正数，1代表负数
	
	while( *tmp == ' ' || *tmp == '\r' || *tmp == '\n' || *tmp == '\t')
	{
		tmp++;
	}
	
    if (*tmp == '-')
    {
        flag = 1;
        tmp = tmp + 1;//会从第二个字符开始转化
    }
    else if (*tmp == '+')
    {
        tmp = tmp + 1;
    }
	
	int num = 0;
	while (*tmp != '\0')
	{
		num = num * 10 + (*tmp - '0');
		
		tmp++;
	}
	
	if(0 == flag)
	{
		return num;
	}
	else
	{
		return -num;
	}
}

int main()
{
	printf("num1 = %d\n", my_atoi("+123"));
	printf("num2 = %d\n", my_atoi("-123"));
	printf("num3 = %d\n", my_atoi("123"));
	
	return 0;
}