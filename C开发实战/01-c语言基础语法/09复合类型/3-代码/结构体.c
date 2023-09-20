#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//定义一个结构体数据类型

//关键字 struct 代表这个是一个结构体类型,
//stu   是这个结构的名字
//整个结构体的类型是   struct  stu
// 结构体类型struct  stu   {}中是结构体的成员,一个有3个成员,每个成员的类型可以是
//任意的类型
//定义结构体类型时,{}后面记得加分号
//注意定义结构struct  stu,它只是一个类型,一个模板,没有空间,不可以给结构体成员赋值
struct  stu
{
	int id ;
	int age;
	char name[128];
} ;//定义类型时,同时定义了两个结构体变量struct  stu a;

struct heima_stu
{
	/*int id;
	int age;
	char name[128];*/
	struct  stu s;
	char subject[128];
};



int main09()
{
	struct  stu a;
	//struct  stu  *p =&a;//p是一个野指针
	struct  stu  *p = malloc(sizeof(struct stu));
	p->id = 100;
	p->age = 30;
	strcpy(p->name,"ubunqu");
	printf("%d %d %s\n",p->id,p->age,p->name);


	system("pause");
	return 0;
}


void memcpy_str(struct  stu  *x, struct  stu  *y)
{
	memcpy(x,y,sizeof(x));

}
int main08()
{
	struct  stu a = {1,34,"bob"};
	struct  stu b;

	//1 memcpy
	//memcpy_str( &b,&a);
	//2
	//b.id = a.id;
	//b.age = a.age;
	////b.name = a.name;//err
	//strcpy(b.name,a.name);

	//3 
	b = a;//ok   相同类型的变量是可以相互赋值
	printf("%d %d %s\n",b.id,b.age,b.name);



	system("pause");
	return 0;
}


int main07()
{
	struct heima_stu heima;
	heima.s.id = 1;
	heima.s.age = 22;
	strcpy(heima.s.name,"ubunqu");
	strcpy(heima.subject,"c++");

	printf("%d %d %s %s\n",heima.s.id,heima.s.age,heima.s.name,heima.subject);

	system("pause");
	return 0;
}


int main06()
{
	//定义一个结构体数组,结构体数组有5个元素,每个元素是struct  stu 类型
	struct  stu num[5] = { {1,20,"lucy"},{2,21,"bob"},{3,22,"peter"},
							{4,25,"maker"},{5,26,"ubunqu"} };

	for(int i=0;i<sizeof(num)/sizeof(num[0]);i++)
	{
		printf("%d %d %s\n",num[i].id,num[i].age,num[i].name);
	}


	system("pause");
	return 0;
}

int main05()
{
	//struct  stu d = {1,20,"ubunqu"};
	//struct  stu d = { .age=20 };//给部分成员初始化,其他成员内容为0
	struct  stu d;
	//如何给结构体成员赋值(如何操作结构体成员)
	//如果通过结构体变量操作结构体成员,使用点域.操作
	/*d.id = 2;
	d.age = 20;
	strcpy(d.name , "world");
	printf("%d %d %s\n",d.id,d.age,d.name);*/

	//如果通过结构体的地址操作结构体成员,使用->
	(&d)->id = 3;
	(&d)->age = 20;
	strcpy((&d)->name, "world");
	printf("%d %d %s\n", (&d)->id,(&d)->age,(&d)->name);
	system("pause");
	return 0;
}
