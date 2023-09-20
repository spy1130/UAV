1、不用使用库函数，编写一个函数my_atoi()，功能和atoi是一样的
	int my_atoi(char *str);	
	
	my_atoi("+123"); 结果为十进制123
	my_atoi("-123"); 结果为十进制-123
	my_atoi("123"); 结果为十进制123
	
	提示：字符如何转换为整形：'1' - '0' = 1; '2' - '0' = 2;
	
2、按要求完成如下接口功能：
	//%s方式打印数组的元素
	//n代表数组元素个数
	void print_word(char *words[], int n);

	//冒泡排序
	void sort_word(char *words[], int n);

	int main()
	{
		char *words[] = { "city", "student", "tree", "bee" };
		int n = sizeof(words) / sizeof(words[0]);

		//排序前，city student tree bee
		print_word(words, n);

		//冒泡排序
		sort_word(words, n);

		//排序后，bee city student tree
		print_word(words, n);

		return 0;
	}
