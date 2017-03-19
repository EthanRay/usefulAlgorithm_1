/*
Lake Counting
Due to recent rains, water has pooled in various places in Farmer John¡¯s field,
which is represented by a rectangle of N x M (1 <= N <= 100; 1 <= M <= 100) squares.
Each square contains either water (¡®W¡¯) or dry land (¡®.¡¯). Farmer John would like to figure out how many ponds have formed in his field. 
A pond is a connected set of squares with water in them, where a square is considered adjacent to all eight of its neighbors.
Given a diagram of Farmer John¡¯s field, determine how many ponds he has.

Line 1: Two space-separated integers: N and M
Lines 2..N+1: M characters per line representing one row of Farmer John¡¯s field. Each character is either ¡®W¡¯ or ¡®.¡¯. The characters do not have spaces between them.
Line 1: The number of ponds in Farmer John¡¯s field.
*/
#include<stdio.h>
#include<stdlib.h>

int N, M;
char field[100][100];
void dfs(int x, int y)
{
	field[x][y] = '.';

	for (int dx = -1; dx <= 1; ++dx)
		for (int dy = -1; dy <= 1; ++dy)
		{
			int nx, ny;
			nx = x + dx; ny = y + dy;
			if (0 <= nx&&nx <= N && 0 <= ny&&ny <= M&&field[nx][ny] == 'W')
				dfs(nx, ny);
		}
	return;
}
void solve()
{
	int n = 0;
	for (int x = 0; x < N; ++x)
		for (int y = 0; y < M; ++y)
		{
			if (field[x][y] == 'W')
			{
				dfs(x, y);
				++n;
			}
		}
	printf("\n",n);
}