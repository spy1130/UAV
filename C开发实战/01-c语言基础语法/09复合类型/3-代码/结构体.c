#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//����һ���ṹ����������

//�ؼ��� struct ���������һ���ṹ������,
//stu   ������ṹ������
//�����ṹ���������   struct  stu
// �ṹ������struct  stu   {}���ǽṹ��ĳ�Ա,һ����3����Ա,ÿ����Ա�����Ϳ�����
//���������
//����ṹ������ʱ,{}����ǵüӷֺ�
//ע�ⶨ��ṹstruct  stu,��ֻ��һ������,һ��ģ��,û�пռ�,�����Ը��ṹ���Ա��ֵ
struct  stu
{
	int id ;
	int age;
	char name[128];
} ;//��������ʱ,ͬʱ�����������ṹ�����struct  stu a;

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
	//struct  stu  *p =&a;//p��һ��Ұָ��
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
	b = a;//ok   ��ͬ���͵ı����ǿ����໥��ֵ
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
	//����һ���ṹ������,�ṹ��������5��Ԫ��,ÿ��Ԫ����struct  stu ����
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
	//struct  stu d = { .age=20 };//�����ֳ�Ա��ʼ��,������Ա����Ϊ0
	struct  stu d;
	//��θ��ṹ���Ա��ֵ(��β����ṹ���Ա)
	//���ͨ���ṹ����������ṹ���Ա,ʹ�õ���.����
	/*d.id = 2;
	d.age = 20;
	strcpy(d.name , "world");
	printf("%d %d %s\n",d.id,d.age,d.name);*/

	//���ͨ���ṹ��ĵ�ַ�����ṹ���Ա,ʹ��->
	(&d)->id = 3;
	(&d)->age = 20;
	strcpy((&d)->name, "world");
	printf("%d %d %s\n", (&d)->id,(&d)->age,(&d)->name);
	system("pause");
	return 0;
}
