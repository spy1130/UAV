#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct  t
{
	int  a;
};
struct tea {

	int  id;
	char *p;
	struct t  *b;
};
int main12()
{
	struct tea  *tmp =(struct tea  *) malloc(sizeof(struct tea));
	tmp->id = 100;
	tmp->p = (char *)malloc(100);
	strcpy(tmp->p,"hello");
	//tmp->b->a = 200; err b是野指针, 不能直接赋值b所指向的空间
	tmp->b = (struct  t *)malloc(sizeof(struct  t));
	tmp->b->a = 1000;

	free(tmp->p);
	free(tmp->b);
	free(tmp);


	system("pause");
	return 0;
}




int main10()
{
	char  *p;
	//p = "hello";
	p = (char *)malloc(128);
	strcpy(p,"hello");//将hello的内容拷贝带p所指向的空间
	printf("%s\n",p);


	system("pause");
	return 0;
}

int main09333()
{


	struct tea  *tmp = (struct tea  *)malloc(sizeof(struct tea));
	tmp->id = 100;
	tmp->p = (char *)malloc(128);
//	tmp->p = "hello";//ok
	strcpy(tmp->p,"hello");
	printf("%s\n",tmp->p);


	system("pause");
	return 0;
}
