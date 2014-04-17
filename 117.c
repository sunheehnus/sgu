#include<stdio.h>
int pop(int a)
{
	a = (a>>1&0x55555555) + (a&0x55555555);
	a = (a>>2&0x33333333) + (a&0x33333333);
	a = (a>>4&0x0f0f0f0f) + (a&0x0f0f0f0f);
	a = (a>>8&0x00ff00ff) + (a&0x00ff00ff);
	a = (a>>16&0x0000ffff) + (a&0x0000ffff);
	return a&0xff;
}
int cnt(int a)
{
	a = a | (a>>16);
	a = a | (a>>8);
	a = a | (a>>4);
	a = a | (a>>2);
	a = a | (a>>1);
	return pop(a);
}
int quick_pow_mod(int num, int pow, int mod)
{
	int i,result,bits;
	if(pow==0)
		return 1%mod;
	bits = cnt(pow);
	for(i=bits-1,result=1;i>=0;i--)
	{
		result = result*result % mod;
		if(pow>>i&1)
			result = result*num % mod;
	}
	return result;
}
int main()
{
	int N,M,K;
	int i,tmp;
	int result;
	scanf("%d %d %d",&N,&M,&K);
	for(i=0,result=0;i<N;i++)
	{
		scanf("%d",&tmp);
		if(!quick_pow_mod(tmp,M,K))
			result++;
	}
	printf("%d\n",result);
	return 0;
}
