#include <stdio.h>

int main()
{
	int a[] = {5,100,56,45,21,67,32,68,41,99,13,71};
	
	//首先默认第一个成员和第二个成员就是最大和第二大
    int max = 0; //最大的成员
    int smax = 0;//第二大成员
	//for(int i=0;i<n-1;i++)
	//{
    if ( *(a+i) > *(a+i+1) )
    {
        max = *(a+0);
        smax = *(a+1);
		
    }
//	break;
//	}
    else 
		//if(*(a+i) < *(a+i+1) )
    
    {
        smax = *(a+0);
        max = *(a+1);
		break;
    }
	//}
	//从第三个成员开始找，如果找到比max更大的成员，那么让max等于这个成员
    //让smax等于max
    int i;
	int n = sizeof(a)/sizeof(*a); //元素个数
    for(i = 2; i < n; i++)
    {
        if ( *(a+i) > max )
        {
			
            smax = max;
			max = *(a+i);
           
        }
        else if (*(a+i) > smax && *(a+i) < max) //*(a+i)有可能等于max
        {
            smax = *(a+i);
        }
    }
	
    printf("smax = %d\n", smax);
	
	return 0;
}