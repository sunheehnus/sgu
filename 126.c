#include<stdio.h>
struct boxes{ int small, big;};
struct boxes next(struct boxes b)
{
	b.big -= b.small;
	b.small += b.small;
	if(b.big<b.small)
	{
		b.big ^= b.small;
		b.small ^= b.big;
		b.big ^= b.small;
	}
	return b;
}
int gcd(int a,int b)
{
	if(a>b)
		gcd(b,a);
	else
	{
		if(b%a==0)
			return a;
		return gcd(b%a,a);
	}
}
int main()
{
	int cnt;
	struct boxes start;
	scanf("%d %d",&start.small,&start.big);
	if(start.big<start.small)
	{
		start.big ^= start.small;
		start.small ^= start.big;
		start.big ^= start.small;
	}
	if(start.small==0)
	{
		printf("0\n");
		return 0;
	}
	cnt = gcd(start.small,start.big);
	start.small/=cnt;
	start.big/=cnt;
	if(start.small==start.big)
		printf("1\n");
	else if((start.small+start.big)&(start.small+start.big-1))
		printf("-1\n");
	else
	{
		cnt = 0;
		while(start.small)
		{
			cnt++;
			start = next(start);
		}
		printf("%d\n",cnt);
	}
	return 0;
}
