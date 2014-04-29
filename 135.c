#include<stdio.h>
int main()
{
	int i;
	int N, res;
	scanf("%d",&N);
	for(i=0,res=1;i<N;i++)
		res += i+1;
	printf("%d\n",res);
	return 0;
}
