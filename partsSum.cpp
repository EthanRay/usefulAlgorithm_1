#include<stdio.h>
#include<stdlib.h>

int book[1000], em[1000];
bool flag = true;
void dfs(int step, int n, int a[], int k, int m)
{
	int i;

	if (flag == false)return;

	if (step == m)
	{
		int sum = 0;
		for (i = 0; i < m; ++i)
			sum += em[i];
		if (sum == k)
		{
			printf("%d= ", k);
			for (i = 0; i < m; ++i)
			{
				if (i == 0)
					printf("%d+", em[i]);
				else if (i == m - 1)
					printf("%d\n", em[i]);
				else
					printf("%d+", em[i]);
			}
			flag = false;
		}
		return;
	}

	for (i = 0; i < n; ++i)
	{
		if (book[i] == 0)
		{
			book[i] = 1;
			em[step] = a[i];

			dfs(step + 1, n, a, k, m);
			book[i] = 0;
		}
	}
	return;
}

void solve(int n, int a[], int k)
{
	for (int i = 1; i <= n; ++i)
	{
		dfs(0, n, a, k, i);
	}
}