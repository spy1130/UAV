#include <stdio.h>

typedef struct student
{
	char name[50];//姓名
	unsigned int age;
	int score;//成绩
}student;

void print_stu(student *stu, int n)
{
	int i = 0;
	
	printf("name\tage\tscore\n");
	for(i = 0; i < n; i++)
	{
		printf("%s\t%d\t%d\n", stu[i].name, stu[i].age, stu[i].score);
	};
}

void sort_stu(student *stu, int n)
{
	int i = 0;
	int j = 0;
	student tmp; //临时结构体变量
	
	//冒泡排序，按照年龄排序，如果年龄相同，按照成绩排序
	for(i = 0; i < n-1; i++)
	{
		for(j = 0; j < n-1-i; j++)
		{
			if(stu[j].age > stu[j+1].age) //升序
			{
				tmp = stu[j];
				stu[j] = stu[j+1];
				stu[j+1] = tmp;
			}
			else if(stu[j].age == stu[j+1].age)//如果年龄相同，按照成绩排序
			{
				if(stu[j].score > stu[j+1].score)
				{
					tmp = stu[j];
					stu[j] = stu[j+1];
					stu[j+1] = tmp;
				}
			}
		}
	}
}

int main()
{
	student stu[5] = 
	{
		{"mike", 18, 90},
		{"jiang", 18, 80},
		{"lily", 30, 70},
		{"lucy", 22, 88},
		{"lilei", 33, 60}
	};
	
	int n = sizeof(stu)/sizeof(stu[0]);
	
	printf("排序前：\n");
	print_stu(stu, n);
	
	//排序
	sort_stu(stu, n);
	
	printf("排序后：\n");
	print_stu(stu, n);
	
	return 0;
}