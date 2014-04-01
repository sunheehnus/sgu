#include<stdio.h>
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
	int i,N,cnt;
	scanf("%d",&N);
	if(N==1)
	{
		printf("1\n");
		return 0;
	}
	cnt = 0;
	for(i=1;i<N;i++)
	{
		if(gcd(i,N)==1)
			cnt++;
	}
	printf("%d\n",cnt);
	return 0;
}
