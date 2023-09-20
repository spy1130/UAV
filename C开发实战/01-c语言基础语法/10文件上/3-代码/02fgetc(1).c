#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>


int main03()
{
	FILE *fp = fopen("./a.txt","r");
	if(NULL == fp)
	{
		perror("");
		return -1 ;
	}
	/*char ch = fgetc(fp);
	printf("%c\n",ch);*/
	char buf[128] = "";
	int i = 0;
	//while ((buf[i++] = fgetc(fp)) != EOF);
	//{
		
		//buf[i] = fgetc(fp);
		//i++;
	//}
	//int a;
	do {
		buf[i] = fgetc(fp);
		i++;
		//a = feof(fp);
	} while (   !  feof(fp)   );

	printf("%s\n",buf);
	system("pause");
	return 0;
}
