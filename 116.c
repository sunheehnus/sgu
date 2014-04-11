#include<stdio.h>
#include<string.h>

#define getpos(array,i) (array[i/8]>>(7-(i%8))&1)
#define setpos(array,i) (array[i/8] |= (1<<(7-(i%8))))
#define clrpos(array,i) (array[i/8] &= ~(1<<(7-(i%8))))

int result[10004];
int rescnt;

unsigned char isPrime[1252];

int superprime[10004];
int spcnt;

int minstep[10004];
int pre[10004];
void findmin(int pos, int cnt)
{
	int i;
	int min = 0x7fffffff;
	int p = 0;
	if(minstep[pos]==1)
		return;
	for(i=0;i<cnt&&pos-superprime[i]>=0;i++)
	{
		if(minstep[pos-superprime[i]]!=0x7fffffff)
		{
			if(minstep[pos-superprime[i]]+1 < min)
			{
				min = minstep[pos-superprime[i]] + 1;
				p = pos-superprime[i];
			}
		}
	}
	if(p!=0)
	{
		pre[pos] = p;
		minstep[pos] = min;
	}
}
void buildresult(int N)
{
	if(pre[N]==-1)
		return;
	while(pre[N])
	{
		result[rescnt++] = N - pre[N];
		N = pre[N];
	}
	result[rescnt++] = N;
}
void outputres()
{
	int i,j,max,pick;
	for(i=0;i<rescnt;i++)
	{
		max = 0;
		pick = -1;
		for(j=0;j<rescnt;j++)
		{
			if(result[j]>max)
			{
				max = result[j];
				pick = j;
			}
		}
		printf("%d ",result[pick]);
		result[pick] = 0;
	}
}
int main()
{
	int i,j;
	int N;
	scanf("%d",&N);
	memset(isPrime,-1,sizeof(isPrime));
	clrpos(isPrime,0);
	clrpos(isPrime,1);
	for(i=0;i<=N;i++)
	{
		if(getpos(isPrime,i))
		{
			for(j=2;i*j<=N;j++)
			{
				clrpos(isPrime,i*j);
			}
		}
	}
	for(i=0,j=0;i<=N;i++)
	{
		minstep[i] = 0x7fffffff;
		pre[i] = -1;
		if(getpos(isPrime,i))
		{
			j++;
			if(getpos(isPrime,j))
			{
				superprime[spcnt++] = i;
				minstep[i] = 1;
				pre[i] = 0;
			}
		}
	}
	for(i=0;i<=N;i++)
	{
		findmin(i, spcnt);
	}
	printf("%d\n",minstep[N]==0x7fffffff?0:minstep[N]);
	buildresult(N);
	outputres();
	printf("\n");
	return 0;
}
