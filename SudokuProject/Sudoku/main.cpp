#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
FILE *file=NULL;

void swap(int *a,int *b)
{
	int c;
	c=*a;
	*a=*b;
	*b=c;
}

int main(int argc, char* argv[])
{
	file=fopen(".\\sudoku.txt","w+");
	if (!strcmp(argv[1],"-c"))
	{
		int i=0,t=0,temp=1;
		while(argv[2][i]!='\0')
		{
			if (argv[2][i]<=57 && argv[2][i]>=48)
			{
				t*=10;
				t+=(argv[2][i]-48);
				i++;
			}
			else
			{
				printf("ERROR!");
				return 0;
			}
		}
		srand(time(NULL));
		while(t--)
		{
			int sudoku[9][9]= {9,8,7,6,5,4,3,2,1,
			                   9,8,7,6,5,4,3,2,1,
			                   9,8,7,6,5,4,3,2,1,
			                   9,8,7,6,5,4,3,2,1,
			                   9,8,7,6,5,4,3,2,1,
			                   9,8,7,6,5,4,3,2,1,
			                   9,8,7,6,5,4,3,2,1,
			                   9,8,7,6,5,4,3,2,1,
			                   9,8,7,6,5,4,3,2,1
			                  };
			int temp1=10;
			while(temp1--)
			{
				int r1=rand()%8+1;
				int r2=rand()%8+1;
				if (r1!=r2)
				{
					swap(&sudoku[0][r1],&sudoku[0][r2]);
				}
			}
			int x=1,y=0,row=0,column,rm;
			while (x!=9)
			{
				bool p=false;
				int rt=0;
				while(!p && rt<20)
				{
					row=0;
					rm=rand()%(9-y);
					rt++;
					while(row<x)
					{
						if (sudoku[row][y] == sudoku[x][rm+y])break;
						else
						{
							row++;
						}
					}
					if (row==x) p=true;
					else
					{
						continue;
					}
					int initR, initC;
					if (x < 3)initR = 0;
					else if (x < 6)initR = 3;
					else if (x < 9)initR = 6;
					if (y < 3)initC = 0;
					else if (y < 6)initC = 3;
					else if (y < 9)initC = 6;
					for (i = 0; i < x%3; i++)
					{
						for (int j = 0; j < 3; j++)
						{
							if (sudoku[i+initR][j+initC]==sudoku[x][rm+y])
							{
								p=false;
								j=3;
								i=x%3;
							}
						}
					}
					if (p)
					{
						swap(&sudoku[x][y],&sudoku[x][y+rm]);
					}
				}
				y=(y+1)%9;
				if (rt>=20)
				{
					if (x!=1)
					x--;
					y=0;
				}
				else if (!y)
				{
					x++;
				}
			}
			for (i=0;i<9;i++)
			{
				for (int j=0; j<9;j++)
				{
					fprintf(file,"%d ",sudoku[i][j]);
				}
				fprintf(file,"\n");
			}
			fprintf(file,"\n");
		}
		fprintf(file,"finish");
	}
	else
	{
		printf("ERROR!");
	}
	fclose(file);
	return 0;
}
