#include<stdio.h>
int A[128][128];
int F,V;
int path[128];
int max;
struct Node
{
	int pre,now,value;
} MAX[128][128];
void init()
{
	int i;
	int pos,max;
	pos = 1;
	max = A[1][1];
	for(i=1;i<=V;i++)
	{
		MAX[1][i].pre = -1;
		if(A[1][i]>max)
		{
			pos = i;
			max = A[1][i];
		}
		MAX[1][i].now = pos;
		MAX[1][i].value = max;
	}
}
void build(int f)
{
	int i;
	MAX[f][f].pre = f-1;
	MAX[f][f].now = f;
	MAX[f][f].value = MAX[f-1][f-1].value + A[f][f];
	for(i=f+1;i<=V;i++)
	{
		if(MAX[f][i-1].value>=MAX[f-1][i-1].value+A[f][i])
		{
			MAX[f][i].now = MAX[f][i-1].now;
			MAX[f][i].pre = MAX[f][i-1].pre;
			MAX[f][i].value = MAX[f][i-1].value;
		}
		else
		{
			MAX[f][i].now = i;
			MAX[f][i].pre = i-1;
			MAX[f][i].value = MAX[f-1][i-1].value+A[f][i];
		}
	}
}
int main()
{
	int i,j;
	int pos;
	scanf("%d %d",&F,&V);
	for(i=1;i<=F;i++)
	{
		for(j=1;j<=V;j++)
			scanf("%d",&A[i][j]);
	}
	init();
	for(i=2;i<=F;i++)
		build(i);
	max = MAX[F][V].value;
	printf("%d\n",max);
	i = pos = F;
	j = V;
	while(j!=-1)
	{
		path[--i] = MAX[pos][j].now;
		j = MAX[pos][j].pre;
		pos --;
	}
	for(i=0;i<F;i++)
	{
		printf("%d ",path[i]);
	}
	printf("\n");
	return 0;
}
