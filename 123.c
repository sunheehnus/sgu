#include<stdio.h>
int F[64];
int fab(int n)
{
	if(F[n])
		return F[n];
	F[n] = fab(n-1) + fab(n-2);
	return F[n];
}
int main()
{
	int S;
	int i,result;
	scanf("%d",&S);
	F[1] = F[2] = 1;
	for(i=1,result=0;i<=S;i++)
		result += fab(i);
	printf("%d\n",result);
	return 0;
}
