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
int equal(struct boxes a, struct boxes b)
{
	return (a.big == b.big) && (a.small == b.small);
}
int main()
{
	int cnt;
	struct boxes start,f1,f2;
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
	cnt = 0;
	f1 = f2 = start;
	do
	{
		f1 = next(f1);
		cnt ++;
		if(f1.small==0)
		{
			printf("%d\n",cnt);
			return 0;
		}
		f2 = next(next(f2));
	}
	while(!equal(f1,f2));
	printf("-1\n");
	return 0;
}
