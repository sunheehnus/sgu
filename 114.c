#include<stdio.h>
int map[50000];
struct City
{
	int pos;
	int citizens;
}city[50000];
long long pre[50000];
long long suf[50000];
long long disagree[50000];

int main()
{
	int N,X,P,total,pos;
	int i;
	long long sum,temdisagree;
	total = 0;
	temdisagree = 0;
	scanf("%d",&N);
	while(N--)
	{
		scanf("%d %d",&X,&P);
		map[X] += P;
	}
	for(i=1;i<50000;i++)
	{
		if(map[i])
		{
			total ++;
			city[total].pos = i;
			city[total].citizens = map[i];
			temdisagree += (city[total].pos-city[1].pos) * city[total].citizens;
		}
	}
	if(total==1)
	{
		printf("%.5lf\n",(double)city[1].pos);
		return 0;
	}
	for(i=1;i<=total;i++)
		pre[i] = pre[i-1] + city[i].citizens;
	for(i=1,sum=pre[total];i<=total;i++)
		suf[i] = sum - pre[i-1];
	disagree[1] = temdisagree;
	for(i=2;i<=total;i++)
		disagree[i] = disagree[i-1] + (pre[i-1]-suf[i])*(city[i].pos-city[i-1].pos);
	for(pos=1;pos<total&&disagree[pos+1]<disagree[pos];pos++);
	printf("%.5lf\n",(double)city[pos].pos);
	return 0;
}
