#include <stdio.h>
//1、有个数组，找出第二大的数，并且打印出来（使用*操作数组元素个数，不要使用[]）
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
	printf("第二个数=%d",smax);
	return 0;
	}
	
	

	
//2、不使用库函数，实现字符串拷贝功能
	char src[100] = "hello";
	char dst[100]; //把src的内容拷贝给dst
	
	void my_strcpy(char dst[], char src[]);