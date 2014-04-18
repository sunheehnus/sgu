#include<stdio.h>
int f(int n)
{
	int tmp;
	while(n>=10)
	{
		tmp = n;
		n = 0;
		while(tmp)
		{
			n += tmp%10;
			tmp /= 10;
		}
	}
	return n;
}
int main()
{
	int K,N;
	int result,prefix,tmp;
	scanf("%d",&K);
	while(K--)
	{
		scanf("%d",&N);
		result = 0;
		prefix = 1;
		while(N--)
		{
			scanf("%d",&tmp);
			prefix = f(prefix*f(tmp));
			result = f(result+prefix);
		}
		printf("%d\n",f(result));
	}
	return 0;
}
