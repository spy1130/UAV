1��������5��ѧ�������������������������ͬ�����ճɼ�����
struct student
{
	char name[50];//����
	unsigned int age;
	int score;//�ɼ�
};


2������sleep����(Linuxƽ̨)��Ͻṹ�壬��дһ��ģ��ʱ��
	struct Time
	{//��ʾʱ�����������
		int hour;
		int minute;
		int second;
	};
	
	��ʾ��
	1)#include <unistd.h>
	  sleep(1);  //����Ϊ��λ
	  
	2) fflush(stdout); //��Ϊˢ�´�ӡ������
	   "\r"��ת���ַ����������״�ӡ
