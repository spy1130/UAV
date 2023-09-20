#include <stdio.h>

int main()
{
	char src[100] = "abcedfdgds\0";
	char dst[100] = { "abcedfdgds\0" };
	int i = 0;
	char *p =src;
	char *q = dst;
	for (i = 0; *(p+i) != '\0'; i++)
	{
		//*(q+i) = *(p+i); // q[i] = p[i]
		dst[i]= src[i];// *(dst+i) = *(src_+i)
		//
	}
	//补结束符
	*(q+i) = 0;

	printf("%s\n", dst);
	
	return 0;
}