#include <stdio.h>
//1���и����飬�ҳ��ڶ�����������Ҵ�ӡ������ʹ��*��������Ԫ�ظ�������Ҫʹ��[]��
int main(){
	int a[] = {100,100,100,234,123,500,32,68,41,99,13,71};
	int max= 0;
	int smax = 0;
	if(* a>* (a+1)){
		max=*a;smax =*(a+1);
	}
	else if(* a<* (a+1)){
		smax =*a;
		max=*(a+1);
	}else{
		max=*a;
		smax=*a;
	}
	for(int i=2;i<sizeof(a)/sizeof(a[0]);i++){
		if (*(a+i)>max){
			smax=max;
			max=*(a+i);}
		else if (smax<*(a+i)&&*(a+i)<max)
		{
			smax=*(a+i);
		}
		else if (max==smax&&*(a+i)<smax)
		{
			smax=*(a+i);
		}		
	}
	printf("�ڶ�����=%d",smax);
	return 0;
	}
	
	

	
//2����ʹ�ÿ⺯����ʵ���ַ�����������
	char src[100] = "hello";
	char dst[100]; //��src�����ݿ�����dst
	
	void my_strcpy(char dst[], char src[]);