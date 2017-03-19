/*
Using CPU clock to generate pseudo-random number
*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>


//CODE-1
void wfun()
{
	int x = 100;
	srand((unsigned)time(NULL));
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			int tmp = rand() % x;//随机产生0-x之内的整数  
			printf("%d ", tmp);
		}
		printf("\n");
	}
}

//CODE-2
// No Repeat Nums
int k, vx,usedx[100];
void fundg2()
{
	if (k == 0)srand((unsigned)time(NULL));
	int tmp = rand() % vx;

	if (k == 5)return;
	if (usedx[tmp] == 0)
	{
		printf("%d ", tmp);
		usedx[tmp] = 1;
		++k;
		fundg2();
	}
	else
		fundg2();
}
