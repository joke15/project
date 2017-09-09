#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
FILE *file=NULL;
struct Node             //�������ڵ�ṹ 
{
	struct Node * next[9];
};

Node * New ()        //�������������µ����ڵ� 
{
	struct Node * q =(struct Node*)malloc(sizeof(struct Node));
	for (int i=0;i<9;i++)       //�Խṹ���ڵ�ÿ��ָ���ʼ�� 
	{
		q->next[i]=NULL;
	}
	return q;
}

void swap(int *a,int *b)    // �������������������� 
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
	if (argc>3)     //�жϲ������������������׼�����������ʾ 
	{
		printf("ERROR!");
	}
	else if (!strcmp(argv[1],"-c"))  //�ж����������ʽ 
	{
		int i=0,t=0,temp=1;
		while(argv[2][i]!='\0')
		{
			if (argv[2][i]<=57 && argv[2][i]>=48)  //�����������ת��ΪINT��ͬʱ�ж������Ƿ�Ϸ� 
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
		struct Node *node = New(); //�������ڵ� 
		srand(time(NULL));
		while(t--)  //ѭ�������������� 
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
			while(temp1--)  //�Ե�һ�н���10�����������ʹ��һ�в������
			{
				int r1=rand()%8+1;   
				int r2=rand()%8+1;
				if (r1!=r2)
				{
					swap(&sudoku[0][r1],&sudoku[0][r2]);
				}
			}
			int x=1,y=0,row=0,rm; //x,y��ʾ��ǰҪ��ո����ڵ����꣬rm�����ɵ��������row�������� 
			while (x!=9) //������ÿһ�н������� 
			{
				bool p=false; //p����ֵ�Ƿ���õı�� 
				int rt=0;  //rt��¼����Ĵ��� 
				while(!p && rt<20)   //��ÿһ�������е��� 
				{
					row=0;
					rm=rand()%(9-y);  //�Ե�ǰ��֮��ɽ���λ�õ�ѡȡ 
					rt++;
					while(row<x)  //���ѡȡ��λ���Ƿ�Ϸ� 
					{
						if (sudoku[row][y] == sudoku[x][rm+y])break; //����ǰ���λ�ú͵�ǰ���ݳ�ͻ 
						else
						{
							row++;
						}
					}
					if (row==x) p=true;   //��������ȫͨ�� 
					else
					{
						continue; //���δͨ�������¿�ʼ 
					}
					int initR, initC;
					if (x < 3)initR = 0;
					else if (x < 6)initR = 3;
					else if (x < 9)initR = 6;
					if (y < 3)initC = 0;
					else if (y < 6)initC = 3;
					else if (y < 9)initC = 6;  //�жϵ�ǰλ�����ھŹ� 
					for (i = 0; i < x%3; i++)  //��Ź��ڵ������бȽ� 
					{
						for (int j = 0; j < 3; j++)
						{
							if (sudoku[i+initR][j+initC]==sudoku[x][rm+y])
							{
								p=false;
								j=3; //�ѳ�ѭ�� 
								i=x%3; //�ѳ�ѭ�� 
							}
						}
					}
					if (p)  //��ǰ��ֵ�Ϸ������н��� 
					{
						swap(&sudoku[x][y],&sudoku[x][y+rm]);
					}
				}
				y=(y+1)%9;  //����ı� 
				if (rt>=20)  //���������δ�����У����˺�һ�У��������� 
				{
					if (x!=1)
					x--;
					y=0;
				}
				else if (!y) //���y����8������ 
				{
					x++;
				}
			}
			//  ����ظ��׶� 
			int e = 1; //�ж��Ƿ��ظ� 
			Node * q = New(); 
			q = node;
			for (i=0;i<9;i++)   // ȡб��9������Ϊ�������̵����������ж� 
			{
				if (i == 8)
				{
					if (q->next[sudoku[i][i] - 1] != NULL)  //�����ظ��������жϸ����������ɣ��������� 
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
			// ����׶� 
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
