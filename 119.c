#include<stdio.h>
struct pair{int a,b;} result[20000];
int exist(int a, int b, int total)
{
	int i;
	for(i=0;i<total;i++)
	{
		if(a==result[i].a && b==result[i].b)
			return 1;
	}
	return 0;
}
void quicksort(int start, int end, struct pair *array)
{
	int i,j,mid;
	struct pair tmp;
	if(start < end)
	{
		i = start;
		j = end;
		mid = (start + end)/2;
		tmp = array[mid];
		array[mid] = array[i];
		while(i<j)
		{
			while(i<j&&((array[j].a>tmp.a)||(array[j].a==tmp.a&&array[j].b>=tmp.b)))
				j--;
			array[i] = array[j];
			while(i<j&&((array[i].a<tmp.a)||(array[i].a==tmp.a&&array[i].b<=tmp.b)))
				i++;
			array[j] = array[i];
		}
		array[i] = tmp;
		quicksort(start, i-1, array);
		quicksort(i+1, end, array);
	}
}
int main()
{
	int N,A,B,total;
	int i;
	scanf("%d %d %d",&N,&A,&B);
	total = 0;
	for(i=0;!exist(A*i%N,B*i%N,total);i++)
	{
		result[total].a = A*i%N;
		result[total].b = B*i%N;
		total ++;
	}
	quicksort(0,total-1,result);
	printf("%d\n",total);
	for(i=0;i<total;i++)
		printf("%d %d\n",result[i].a,result[i].b);
	return 0;
}
