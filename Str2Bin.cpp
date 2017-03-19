/*
Converting a string/chars to a binary
*/

#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include<limits.h>
#include<stdbool.h>



using namespace std;

char* Fun(char a)
{
	int i = 0, t = 0;
	char res[1000];
	char* pc;

	while (a != 0)
	{
		if (a % 2 == 0)
			res[i++] = '0';
		else
			res[i++] = '1';
		a = a / 2;
	}
	pc = (char*)malloc(i* sizeof(char));
	for (int j = i - 1; j >= 0; --j)
	{
		pc[t++] = res[j];

	}
	pc[t] = '\0';
	return pc;
}

char* Decode(char* in)
{
	int len = strlen(in);
	for (int i = 0; i < len; ++i)
	{
		if (i == 0)
			strcpy(in, fun233(in[i]));
		else
			strcat(in, fun233(in[i]));
	}
	return in;
}

void Slove()
{
	char* in;
	char* res;
	in = (char*)malloc(512000 * sizeof(char));
	scanf("\n%[^\n]", in);
	res = Decode(in);
	printf("%s\n", res);
}