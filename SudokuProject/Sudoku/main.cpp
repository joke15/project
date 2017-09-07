#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <time.h>
#include <string.h>
using namespace std;

int main()
{
	FILE *f1 =fopen(".\\Sudoku.txt","w");
	int t;
	cin >> t;
	int rep[10000] = { 0 }; rep[0] = 100;
	srand(time(NULL));
	while (t)
	{
		int res[9][9];
		memset(res, 0, sizeof(res));
		while (rep[res[0][8] + res[0][7] * 10 + res[0][6] * 100 + res[0][5] * 1000]>=10)
		{
        	int p = 8, num[9] = { 0 };
        	num[8] = 1;
        	res[0][0] = 9;
			while (p)
			{
				int rn = rand() % 8;
				if (!num[rn])
				{
					p--;
					num[rn] = 1;
					res[0][8-p] = rn + 1;
				}
			}
		}
		rep[res[0][8] + res[0][7] * 10 + res[0][6] * 100 + res[0][5] * 1000]++;
		int x = 1, y = 0, z = 0;
		while (x != 9)
		{
			if (z == 50) { if(x!=1)x--; y = 0; z = 0; }
			int row = 0, column = 0, ver = 1;
			int randon = rand() % 9 + 1;
			while (column < y)
			{
				if (randon != res[x][column])column++;
				else { ver = 0; break; }
			}
			while (ver&&row < x)
			{
				if (randon != res[row][y])row++;
				else { ver = 0; break; }
			}
			if (ver)
			{
				int initR, initC, r = x % 3, c = y % 3;
				if (x < 3)initR = 0;
				else if (x < 6)initR = 3;
				else if (x < 9)initR = 6;
				if (y < 3)initC = 0;
				else if (y < 6)initC = 3;
				else if (y < 9)initC = 6;
				for (int i = 0; i < r; i++)
				{
					for (int j = 0; j < c; j++)
					{
						if (randon == res[initR + i][initC + j])ver = 0;
					}
				}
			}
			if (ver)
			{
				res[x][y] = randon;
				z = 0;
				y++;
				if (y % 9 == 0)
				{
					y = y % 9;
					x++;
				}
			}
			z++;
		}
		for (int i = 0; i <= 8; i++)
		{
			for (int j = 0; j <= 8; j++)
			{
				fprintf(f1,"%d ", res[i][j]);
			}
			fprintf(f1,"\n");
		}
		fprintf(f1,"\n");
		t--;
	}
	printf("finish");
	fclose(f1);
	return 0;
}
