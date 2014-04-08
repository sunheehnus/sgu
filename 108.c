#include<stdio.h>
#include<string.h>

#define getpos(i) (array[i/8]>>(7-(i%8))&1)
#define setpos(i) (array[i/8] |= (1<<(7-(i%8))))
#define clrpos(i) (array[i/8] &= ~(1<<(7-(i%8))))

unsigned char array[1250001];
int map[5000];
int sort[5000];
int result[5000];

void quicksort(int start, int end, int *array)
{
	int i,j,mid,tmp;
	if(start<end)
	{
		i = start;
		j = end;
		mid = (i+j)>>1;
		tmp = array[mid];
		array[mid] = array[start];
		while(i<j)
		{
			while(i<j&&array[j]>=tmp)
				j--;
			array[i] = array[j];
			while(i<j&&array[i]<=tmp)
				i++;
			array[j] = array[i];
		}
		array[i] = tmp;
		quicksort(start,i-1,array);
		quicksort(i+1,end,array);
	}
}
int bisearch(int start, int end, int *array, int target)
{
	int mid;
	while(start<=end)
	{
		mid = (start + end)>>1;
		if(array[mid]<target)
			start = mid + 1;
		else if(array[mid]>target)
			end = mid - 1;
		else
			return mid;
	}
	return -1;
}
int next(int a)
{
	int tmp = a;
	while(tmp)
	{
		a+=tmp%10;
		tmp/=10;
	}
	return a;
}

void cleardescent(int startpos, int ceiling)
{
	int nowpos;
	nowpos = next(startpos);
	while(nowpos<=ceiling && getpos(nowpos))
	{
		clrpos(nowpos);
		nowpos = next(nowpos);
	}
}
int main()
{
	int i,j;
	int N,K,nowpos;
	int total;
	memset(array,-1,sizeof(array));
	clrpos(0);
	scanf("%d %d",&N,&K);
	for(i=1;i<=N;i++)
	{
		if(getpos(i))
		{
			cleardescent(i,N);
		}
	}
	for(i=0;i<K;i++)
	{
		scanf("%d",map+i);
		sort[i]=map[i];
	}
	quicksort(0,K-1,sort);
	total = 0;
	for(i=1,j=0;i<=N;i++)
	{
		if(getpos(i))
		{
			total++;
			while(j<K&&total == sort[j])
				result[j++] = i;
		}
	}
	printf("%d\n",total);
	for(i=0;i<K;i++)
	{
		nowpos = bisearch(0,K-1,sort,map[i]);
		printf("%d ",result[nowpos]);
	}
	printf("\n");
	return 0;
}
