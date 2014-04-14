/*
 *    Euler-circuit (undirected graph)
 *
 *    Procedure Euler-circuit (start);
 *    Begin
 *      Foreach (start,v) Do
 *      If (start,v) is not visited
 *       Then Begin
 *        set (start,v) visited;
 *        set (v,start) visited;
 *        Euler-circuit (v);
 *        Push (start,v);
 *      End;
 *    End;
 */
#include<stdio.h>
int map[16][16];
int degree[16];
struct Edge{int s1,s2;} edge[128],trace[128];
int total;
void dfs(int s)
{
	int i;
	for(i=0;i<7;i++)
	{
		if(map[s][i])
		{
			map[s][i]--;
			map[i][s]--;
			dfs(i);
			trace[total].s1 = s;
			trace[total].s2 = i;
			total++;
		}
	}
}
int main()
{
	int N,s,t,i,j;
	int oddcnt;
	scanf("%d",&N);
	for(i=0;i<N;i++)
	{
		scanf("%d %d",&s,&t);
		map[s][t]++;
		map[t][s]++;
		degree[s]++;
		degree[t]++;
		edge[i].s1=s;
		edge[i].s2=t;
	}
	for(i=0,oddcnt=0;i<7;i++)
	{
		oddcnt += degree[i]&1;
	}
	if(oddcnt!=0&&oddcnt!=2)
		printf("No solution\n");
	else if(oddcnt)
	{
		for(i=0;i<7&&(degree[i]&1)==0;i++);
		dfs(i);
	}
	else
	{
		for(i=0;i<7&&degree[i]==0;i++);
		dfs(i);
	}
	if(total!=N)
		printf("No solution\n");
	else
	{
		for(i=total-1;i>=0;i--)
		{
			for(j=0;j<N;j++)
			{
				if(trace[i].s1==edge[j].s1&&trace[i].s2==edge[j].s2)
				{
					printf("%d +\n",j+1);
					edge[j].s1 = edge[j].s2 = -1;
					break;
				}
				else if(trace[i].s1==edge[j].s2&&trace[i].s2==edge[j].s1)
				{
					printf("%d -\n",j+1);
					edge[j].s1 = edge[j].s2 = -1;
					break;
				}
			}
		}
	}
	return 0;
}
