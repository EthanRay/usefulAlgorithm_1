/*
快排求第i小元素
Find the i-th minimum element using quick sort
*/

#include<stdio.h>
#include<stdlib.h>
#include<algorithm>


bool flg = true;
void Solve13(int a[], int low, int high, int k)
{
	int tmp = a[low];
	int i = low, j = high;
	if (i > j)
		return;
	while (flg)
	{
		while (a[j] >= tmp&&i < j)--j;
		while (a[i] <= tmp&&i < j)++i;
		if (i < j)
			std::swap(a[i], a[j]);
		else
			break;
	}
	std::swap(a[i], a[low]);

	if (i == k)
	{
		printf("%d\n", a[i]);
		flg = false;
		return;
	}
	Solve13(a, low, i - 1, k);
	Solve13(a, i + 1, high, k);
}
void QSrun(int a[], int n, int i)
{
	Solve13(a, 0, n - 1, 1);
}