/*������Ϸ(��Linuxƽ̨�±�д)��
	1)��������������ĸ�0-9֮������֣����ǲ���һ����λ����
	A.srand( (unsigned)time(NULL) ); �Ե�ǰʱ��Ϊ׼�������������
	  ע�⣺�˺�������ÿ�ο�ʼ��Ϸ�����һ�μ���
	B.rand();
	  ע�⣺rand()������ÿ����һ�Σ�����һ���������
	
	��������ͷ�ļ���*/
	#include <stdlib.h> //srand(),  rand()
	#include <time.h>   //time()
	int main(){
		srand( (unsigned)time(NULL) ); 
		int answer =rand()%10;
		int gus=0;
		do{
			printf("��������µ�����");
			scanf("%d",&gus);
			if(answer>gus){
			printf("С��С��");
			}else if (answer<gus)
			{
				printf("���˴���");
			}else{
				printf("��ϲ������");
				break;
			}			
		}while(gus>=0 && gus<=9);
		return 0;
	}
