//# Ԥ����ָ���Ԥ����ʱ����
//#include <stdio.h> ����stdio.h�ļ�  stdio.h�����ڲ˵�
// ����б����ע��
//�����루����ʹ��������һ������ 
//main() main����Ҳ�������� ���������н���ֻ��һ��main�����������main����
//��ʼִ��
//int  ����main��������֮��ķ���ֵ����
//return  �������������Ȼ�󷵻�ֵ������ֵ�����ͺͺ�������ʱ����ֵ����һ��
//{}������Ǻ����壬������Ҫִ�еĴ������д��{}��
//ÿһ����������Էֺţ���β
//printf��һ���⺯����printf+�������Ǻ�������
#define _CRT_SECURE_NO_WARNINGS     //����궨�����Ҫ�ŵ�.c�ļ��ĵ�һ��
#include <stdio.h>
#include <stdlib.h>
int main01()
{
	//syetem������������������ϵͳ�����ҵ������ü�·����
	//������������Ҳ�������Ҫ��·��
	//windows·����\\  �� /
	//system("mspaint");//������ͼ��
	//system("C:\\Users\\Administrator\\Desktop\\c++13\\hello.exe");
	system("C:/Users/Administrator/Desktop/c++13/hello.exe");
	printf("hello worldfbahfoahfoooooooooooooooooooooo\n");//��ӡ���ն�
	system("pause");//pause����������ǵȴ��û��������ⰴ��
	return 0;
}


int main02()
{
	//�������ͱ���a, b, c
	int a = 3;
	int  b = 4;
	int c = 0;
	//����ʱ���öϵ㣬�ϵ����������ʹ�����������ϵ�ʱֹͣ��ʹ�������Ϊ����
	c = a + b;

	printf("%d\n", c);//��c��ֵ���

	return 0;//�ɹ����
}



int main03()
{
	char  buf[1024] = "";
	sprintf(buf,"abc");
	printf("buf=%s\n",buf);
	system("pause");
	return 0;
}


