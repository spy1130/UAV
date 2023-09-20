#include <stdio.h>
#include <stdlib.h>
int main(int argc, char const *argv[])
{
	float a[5][3] = {{80,75,56}, {59,65,71}, {59,63,70}, {85,45,90}, {76,77,45}};
	float person_aver[5] = {0.0f};
	int class_lower[5] = {0};

	//行数
	int row = sizeof(a)/sizeof(a[0]);
	//列数
	int col = sizeof(a[0])/sizeof(a[0][0]);
	
	float sum = 0.0f;
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			sum += a[i][j];
			if(a[i][j]<60)
			{
				class_lower[i]++;
			}
		}

		person_aver[i] = sum/col;
		sum = 0.0f;
	}

	printf("老到老五的平均成绩:");
	for (int i = 0; i < row; ++i)
	{
		printf("%.2f ", person_aver[i]);
	}
	printf("\n");

	printf("老大到老五不及格科数：");
	for (int i = 0; i < row; ++i)
	{
		printf("%d ", class_lower[i]);
	}
	printf("\n");
	return 0;
}