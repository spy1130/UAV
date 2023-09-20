#include <stdio.h>
#include <stdlib.h>
int main(int argc, char const *argv[])
{
	
	int num[10] = {0};  
	int len = sizeof(num)/sizeof(num[0]);

	//从键盘获取输入
	printf("请输入10个整数\n");
	for (int i = 0; i < len; ++i)
	{
		scanf("%d", &num[i]);
	}

    //遍历    
    for (int i=0; i < len; i++)  
    {  
        printf("%d ", num[i]);  
    }   
    printf("\n");   
   
    //外层循环     
    for (int j = 0; j<len-1; j++)   
    {  
        //内层循环    
        for (int i = 0; i + 1 < 10 -j; i++)  
        {   
            if (num[i] > num[i + 1])  
            {   
                int tmp = 0;  
  
                tmp = num[i];  
                num[i] = num[i + 1];  
                num[i + 1] = tmp;   
            }   
        }   
    }   
  
    for (int i = 0; i < len; i++)   
    {   
        printf("%d ", num[i]);   
    }  
    printf("\n");  

    system("pause");
	return 0;
}