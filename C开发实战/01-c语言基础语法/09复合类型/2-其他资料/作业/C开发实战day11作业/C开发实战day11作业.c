//1��������5��ѧ�������������������������ͬ�����ճɼ�����
#include <stdio.h>

void print(student *stu,int len);
void sort_stu(student *stu, int n);

typedef struct student
{
	char name[50];//����
	unsigned int age;
	int score;//�ɼ�
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
{	student tmp;//��ʱ�ṹ�����
    for (int i = 0; i < n - 1; i++) // �Ƚϵ�����
    {
        for (int j = 0; j < n - 1 - i; j++) // ÿһ����Ҫ�ȽϵĴ���
        {
            if (stu[j].age>stu[j+i].age)//����
            {
                tmp = stu[j + 1];
                stu[j + 1] = stu[j];
                stu[j] = tmp;
            }
			else if (stu[i].age==stu[j+1].age)
			{
				if (stu[j].score>stu[j+i].score)//����
            {
                tmp = stu[j + 1];
                stu[j + 1] = stu[j];
                stu[j] = tmp;
            }
			}
			
        }
    }
}

//2������sleep����(Linuxƽ̨)��Ͻṹ�壬��дһ��ģ��ʱ��
	struct Time
	{//��ʾʱ�����������
		int hour;
		int minute;
		int second;
	};
	
	
	
	
	
	/*��ʾ��
	1)#include <unistd.h>
	  sleep(1);  //����Ϊ��λ
	  
	2) fflush(stdout); //��Ϊˢ�´�ӡ������
	   "\r"��ת���ַ����������״�ӡ
