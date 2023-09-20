//1、假如有5个学生，按照年龄排序，如果年龄相同，按照成绩排序
#include <stdio.h>

void print(student *stu,int len);
void sort_stu(student *stu, int n);

typedef struct student
{
	char name[50];//姓名
	unsigned int age;
	int score;//成绩
}student;
int main(){
	student num[5]={
		{"mike",18,80},
		{"spric",19,100}.
		{"lily",30,78}.
		{"lucy",22,88}.
		{"lilei",33,60}
	};
	int len =sizeof(num)/sizeof(num[0]);
	print(num,len);
	sort_stu(num,len);
	print(num,len);
}
void print(student *stu,int len){
	printf("name\tage\tscore\n");
	for(int i=0;i<len;i++){
		printf("%s\t%d\t%d\n",stu[i].name,stu[i].age,stu[i].score);
	};
}
void sort_stu(student *stu, int n)
{	student tmp;//临时结构体变量
    for (int i = 0; i < n - 1; i++) // 比较的轮数
    {
        for (int j = 0; j < n - 1 - i; j++) // 每一轮需要比较的次数
        {
            if (stu[j].age>stu[j+i].age)//升序
            {
                tmp = stu[j + 1];
                stu[j + 1] = stu[j];
                stu[j] = tmp;
            }
			else if (stu[i].age==stu[j+1].age)
			{
				if (stu[j].score>stu[j+i].score)//升序
            {
                tmp = stu[j + 1];
                stu[j + 1] = stu[j];
                stu[j] = tmp;
            }
			}
			
        }
    }
}

//2、利用sleep函数(Linux平台)结合结构体，编写一个模拟时钟
	struct Time
	{//表示时间的数据类型
		int hour;
		int minute;
		int second;
	};
	
	
	
	
	
	/*提示：
	1)#include <unistd.h>
	  sleep(1);  //以秒为单位
	  
	2) fflush(stdout); //人为刷新打印缓冲区
	   "\r"，转义字符，跳到句首打印
