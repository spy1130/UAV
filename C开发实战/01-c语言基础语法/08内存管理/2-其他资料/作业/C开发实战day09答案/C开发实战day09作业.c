1������ʹ�ÿ⺯������дһ������my_atoi()�����ܺ�atoi��һ����
	int my_atoi(char *str);	
	
	my_atoi("+123"); ���Ϊʮ����123
	my_atoi("-123"); ���Ϊʮ����-123
	my_atoi("123"); ���Ϊʮ����123
	
	��ʾ���ַ����ת��Ϊ���Σ�'1' - '0' = 1; '2' - '0' = 2;
	
2����Ҫ��������½ӿڹ��ܣ�
	//%s��ʽ��ӡ�����Ԫ��
	//n��������Ԫ�ظ���
	void print_word(char *words[], int n);

	//ð������
	void sort_word(char *words[], int n);

	int main()
	{
		char *words[] = { "city", "student", "tree", "bee" };
		int n = sizeof(words) / sizeof(words[0]);

		//����ǰ��city student tree bee
		print_word(words, n);

		//ð������
		sort_word(words, n);

		//�����bee city student tree
		print_word(words, n);

		return 0;
	}
