/*
Printing all array of N numbers using DFS
*/
#include<stdio.h>  
#include<stdlib.h>
int a[10] = { 0 };
int t[5] = { 11, 12, 13, 14, 15 };
int usedx[100] = { 0 };

void dfsFun(int n)
{
	if (n == 5)
	{
		for (int i = 0; i < 5; ++i)
		{
			printf("%d ", a[i]);
		}
		printf("\n");
		return;
	}

	for (int i = 0; i < 5; ++i)
	{
		if (usedx[t[i]] == 0)
		{
			a[n] = t[i];
			usedx[t[i]] = 1;
			dfsFun(n + 1);
			usedx[t[i]] = 0;
		}
	}

}