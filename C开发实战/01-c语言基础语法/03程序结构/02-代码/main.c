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


int main19()
{
	printf("�Ұ���\n");
	printf("�Ұ���\n");
	printf("�Ұ���\n");
	printf("�Ұ���\n");

	system("pause");
	return 0;
}

//switch
int main18()
{
	int num = 0;
	int a = 0;
	scanf("%d", &num);
	a = num % 4;//0 1  2  3
	switch (a)//()������ж�����ֻ��������
	{
		case 0:
			printf("0\n");
			printf("hello\n");
			break;//����switch���
		case 1:
			printf("1\n");
			break;//����switch���
		case 2:
			printf("2\n");
			break;//����switch���
		default://Ĭ��
			printf("3\n");
			break;//����switch���
	}

	system("pause");
	return 0;
}

//��Ŀ�����
int main17()
{
	int  a = 10;
	int b = 20;
	int c = 0;
	//��a��b�����ֵ��c
	//if (a > b)
	//{
	//	c = a;
	//}
	////else
	//{
	//	c = b;
	//}
	c = a > b ? a : b;
	printf("c=%d\n",c);

	system("pause");
	return 0;
}


int main16()
{
	//�������ж��ֵ��ǲ�ȷ������һ��,����ÿ���ṹ�ǻ����
	int num = 0;
	int a = 0;
	scanf("%d",&num);
	a = num % 4;//0 1  2  3
	if (0 == a)
	{
		printf("�� 0\n");
	}
	 else if (1 == a)
	{
		printf("�� 1\n");
	}
	else if( 2 == a)
	{
		printf("�� 2\n");
	}
	else if(3 == a)
	{
		printf("�� 3\n");
	}


	system("pause");
	return 0;
}


int main15()
{
	int a = 1;
	int b = 2;
	if (a > b)
	{
		printf("a>b\n");
	}
	else
	{
		printf("a<=b\n");
	}
		


	system("pause");
	return 0;
}

int main14()
{
	int  a = 2;
	int b = 3;
	//if���治Ҫ�� �ֺ�,�ֺ��ǿ����
	//һ��if�������{},{}�������䶼����if
	//���if���治��{},ֻ��if�����һ���������if
	/*if (a == b);
	{
		printf("a==b\n");
	}*/
	if (a != 3)//��ó���д���
	{
		printf("a==b\n");
		printf("bbbbb\n");
	}
	printf("aaaaaa\n");

	system("pause");
	return 0;
}


int main13()
{
	int  a = 3;
	double b = (double)a;//��ʽת��
	//���͵�ת��  ����Ҫ�����ͺ͸������Ͳ�ƥ��,��Ҫת��
	//ǿ��ת��  (��Ҫת������)ԭ������������
	printf("%d\n",(int)3.14);
	printf("%lf\n",(double)a);


	system("pause");
	return 0;
}

int main12()
{
	int a = 1;
	int b = 2;
	//���������,���յĽ�������һ�����ʽ�Ľ��
	int c = (a++,b++,a+b,10,200,a+b,1000);
	printf("%d\n",c);

	system("pause");
	return 0;
}


int main11()
{
	int a = 1;
	int b = 2;
	int c = 0;
	//c += a *= 10;//a=a*10  c=c+a
	//printf("c=%d\n",c);
	printf("%d\n",c+++b);//c+b, c=c+1 

	system("pause");
	return 0;
}

int main10()
{
	int a = 0;
	int b = 1;
	int c = 0;
	printf("%d\n",a || b);
	printf("%d\n", a || c);
	printf("%d\n", b || a++);
	printf("a=%d b=%d\n",a,b);
	system("pause");
	return 0;
}

int main09()
{
	//��0 Ϊ��
	int  a = 0;
	int b = 1;
	/*printf("%d\n",!a);
	printf("%d\n", !0);
	printf("%d\n", !-1);*/
	//�߼�&&  A && B   ����A��B��Ϊ��,�������ʽ��Ϊ��
	//���A ���ʽΪ��,B���ʽ��ִ��
	printf("%d\n",a && b++);
	printf("a=%d b=%d\n",a,b);


	system("pause");
	return 0;
}


int main08()
{
	printf("%d\n",3==4);
	printf("%d\n", 3 != 4);
	printf("%d\n", 3 > 4);
	printf("%d\n", 3 < 4);
	printf("%d\n", 3 <= 4);
	system("pause");
	return 0;
}

//��ֵ����
int main07()
{
	int  a = 1;
	//a = a + 2;  a +=2;
	//a += 2;
	//a -= 5;//a= a-5;
	//a *= 5;//a =a*5
	printf("%d\n",a);

	system("pause");
	return 0;
}


int main06()
{
	// �Լ� �Լ�
	//a = a + 1;// a++  ++a
	int  a = 1;
	int b = 0;
	int c = 2;
	//���a++  ��++a����ʹ��,Ч����ͬ ����a = a+1
	//a++;//a=a+1
	//++a;//a=a+1;
	//b = a++;//  ++�ں�,��ʹ��,���Լ� b=a, a=a+1
	b = ++a;//++��ǰ  ���Լ�,��ʹ��a=a+1, b=a
	printf("b=%d a=%d\n",b, a);
	//printf("c= %d\n",c++);//�ȴ�ӡ(ʹ��),���Լ�
	printf("c= %d\n", ++c);//���Լ�,��ʹ��
	printf("c= %d\n", c);
	system("pause");
	return 0;
}


int main05()
{
	int  num = 8981234;
	int  a = num % 10;//��λ
	int b = num / 10 % 10;//ʮλ
	int c = num / 100 % 10;//��λ
	int d = num / 1000 % 10;//ǧλ
	printf("%d %d %d %d\n",d,c,b,a);
	system("pause");
	return 0;
}


int main04()
{
	int  a = 2;
	int b = 3;
	int c = b%a;//
	printf("%d\n",c);

	system("pause");
	return 0;
}

int main03()
{
	int a = 10;
	int b = 20;
	int c = a + b;
	int d = a - b;
	int e = a *b;
	printf("%d %d %d\n",c,d,e);
	//�������,���Ҫ�õ�С��,������һ����double���ͻ�float����
	//double f = a*1.0 / b;//0.5
	//int f = b / a;
	//int f = a / 0;err ��������Ϊ0

	//printf("%lf\n",f);

	system("pause");
	return 0;
}

int main02()
{
	short a = 0xfffe;//65535  255
	//����:  1111 1111 1111 1110
	//����: 1000 0000 0000 0001
	//ԭ��:1000 0000 0000 0010
	printf("%hd\n", a); //������Ϊ_____
	printf("%hu\n", a);//1111 1111 1111 1110

	system("pause");
	return 0;
}

int main01()
{
	//������λΪ1,��ǰ��չ1,������λ��0,��ǰ��չ0
	//1111 1111 1111 1111 1111 1111  0000 0001
	//char num = 0x81;
	//8λ����: 1000 0001 ->8λ��ԭ�� -> 32λԭ��->   32λ����  -> 32ԭ��
	//8λ��ԭ��: 1111 1111
	//32λԭ��: 1000 0000 0000 0000 0000 0000 0111 1111 = -127
	//32λ�Ĳ���: 1111 1111 1111 1111 1111 1111 1000 0001 = ffffff81
	//printf("%d\n",num);//-127
	char num = 0x12;//1000 0010-> 1111 1111 1111 1111 1111 1111 1000 0010
	//0001 0010 -> 0000 0000 0000 0000 0000 0000 0001 0010
	printf("%x\n",num);//4294967169
	system("pause");
	return 0;
}
