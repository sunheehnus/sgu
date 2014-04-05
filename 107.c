#include<stdio.h>
#include<math.h>
void violent()
{
	int i;
	long long tmp;
	for(i=sqrt(987654321);i<999999999;i++)
	{
		tmp = (long long)i * i;
		if(tmp%1000000000 == 987654321)
		{
			printf("%d\n",i);
		}
	}
}
int main()
{
	int i,N;
	/*violent();*/
	scanf("%d",&N);
	if(N<9)
		printf("0\n");
	else if(N==9)
		printf("8\n");
	else
	{
		printf("72");
		for(i=10;i<N;i++)
		{
			printf("0");
		}
		printf("\n");
	}
	return 0;
}
