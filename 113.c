#include<stdio.h>
#include<string.h>
int prime[31624];
int pricnt;
void findprime()
{
	int i,j;
	memset(prime,-1,sizeof(prime));
	prime[0] = prime[1] = 0;
	for(i=2;i<31624;i++)
	{
		if(prime[i]==-1)
		{
			for(j=2;i*j<31624;j++)
				prime[i*j] = 0;
		}
	}
	for(i=0,pricnt=0;i<31624;i++)
	{
		if(prime[i]==-1)
			prime[pricnt++]=i;
	}
}
int main()
{
	int i,j,N,tmp;
	findprime();
	scanf("%d",&N);
	for(i=0;i<N;i++)
	{
		scanf("%d",&tmp);
		for(j=0;j<pricnt;j++)
		{
			if(tmp!=prime[j]&&tmp%prime[j]==0)
				break;
		}
		if(j<pricnt)
		{
			tmp = tmp/prime[j];
			for(j=0;j<pricnt;j++)
			{
				if(tmp==prime[j])
					break;
			}
			if(j<pricnt)
				printf("Yes\n");
			else
			{
				for(j=0;j<pricnt;j++)
				{
					if(tmp%prime[j]==0)
						break;
				}
				if(j<pricnt)
					printf("No\n");
				else
					printf("Yes\n");
			}
		}
		else
			printf("No\n");
	}
	return 0;
}
