#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
FILE *file=NULL;
struct Node             //用作树节点结构 
{
	struct Node * next[9];
};

Node * New ()        //函数用作创建新的树节点 
{
	struct Node * q =(struct Node*)malloc(sizeof(struct Node));
	for (int i=0;i<9;i++)       //对结构体内的每个指针初始化 
	{
		q->next[i]=NULL;
	}
	return q;
}

void swap(int *a,int *b)    // 交换函数，将两数交换 
{
	int c;
	c=*a;
	*a=*b;
	*b=c;
}

int main(int argc, char* argv[])
{
	//fopen_s(&file,".\\sudoku.txt","w+");
	file=fopen("sudoku.txt","w+");
	if (argc>3)     //判断参数数量，大于输入标准，输出错误提示 
	{
		printf("ERROR!");
	}
	else if (!strcmp(argv[1],"-c"))  //判断输入参数格式 
	{
		int i=0,t=0,temp=1;
		while(argv[2][i]!='\0')
		{
			if (argv[2][i]<=57 && argv[2][i]>=48)  //将输入的数字转化为INT型同时判断输入是否合法 
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
		struct Node *node = New(); //建立根节点 
		srand(time(NULL));
		while(t--)  //循环生成数独终盘 
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
			while(temp1--)  //对第一行进行10次随机交换，使第一行产生随机
			{
				int r1=rand()%8+1;   
				int r2=rand()%8+1;
				if (r1!=r2)
				{
					swap(&sudoku[0][r1],&sudoku[0][r2]);
				}
			}
			int x=1,y=0,row=0,rm; //x,y表示当前要填空格所在的坐标，rm是生成的随机数，row代表行数 
			while (x!=9) //对数独每一行进行生成 
			{
				bool p=false; //p是数值是否可用的标记 
				int rt=0;  //rt记录随机的次数 
				while(!p && rt<20)   //对每一个数进行调整 
				{
					row=0;
					rm=rand()%(9-y);  //对当前及之后可交换位置的选取 
					rt++;
					while(row<x)  //检查选取的位置是否合法 
					{
						if (sudoku[row][y] == sudoku[x][rm+y])break; //发现前面的位置和当前数据冲突 
						else
						{
							row++;
						}
					}
					if (row==x) p=true;   //检查结束，全通过 
					else
					{
						continue; //检查未通过，重新开始 
					}
					int initR, initC;
					if (x < 3)initR = 0;
					else if (x < 6)initR = 3;
					else if (x < 9)initR = 6;
					if (y < 3)initC = 0;
					else if (y < 6)initC = 3;
					else if (y < 9)initC = 6;  //判断当前位置所在九宫 
					for (i = 0; i < x%3; i++)  //与九宫内的数进行比较 
					{
						for (int j = 0; j < 3; j++)
						{
							if (sudoku[i+initR][j+initC]==sudoku[x][rm+y])
							{
								p=false;
								j=3; //脱出循环 
								i=x%3; //脱出循环 
							}
						}
					}
					if (p)  //当前数值合法，进行交换 
					{
						swap(&sudoku[x][y],&sudoku[x][y+rm]);
					}
				}
				y=(y+1)%9;  //坐标改变 
				if (rt>=20)  //如果随机多次未能命中，则退后一行，重新生成 
				{
					if (x!=1)
					x--;
					y=0;
				}
				else if (!y) //如果y超过8，则换行 
				{
					x++;
				}
			}
			//  检测重复阶段 
			int e = 1; //判断是否重复 
			Node * q = New(); 
			q = node;
			for (i=0;i<9;i++)   // 取斜向9个数作为数独终盘的特征进行判断 
			{
				if (i == 8)
				{
					if (q->next[sudoku[i][i] - 1] != NULL)  //发现重复特征，判断该终盘已生成，重新生成 
					{
						e = 0;
						t++;
					}
				}
				else if (q -> next[sudoku[i][i]-1]!=NULL)
				{
					q =q -> next[sudoku[i][i]-1];
				}
				else
				{
					struct Node *n=New();
					q -> next[sudoku[i][i]-1]=n;
					q=q -> next[sudoku[i][i]-1];
				}
			}
			// 输出阶段 
			if (e)
			{
				for (i = 0; i < 9; i++)
				{
					for (int j = 0; j < 9; j++)
					{
						fprintf(file, "%d ", sudoku[i][j]);
					}
					fprintf(file, "\n");
				}
				fprintf(file, "\n");
			}
		}	
		//printf(file,"finish");
	}
	else
	{
		printf("ERROR!");
	}
	fclose(file);
	return 0;
}
