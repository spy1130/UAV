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




int main()
{
	int  num = 0x01020304;
	char  *p1 = (char *)&num;//int *
	short *p2 = (short *)&num;
	int *p3 = &num;
	//ͨ��*ȡָ�������ָ���ǿ�ռ�����ʱ,ȡ���ڴ�Ŀ�Ⱥ�ָ���������������й�

	/*printf("%x\n",*p1);
	printf("%x\n", *p2);
	printf("%x\n", *p3);*/
	printf("%u\n",p1);
	printf("%u\n", p2);
	printf("%u\n", p3);

	printf("%u\n", p1+1);
	printf("%u\n", p2+1);
	printf("%u\n", p3+1);
	system("pause");
	return 0;
}


int main02()
{
	char  *p1;
	short *p2;
	int *p3;
	int **p4;//p4Ҳ��һ��ָ�����  int **

	printf("%d\n",sizeof(p1));
	printf("%d\n", sizeof(p2));
	printf("%d\n", sizeof(p3));
	printf("%d\n", sizeof(p4));
	system("pause");
	return 0;
}

int main01()
{
	// ��ʹ��ʱ,��һ�����ʽȡ*,�ͻ�Ա��ʽ��һ��*,����Ա��ʽȡ&,�ͻ��һ��*
	int  a = 10;
	//����ָ���������
	//1  *����Ž�ϴ�����һ��ָ�����  2 Ҫ����˭�ĵ�ַ,�����Ķ�����ʽ���ڴ˴�
	//3 ��*p�滻������ı���
	//*p
	int  *p;
	p = &a;
	//����
	//1��*��ϴ������һ��ָ�����
	//2p�Ǳ���,p�������ǽ�����p�����Ϻ�,ʣ�µ����;���ָ�����������  int   *
	//3ָ�����p��������ʲô�������ݵĵ�ַ ,��ָ�����p��ָ�����p�����*һ���Ϻ�,
	//ʣ��ʲô���;ͱ���ʲô�������ݵĵ�ַ
	//p = &a;

	*p = 100;// ��ʹ��ʱ,*��p��ϴ���,ȡpָ����ָ���ǿ�ռ������
	printf("a=%d\n",a);
	int  b = 200;
	p = &b;

	system("pause");
	return 0;
}

