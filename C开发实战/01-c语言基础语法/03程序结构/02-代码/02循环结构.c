#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>


int main27()
{
	int  a = 5;
	if (10< a  && a < 15)
	{
		printf("##############\n");
	}


	system("pause");
	return 0;
}

int main26()
{
	goto End; //��������ת��End�ı�ʶ
	printf("aaaaaaaaa\n");

End:
	printf("bbbbbbbb\n");

	return 0;
}


int main25()
{
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (j == 1)
				break;
			printf("i= %d  j=%d\n",i,j);
		}
		
	}


	system("pause");
	return 0;
}

int main24()
{
	int i = 0;
	for (i = 0; i < 5; i++)
	{
		if (i == 2)
		{ 
			//break;
			continue;
		}
		printf("i=%d\n",i);
	
	}


	system("pause");
	return 0;
}


int main23()
{
	int i = 0;
	int j = 0;
	for (i = 0; i < 2; i++)
	{
		for (j = 0; j < 3; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				printf("i=%d j=%d k=%d\n", i, j,k);
			}
		}
		/*j = 0;
		while (j < 3)
		{
			printf("i=%d j=%d\n", i, j);
			j++;
		}*/
	
	}


	system("pause");
	return 0;
}


int main22()
{
	int  i = 1;
	int sum = 0;
	//for()���治�ܼӷֺ�
	for (  ;  i<=100 ;)//���forѭ����д����,����Ĭ��Ϊ��
	{
		sum += i;
		i++;
	}
	printf("sum=%d\n",sum);
	system("pause");
	return 0;
}

int main21()
{
	// 1 +2+3+4+...+100
	int  i = 1;
	int sum = 0;
	//while()������Ҫ�ӷֺ�
	do {
		sum += i;
		i++;
	
	} while (i<=100);

	printf("%d\n",sum);
	system("pause");
	return 0;
}


int main20()
{
	// 1 +2+3+4+...+100
	int  i = 1;
	int sum = 0;
	//while(����) ����Ϊ���ִ��,Ϊ�ٽ���ѭ��
	//while()���治Ҫ�ӷֺ�
	while (i <= 100)
	{
		sum = sum + i;
		i++;
	
	}
	//while (1);//��ѭ��
	printf("sum =%d\n",sum);
	system("pause");
	return 0;
}
