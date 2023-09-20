#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int my_strcmp(char [],char []); // 字符串相同判断函数
void listen(); // 监听指令输入

void main()
{
	printf("请输入指令及操作:\n");
	while (1)
	{
		listen();
	}
}

/**
 * 字符串相同判断函数
 * @param  char[]  a  比对字符串1
 * @param  char[]  a  比对字符串2
 * @return Int
 */
int my_strcmp(char a[],char b[]) {
	int a_len = sizeof(a), b_len = sizeof(b);
	if (a_len == b_len) {
		int i = 0,n = 0;
		while (i<a_len)
		{
			if (a[i] != b[i]) { // 当其中某个字符不一致时n自加
				n++;
			}
			i++;
		}
		if (!n) { // 非0返回真
			return 1;
		}
		else {
			return 0;
		}
	}
	else { // 当两变量长度不一致时直接返回false
		return 0;
	}
}

/**
 * 监听输入&指令判断
 */
void listen() {
	char command[5] = "";
	int a, b, sum = 0;
	scanf("%s %d %d", command, &a, &b);
	if (my_strcmp("add", command)) {
		// 计算 xx + xx 的值
		sum = a + b;
		printf("结果: %d + %d = %d\n--------------\n", a, b, sum);
	}
	else if (my_strcmp("sub", command)) {
		//计算 xx - xx 的值
		sum = a - b;
		printf("结果: %d - %d = %d\n--------------\n", a, b, sum);
	}
	else if (my_strcmp("mux", command)) {
		//计算 xx * xx 的值
		sum = a * b;
		printf("结果: %d * %d = %d\n--------------\n", a, b, sum);
	}
	else if (my_strcmp("dive", command)) {
		//计算 xx / xx 的值
		sum = a / b;
		printf("结果: %d / %d = %d\n--------------\n", a, b, sum);
	}
	else {
		printf("不存在该指令\"%s\",请重新输入指令及操作:\n", command);
	}
}
