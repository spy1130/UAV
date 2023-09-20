#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void start_game(void);
void game_cmd(void)
{
	printf("��1 ������Ϸ\n");
	printf("��2 �鿴��Ϸ����\n");
	printf("��0 �˳���Ϸ\n");
}
void game_rule(void)
{
	printf("������:ϵͳ���������һ����λ�����ڲ�ͬ�Ѷ�\n");
	printf("��������Ӧ�Ĵ���ȥ�²�������֡�ϵͳ�����ʾ\n");
	printf("��Ϣ���ڹ涨�����ڲ¶Լ���ʤ��\n");

	int cmd=0;
	printf("��1 ������Ϸ\n");
	printf("��0 �˳���Ϸ\n");
	scanf("%d", &cmd);
	getchar();

	switch(cmd)
	{
		case 1:
			start_game();
			break;
		case 0:
			exit(-1);
	}
}
void start_game(void)
{
	//��λ�����
	int dst[4] = {0};
	int lev[3] = {10,7,5};
	for (int i = 0; i < sizeof(dst)/sizeof(dst[0]); ++i)
	{
		dst[i] = rand()%10;//��ȡһλ�� 123%10==3
	}

	printf("��ѡ����Ϸ�Ѷȼ���1(10��)��2(7��)��3(5��)\n");
	int level = 0;
	scanf("%d", &level);
	getchar();

	printf("Lev.%d\n", level);
	printf("��ʼ��Ϸ����������ֵ:\n");

	
	for (int i = 0; i < lev[level-1]; ++i)
	{
		int flag = 0;
		int data = 0;
		scanf("%d", &data);
		getchar();

		//��ȡ�������ݵ�ÿ��λ
		int src[4] = {0};
		for (int j = sizeof(src)/sizeof(src[0]) -1; j >= 0 ; --j)
		{
			src[j] = data%10;
			data = data/10;
		}

		//src��dst��λ�Ƚ�
		for (int j=0; j < sizeof(src)/sizeof(src[0]); ++j)
		{
			if(src[j] == dst[j])
			{
				printf("��%dλ���\n", j+1);
				flag ++;
			}
			else if(src[j] < dst[j])
			{
				printf("��%dλС����ȷ��\n", j+1);
			}
			else if(src[j] > dst[j])
			{
				printf("��%dλ������ȷ��\n", j+1);
			}

		}

		if(flag == 4)//��ȷ
		{
			printf("��������ȷ��������˳�\n");
			getchar();
			exit(-1);
		}
		if(i+1<lev[level-1])
			printf("�ٴ���������\n");

	}


	printf("ʧ����\n");
	return;

}
int main(int argc, char const *argv[])
{

	//�������������
	srand(time(NULL));
	while(1)
	{
		game_cmd();
		int cmd = 0;
		scanf("%d",&cmd);
		getchar();//ȥ���س�

		switch(cmd)
		{
			case 0:
				return 0;
			case 1:
				//������Ϸ
				start_game();
				break;
			case 2:
				game_rule();
				break;
		}
	}
	
	return 0;
}