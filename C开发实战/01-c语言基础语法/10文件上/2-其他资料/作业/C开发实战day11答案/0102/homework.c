#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

typedef struct student
{
    char name[50]; //姓名
    unsigned int age;
    int score; //成绩
} stu;

// 1、假如有5个学生，按照年龄排序，如果年龄相同，按照成绩排序
void _sort(stu *, int);
void _print(stu *, int);
void show_clock();

int main(void)
{
    stu arr[5] = {{"haha", 18, 80}, {"hehe", 17, 80}, {"xixi", 18, 70}, {"shasha", 18, 90}, {"bibi", 18, 90}};
    int len = sizeof(arr) / sizeof(stu);
    _sort(arr, len);
    _print(arr, len);
    show_clock();
    return 0;
}
void _sort(stu *arr, int len)
{
    stu temp;
    for (size_t i = 0; i < len - 1; i++)
    {
        for (size_t j = 0; j < len - 1 - i; j++)
        {
            if (arr[j].age > arr[j + 1].age)
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
            else if (arr[j].age == arr[j + 1].age)
            {
                if (arr[j].score > arr[j + 1].score)
                {
                    temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }
    }
}

void _print(stu *arr, int len)
{
    for (int i = 0; i < len; i++)
    {
        printf("第%d个学生名字是%s,年龄是%d,成绩是%d\n", i, arr[i].name, arr[i].age, arr[i].score);
    }
}

// 2、利用sleep函数(Linux平台)结合结构体，编写一个模拟时钟
void show_clock()
{
    time_t timep;
    struct tm *p;
    printf("--------------------------------------\n");
    while (1)
    {
        sleep(1);
        time(&timep);
        p = localtime(&timep);
        printf("\r现在是北京时间:%04d-%d-%d 星期%d %02d:%02d:%02d", 1900 + p->tm_year, 1 + p->tm_mon, p->tm_mday, p->tm_wday, p->tm_hour, p->tm_min, p->tm_sec);
        fflush(stdout);
    }
}