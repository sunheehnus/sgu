#include<stdio.h>
#include<stdlib.h>
int finish;
int N;
char map[1024][1024];
int visit[1024];
int path[1024];
int total;
char buf[4096];

char * next(char *a)
{
	while(*a&&(*a!=' '&&*a!='\t'))
		a++;
	while(*a==' '||*a=='\t')
		a++;
	return a;
}
int num(char *a)
{
	int n=0;
	while(*a>='0'&&*a<='9')
	{
		n*=10;
		n+=*a-'0';
		a++;
	}
	return n;
}
void DFS(int i)
{
	int j;
	visit[i] = 1;
	path[++total] = i;
	if(total==N&&map[i][1])
	{
		finish = 1;
		path[++total] = 1;
		visit[i] = 0;
		return;
	}
	for(j=1;j<=N;j++)
	{
		if(!finish&&!visit[j]&&map[i][j])
		{
			DFS(j);
		}
	}
	visit[i] = 0;
	total--;
}
int main()
{
	int i,j;
	char *pos;
	fscanf(stdin,"%d",&N);
	fgets(buf, 4096, stdin);
	for(i=1;i<=N;i++)
	{
		fgets(buf, 4096, stdin);
		pos = buf;
		if(*pos==' '||*pos=='\t')
			pos = next(pos);
		for(;*pos;pos=next(pos))
		{
			j = num(pos);
			map[i][j] = map[j][i] = 1;
		}
	}
	/*for(i=1;i<=N;i++)*/
	/*{*/
		/*for(j=1;j<=N;j++)*/
			/*printf("%d ",map[i][j]);*/
		/*printf("\n");*/
	/*}*/
	DFS(1);
	if(!finish)
		printf("No solution\n");
	else
	{
		for(i=1;i<=N;i++)
			printf("%d ",path[i]);
		printf("%d\n",path[i]);
	}
	return 0;
}
