#include<stdio.h>
int month[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
int main()
{
	int i,tmp;
	int day,mon;
	scanf("%d %d",&day,&mon);
	if(day>month[mon])
		printf("Impossible\n");
	else
	{
		for(i=1,tmp=0;i<mon;i++)
			tmp += month[i];
		tmp += day;
		printf("%d\n",tmp%7?tmp%7:7);
	}
	return 0;
}
