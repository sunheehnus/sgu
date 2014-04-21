#include<stdio.h>
int map[128][128];
int color[128][128];
int degree[128];
int visit[128];
int N;
void DFS(int island, int cr)
{
	int i;
	if(visit[island])
		return;
	visit[island] = 1;
	for(i=1;i<=N;i++)
	{
		if(map[island][i]&&!color[island][i])
		{
			color[island][i] = cr;
			color[i][island] = cr;
			cr = 3 - cr;
			DFS(i, cr);
		}
	}
}
int main()
{
	int i,j;
	int exist1,exist2;
	scanf("%d",&N);
	for(i=1;i<=N;i++)
	{
		while(1)
		{
			scanf("%d",&j);
			if(j==0)
				break;
			map[i][j] = 1;
			degree[i]++;
		}
	}
	for(i=1;i<=N;i++)
	{
		if(degree[i]&1)
			DFS(i,1);
	}
	for(i=1;i<=N;i++)
	{
		if(!(degree[i]&1)&&(degree[i]>3))
			DFS(i,1);
	}
	for(i=1;i<=N;i++)
		DFS(i,1);
	for(i=1;i<=N;i++)
	{
		if(degree[i]>1)
		{
			exist1=exist2=0;
			for(j=1;j<=N;j++)
			{
				if(color[i][j]==1)
					exist1 = 1;
				else if(color[i][j]==2)
					exist2 = 1;
			}
			if(!(exist1&exist2))
			{
				printf("No solution\n");
				return 0;
			}
		}
	}
	for(i=1;i<=N;i++)
	{
		for(j=1;j<=N;j++)
		{
			if(color[i][j])
				printf("%d ",color[i][j]);
		}
		printf("0\n");
	}
	return 0;
}
