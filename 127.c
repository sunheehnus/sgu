#include<stdio.h>
int array[8192];
void quicksort(int start, int end, int *array)
{
	int i,j,mid,tmp;
	if(start<end)
	{
		i = start;
		j = end;
		mid = (start + end)>>1;
		tmp = array[mid];
		array[mid] = array[start];
		while(i<j)
		{
			while(i<j&&array[j]>=tmp)
				j--;
			array[i] = array[j];
			while(i<j&&array[i]<=tmp)
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
	int i,j;
	int K,N;
	int result;
	scanf("%d %d",&K,&N);
	for(i=0;i<N;i++)
		scanf("%d",array+i);
	quicksort(0,N-1,array);
	result = 2;
	for(i=0;i<N;i=j)
	{
		for(j=i+1;j<N&&array[j]/1000==array[i]/1000;j++);
		result += (j-i)/K+!!((j-i)%K);
	}
	printf("%d\n",result);
	return 0;
}
