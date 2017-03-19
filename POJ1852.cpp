#include<algorithm>
#include<stdio.h>
#include<stdlib.h>
using namespace std;
void solve(int L, int n, int x[])
{
	int minT = 0, maxT = 0;
	for (int i = 0; i < n; ++i)
		minT = max(minT, min(x[i], L - x[i]));
	for (int i = 0; i < n; ++i)
		maxT = max(maxT, min(x[i], L - x[i]));
	printf("%d %d\n", minT, maxT);
}