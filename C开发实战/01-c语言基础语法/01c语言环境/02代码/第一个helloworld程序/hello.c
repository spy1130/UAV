//# 预处理指令，在预编译时处理
//#include <stdio.h> 包含stdio.h文件  stdio.h类似于菜单
// 两个斜杠是注释
//符号与（）结和代表这个是一个函数 
//main() main函数也叫主函数 整个程序中仅且只有一个main函数，程序从main函数
//开始执行
//int  代表main函数结束之后的返回值类型
//return  结束这个函数，然后返回值，返回值的类型和函数定义时返回值类型一致
//{}里面的是函数体，所有需要执行的代码必须写在{}中
//每一条代码必须以分号；结尾
//printf是一个库函数，printf+（）就是函数调用
#define _CRT_SECURE_NO_WARNINGS     //这个宏定义最好要放到.c文件的第一行
#include <stdio.h>
#include <stdlib.h>
int main01()
{
	//syetem启动程序，如果这个程序系统可以找到，不用加路径，
	//如果环境变量找不到，需要加路径
	//windows路径以\\  或 /
	//system("mspaint");//启动画图板
	//system("C:\\Users\\Administrator\\Desktop\\c++13\\hello.exe");
	system("C:/Users/Administrator/Desktop/c++13/hello.exe");
	printf("hello worldfbahfoahfoooooooooooooooooooooo\n");//打印到终端
	system("pause");//pause程序的作用是等待用户输入任意按键
	return 0;
}


int main02()
{
	//定义整型变量a, b, c
	int a = 3;
	int  b = 4;
	int c = 0;
	//调试时设置断点，断点的意义在于使程序运行至断点时停止，使其可以认为控制
	c = a + b;

	printf("%d\n", c);//把c的值输出

	return 0;//成功完成
}



int main03()
{
	char  buf[1024] = "";
	sprintf(buf,"abc");
	printf("buf=%s\n",buf);
	system("pause");
	return 0;
}


