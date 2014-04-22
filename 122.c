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
void reverse(int *array, int start, int end)
{
	int tmp;
	while(start<end)
	{
		tmp = array[start];
		array[start] = array[end];
		array[end] = tmp;
		start ++;
		end --;
	}
}
void shift(int *array, int length, int distance)
{
	reverse(array,0,length-distance-1);
	reverse(array,length-distance,length-1);
	reverse(array,0,length-1);
}
void DFS(int i)
{
	int j;
	visit[i] = 1;
	path[total++] = i;
	for(j=1;j<=N;j++)
	{
		if(!visit[j]&&map[i][j])
		{
			DFS(j);
			break;
		}
	}
}
void Build()
{
	int i,j,z;

	/* i) */
	DFS(1);

	/* ii) */
	while(1)
	{
		/* a) */
		if(map[path[0]][path[total-1]])
		{
			/* b) */
			if(total==N)
			{
				finish = 1;
				break;
			}
			/* c) */
			else
			{
				for(z=1;z<=N;z++)
				{
					if(!visit[z])
					{
						for(i=1;i<=N;i++)
						{
							if(visit[i]&&map[z][i])
								break;
						}
						if(i<=N)
							break;
					}
				}
				if(z<=N)
				{
					for(j=0;j<total;j++)
					{
						if(path[j]==i)
							break;
					}
					shift(path,total,total-j);
					for(i=total;i>0;i--)
						path[i] = path[i-1];
					path[0] = z;
					visit[z] = 1;
					total++;
				}
			}
		}
		/* iii) */
		else
		{
			for(i=1;i<total-1;i++)
			{
				if(map[path[0]][path[i]]&&map[path[i-1]][path[total-1]])
					break;
			}
			if(i>=total-1)
				break;
			reverse(path,i,total-1);
		}
	}
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
	Build();
	if(!finish)
		printf("No solution\n");
	else
	{
		for(i=0;i<N&&path[i]!=1;i++);
		shift(path,N,N-i);
		for(i=0;i<N;i++)
			printf("%d ",path[i]);
		printf("%d\n",path[0]);
	}
	return 0;
}
