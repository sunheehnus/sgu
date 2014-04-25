#include<stdio.h>
int N;
int A[5][5],B[5][5];
int exist;
int nextx(int x, int y)
{
	if(x==N&&y==N)
		return -1;
	return y==N?(x+1):x;
}
int nexty(int x, int y)
{
	if(x==N&&y==N)
		return -1;
	return y==N?1:(y+1);
}
int abs_ok(int x, int y)
{
	int cnt = 0;
	if(x<1||x>N||y<1||y>N)
		return 1;
	if(x-1>=1&&y>=1&&A[x-1][y]>A[x][y])
		cnt ++;
	if(x+1<=N&&y>=1&&A[x+1][y]>A[x][y])
		cnt ++;
	if(x>=1&&y-1>=1&&A[x][y-1]>A[x][y])
		cnt ++;
	if(x>=1&&y+1<=N&&A[x][y+1]>A[x][y])
		cnt ++;
	return cnt == B[x][y];
}
int exceptdown_ok(int x, int y)
{
	int cnt = 0;
	if(x<1||x>N||y<1||y>N)
		return 1;
	if(x-1>=1&&y>=1&&A[x-1][y]>A[x][y])
		cnt ++;
	if(x>=1&&y-1>=1&&A[x][y-1]>A[x][y])
		cnt ++;
	if(x>=1&&y+1<=N&&A[x][y+1]>A[x][y])
		cnt ++;
	return (cnt == B[x][y])||(cnt == B[x][y]-1);
}
int exceptright_ok(int x, int y)
{
	int cnt = 0;
	if(x<1||x>N||y<1||y>N)
		return 1;
	if(x-1>=1&&y>=1&&A[x-1][y]>A[x][y])
		cnt ++;
	if(x+1<=N&&y>=1&&A[x+1][y]>A[x][y])
		cnt ++;
	if(x>=1&&y-1>=1&&A[x][y-1]>A[x][y])
		cnt ++;
	return (cnt == B[x][y])||(cnt == B[x][y]-1);
}
int exceptdownright_ok(int x, int y)
{
	int cnt = 0;
	if(x<1||x>N||y<1||y>N)
		return 1;
	if(x-1>=1&&y>=1&&A[x-1][y]>A[x][y])
		cnt ++;
	if(x>=1&&y-1>=1&&A[x][y-1]>A[x][y])
		cnt ++;
	return (cnt == B[x][y])||(cnt == B[x][y]-1)||(cnt == B[x][y]-2);
}
int ok(int x, int y)
{
	if(!abs_ok(x-1,y))
		return 0;
	if(x!=N)
	{
		if(!exceptdown_ok(x,y-1))
			return 0;
		if(!exceptdownright_ok(x,y))
			return 0;
	}
	else
	{
		if(!abs_ok(x,y-1))
			return 0;
		if(y==N&&!abs_ok(x,y))
			return 0;
		else if(y!=N&&!exceptright_ok(x,y))
			return 0;
	}
	return 1;
}
void Build(int x, int y)
{
	int i;
	int nx,ny;
	if(x==-1||y==-1)
	{
		exist=1;
		return;
	}
	nx = nextx(x, y);
	ny = nexty(x, y);
	for(i=0; i<=9; i++)
	{
		if(exist)
			return;
		A[x][y] = i;
		if(ok(x,y))
			Build(nx,ny);
	}
}
int main()
{
	int i,j;
	scanf("%d",&N);
	for(i=1;i<=N;i++)
	{
		for(j=1;j<=N;j++)
			scanf("%d",&B[i][j]);
	}
	Build(1,1);
	if(exist)
	{
		for(i=1;i<=N;i++)
		{
			for(j=1;j<=N;j++)
				printf("%d ",A[i][j]);
			printf("\n");
		}
	}
	else
	{
		printf("NO SOLUTION\n");
	}
	return 0;
}
