/*
Calculating all the vertices which the shortest path to vertex v is K.

Assuming MGraph is the Graph
*/

#include<stdio.h>
#include<stdlib.h>
#include<queue>

struct MGraph
{
	int edge[100][100];
	int NumVex;
};

void shortPath(int v, int k, int t, MGraph *G)
{
	std::queue<int> Que;
	int leve = 0, n = G->NumVex;

	int* book;
	book = new int[n];
	memset(book, -1, sizeof(book));

	Que.push(v); book[v] = 0;
	while (!Que.empty())
	{
		int u = Que.front();
		Que.pop();

		if (book[u] == leve)leve++;
		if (leve > k)
		{
			Que.push(u);
			break;
		}

		for (int i = 0; i < n; ++i)
		{
			if (book[i] < 0 && G->edge[u][i]>0)
			{
				book[i] = leve;
				Que.push(i);
			}
		}
	}

	if (!Que.empty())
	{
		while (!Que.empty())
		{
			int u = Que.front();
			Que.pop();
			printf("%d ", u);
		}
	}
}

