#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct  c13
{
	int  id;
	char name[128];
};



int main19()
{
	struct  c13 a;
	struct  c13 b;
	// struct  c13  const *p = &a;
	//p->id = 100; err  const修饰的是*,不能通过指针p取修改p指向的那块空间

	struct  c13   * const p = &a;
	//p = &b;  const修饰的是指针变量p,不能修改p本身的内容(指向)
	system("pause");
	return 0;
}



//void set_num(struct  c13 num[5] )
void set_num(struct  c13 *p,int n )
{

	for (int i = 0; i < n; i++)
	{
	//	(*(p + i)).id = i + 10;
		p[i].id = i + 10;
		//(p + i)->id = i + 10;
		char buf[128] = "";
		sprintf(buf,"%d%d%d",i,i,i);
		strcpy(p[i].name,buf);
	}

}
int main14()
{
	struct  c13 num[5];
	memset(num,0,sizeof(num));
	set_num(num,sizeof(num)/sizeof(num[0]));// num  = &num[0]  
	for (int i = 0; i < sizeof(num) / sizeof(num[0]); i++)
	{
		printf("%d %s\n",num[i].id,num[i].name);
	
	}

	system("pause");
	return 0;
}
