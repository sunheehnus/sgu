#include<stdio.h>
int main()
{
	int N;
	scanf("%d",&N);
	printf("%d\n",N-(N/3+!!(N%3)));
	return 0;
}
