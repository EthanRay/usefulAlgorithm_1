/*
A implementation of Dijkstra Algorithm for solving Path-Repair  problems
*/

#include<stdio.h>  
#include<stdlib.h>
#include<vector>
#include<algorithm>  
#define MAXVEX 100
#define INF 65535


using namespace std;

int prev2[MAXVEX];
int V = 28;

struct edge
{
	int to;
	int cap;
	int cost;
};
std::vector<edge>G2[MAXVEX];
bool used[MAXVEX];

void dijkRj(int s)
{

	int dis[MAXVEX];
	bool used[MAXVEX];
	fill(prev2, prev2 + V, -1);
	fill(dis, dis + V, INF);
	fill(used, used + V, false);
	dis[s] = 0;

	while (true)
	{
		int v = -1, mins = INF;
		for (int u = 0; u < V; ++u)
		{
			if (!used[u] && dis[u] < mins)
			{
				mins = INF;
				v = u;
			}
		}

		if (v == -1)break;
		used[v] = true;

		for (int u = 0; u <G2[v].size(); ++u)
		{
			edge e = G2[v][u];
			if (dis[e.to] > dis[v] + e.cost)
			{
				dis[e.to] = dis[v] + e.cost;
				prev2[e.to] = v;
			}
		}
	}
}

void getPath(int t)
{
	vector<int> path;
	for (; t != -1; t = prev2[t])path.push_back(t);
	reverse(path.begin(), path.end());

	for (int i = 0; i < path.size(); ++i)
		printf("%d ", path[i]);
	printf("\n");

}