1�������ַ����谴�س���
	a)�����Linuxƽ̨������mygetch.h��mygetch.c����д����Ŀ¼��
	#include "mygetch.h"
	char ch = mygetch(); //mygetch()��mygetch.c�ڲ�ʵ�֣����Ǳ�׼����
	
	b)�����Windowsƽ̨��WINAPI�Դ����ƹ��ܺ���
	char ch = _getch(); //��Ҫͷ�ļ�#include <conio.h>
	
	
2����������
	system("clear"); //Linuxƽ̨
	system("cls");   //Windowsƽ̨
	

3���������غ���
	//����ͷ�ļ���
	#include <stdlib.h> //srand(), rand()
	#include <time.h> //time()

	srand((unsigned int)time(NULL)); //�������
	rand();	//�����
	
	�ܹ���26����ĸ����β���26�������ĸ��
	
	
4�������ʱ
	��ȡ��ǰϵͳʱ�䣺
	time_t start_time = time(NULL); //��Ҫͷ�ļ�#include <time.h>
	
	
5��Ҫ���ʵ���װ��������Ҫ���д��붼д��main()������

	