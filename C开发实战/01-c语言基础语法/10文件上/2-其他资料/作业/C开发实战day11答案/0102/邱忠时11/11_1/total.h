#pragma once
#include <stdio.h>
#define MAX 1024   //学生人数

typedef struct _std
{
	char *name;//姓名
	unsigned int age;
	float score;//成绩	
}std;

extern void fun(std **, int);      //分配空间
extern void fuzhi(std **, int );   //赋值
extern void n_sort(std**, int);	   //英文名字排序
extern void a_sort(std **, int );  //年龄排序
extern void s_sort(std**, int);    //分数排序

void(*g[5])(std **, int) = {fun, fuzhi,n_sort,a_sort,s_sort }; 
//五个函数类型相同，函数指针数组存放