#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//�в��з���ֵ
int  fun3(int  a, int b)
{
	int c = a + b;
	return c;
	//return  a + b;

}
//���������þ��Ǹ��߱�������������������ط�����
//����������,�Ѻ����Ķ�����ʽ���ڵ���֮ǰ
//û�к�������Ǻ���������,�к�������Ǻ����Ķ���
//������������д������
//��������ʱ��Ҫ�ӷֺ�
//��������������extern Ҳ�ǿ��Ե�
//extern  ��������
//extern void swap(int  a, int  b);
//void swap(int a , int  b);
//void swap(int , int  );
int main()
{
	//exit(0);
	//return 0;
	int  x = 10;
	int  y = 20;
	int  sum = 0;
	//�����з���ֵ����ʱ,���Բ��ӷ���ֵ,Ҳ���Խ�
	//ע��  ���ص����ͺ������շ���ֵ�ı�����������Ҫ��ͬ
	//�����Ĵ���,ֻ���ǵ��򴫵�(ʵ�δ����β�)
	//sum = fun3(x, y);
	//printf("sum=%d\n",fun3(x,y));//���������õķ���ֵ��Ϊ���������Ĳ���
	void swap(int a, int  b);
	swap(x,y);
	printf("x=%d   y=%d\n",x,y);
	system("pause");
	return 0;
}

void swap(int  a, int  b)
{
	exit(0);
	//return;
	int  c = a;
	a = b;
	b = c;
	printf("a=%d  b=%d\n", a, b);
	return;
}