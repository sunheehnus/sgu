#include<stdio.h>
int step[128][128];
int N;

void Build(int length, int nowstep)
{
	int i,j;
	for(i=1;i<=length/2;i++)
	{
		for(j=i;j<length-i+1;j+=2)
		{
			step[i][j] = nowstep;
			step[i][j+1] = nowstep+2;
			step[length-i+1][j] = nowstep;
			step[length-i+1][j+1] = nowstep+2;
			step[j][i] = nowstep;
			step[j+1][i] = nowstep+2;
			step[j][length-i+1] = nowstep;
			step[j+1][length-i+1] = nowstep+2;
		}
		step[i][j] = nowstep;
		step[length-i+1][j] = nowstep;
		step[j][i] = nowstep;
		step[j][length-i+1] = nowstep;
		nowstep += 4;
	}
}
int main()
{
	int i,j,k,st;
	scanf("%d",&N);
	if(N&1)
		Build(N,N);
	else
	{
		for(i=1;i<=N;i+=2)
		{
			step[N][i+1] = N+1;
			step[N][i] = N+3;
			step[i+1][N] = N+1;
			step[i][N] = N+3;
		}
		Build(N-1,N+5);
	}
	if(N&1)
	{
		for(k=1,st=N;k<N;k++,st+=2)
		{

			printf("%d",st);
			for(i=1;i<=N;i++)
			{
				for(j=1;j<=N;j++)
				{
					if(step[i][j]==st)
					{
						printf(" %d",(i-1)*N+j);
					}
				}
			}
			printf("\n");
		}
	}
	else
	{
		for(k=1,st=N+1;k<=N;k++,st+=2)
		{

			printf("%d",st);
			for(i=1;i<=N;i++)
			{
				for(j=1;j<=N;j++)
				{
					if(step[i][j]==st)
					{
						printf(" %d",(i-1)*N+j);
					}
				}
			}
			printf("\n");
		}
	}
	return 0;
}
