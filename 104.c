#include<stdio.h>
#include<string.h>
int A[128][128];
int F,V;
int path[128];
int max;
void Place(int flower, int vase, int *place, int value)
{
	int i;
	if(flower>F||vase>V)
	{
		if(value>max)
		{
			max = value;
			for(i=1;i<=V;i++)
				path[i] = place[i];
		}
	}
	else
	{
		for(i=vase; i<=V; i++)
		{
			place[i] = flower;
			value += A[flower][i];
			Place(flower+1,i+1,place,value);
			value -= A[flower][i];
			place[i] = 0;
		}
	}
}
void build()
{
	int tmp[128];
	memset(tmp,0,sizeof(tmp));
	Place(1,1,tmp,0);
}
int main()
{
	int i,j;
	scanf("%d %d",&F,&V);
	for(i=1;i<=F;i++)
	{
		for(j=1;j<=V;j++)
			scanf("%d",&A[i][j]);
	}
	build();
	printf("%d\n",max);
	for(i=1;i<=V;i++)
	{
		if(path[i])
			printf("%d ",i);
	}
	printf("\n");
	return 0;
}
