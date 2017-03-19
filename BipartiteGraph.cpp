/*
The Solution of Bipartite Graph problems by Depth-first search
*/
#include<stdio.h>  
#include<stdlib.h>
#include<vector>
#define MAXVEX 100

using namespace std;

vector<int>G[MAXVEX];
int V = 25;
int color[MAXVEX] = { 0 };
bool dfs(int v, int c)
{
	color[v] = c;
	for (int i = 0; i < G[v].size(); ++i)
	{
		if (color[G[v][i] == c])return false;
		if (color[G[v][i]] == 0 && !dfs(G[v][i], -c))return false;
	}
	return true;
}
void solve22()
{
	for (int i = 0; i < V; ++i)
	{
		if (color[i] == 0)
		{
			if (!dfs(i, 1))
			{
				printf("NO\n");
				return;
			}
		}
	}

	for (int i = 0; i < V; ++i)
	{
		printf("%d=%d ", i, color[i]);
	}
	printf("\nYES\n");
}