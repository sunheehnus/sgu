#include<stdio.h>
long long N[32]={1,1,2};
long long f(int pos)
{
	int i,j;
	long long tmp;
	if(N[pos])
		return N[pos];
	tmp = 0;
	for(i=1;i<pos;i++)
	{
		for(j=i;j<pos;j++)
		{
			tmp += f(i-1)*f(j-i)*f(pos-1-j);
		}
	}
	N[pos] = f(pos-1) + tmp;
	return N[pos];
}
int main()
{
	int K;
	scanf("%d",&K);
	printf("%lld %d\n",f(K),K+1);
	return 0;
}
