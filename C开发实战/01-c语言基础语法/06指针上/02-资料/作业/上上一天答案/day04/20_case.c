#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char const *argv[])
{
	char buf[64] = "";
	printf("������һ��С��64�ֽڵ��ַ���\n");
	fgets(buf, sizeof(buf), stdin);

	int len = strlen(buf);
	for (int i = 0; i < len; ++i)
	{
		if(buf[i]>='a' && buf[i]<='z')
		{
			buf[i] -= 32;
		}
		else if(buf[i]>='A' && buf[i]<='Z')
		{
			buf[i] += 32;
		}

		printf("%c", buf[i]);
	}
	printf("\n");

	return 0;
}