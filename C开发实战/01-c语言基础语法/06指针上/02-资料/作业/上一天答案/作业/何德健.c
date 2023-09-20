#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int my_strcmp(char [],char []); // �ַ�����ͬ�жϺ���
void listen(); // ����ָ������

void main()
{
	printf("������ָ�����:\n");
	while (1)
	{
		listen();
	}
}

/**
 * �ַ�����ͬ�жϺ���
 * @param  char[]  a  �ȶ��ַ���1
 * @param  char[]  a  �ȶ��ַ���2
 * @return Int
 */
int my_strcmp(char a[],char b[]) {
	int a_len = sizeof(a), b_len = sizeof(b);
	if (a_len == b_len) {
		int i = 0,n = 0;
		while (i<a_len)
		{
			if (a[i] != b[i]) { // ������ĳ���ַ���һ��ʱn�Լ�
				n++;
			}
			i++;
		}
		if (!n) { // ��0������
			return 1;
		}
		else {
			return 0;
		}
	}
	else { // �����������Ȳ�һ��ʱֱ�ӷ���false
		return 0;
	}
}

/**
 * ��������&ָ���ж�
 */
void listen() {
	char command[5] = "";
	int a, b, sum = 0;
	scanf("%s %d %d", command, &a, &b);
	if (my_strcmp("add", command)) {
		// ���� xx + xx ��ֵ
		sum = a + b;
		printf("���: %d + %d = %d\n--------------\n", a, b, sum);
	}
	else if (my_strcmp("sub", command)) {
		//���� xx - xx ��ֵ
		sum = a - b;
		printf("���: %d - %d = %d\n--------------\n", a, b, sum);
	}
	else if (my_strcmp("mux", command)) {
		//���� xx * xx ��ֵ
		sum = a * b;
		printf("���: %d * %d = %d\n--------------\n", a, b, sum);
	}
	else if (my_strcmp("dive", command)) {
		//���� xx / xx ��ֵ
		sum = a / b;
		printf("���: %d / %d = %d\n--------------\n", a, b, sum);
	}
	else {
		printf("�����ڸ�ָ��\"%s\",����������ָ�����:\n", command);
	}
}
