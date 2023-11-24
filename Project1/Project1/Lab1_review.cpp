#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

void compute(float*, float* ,float*);
void display(float*, float* ,float*);


int main()
{
	float hours[3] = { 10.2,12.8,5.2 };
	float efficiency[3] = { 8.0,8.5,6.0 };
	float productivity[3];

	compute(hours, efficiency, productivity);
	display(hours, efficiency, productivity);

	return 0;
}

void compute(float* hours, float* efficiency, float* productivity)
{
	for (int i = 0; i < 3; i++)
	{
		productivity[i] = hours[i] * efficiency[i];
	}
}

void display(float* hours, float* efficiency, float* productivity)
{
	printf("Productivity:\n");
	for (int i = 0; i < 3; i++)
	{
		printf("Day %d: %.2f hours * %.2f efficiency = %.2f\n", i + 1, hours[i], efficiency[i], productivity[i]);
	}
}