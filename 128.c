#include<stdio.h>
#include<string.h>

int color[10004];

struct Point{ int x,y; int next_hor,next_ver;} point[10004];

struct Line{int x1,y1,x2,y2;};
struct Line start_horline[10004];
struct Line end_horline[10004];
struct Line verline[10004];
int horlinecnt,start_horlinepos,end_horlinepos;
int verlinecnt,verlinepos;

char visit[10004];
int xy_array[10004];
int yx_array[10004];
int xxx[10004];
int xtotal;
int yyy[10004];
int ytotal;
int N;
int result;
void quicksortxy( int start, int end)
{
	int i,j,mid,tmp;
	if(start<end)
	{
		mid = (start + end) / 2;
		tmp = xy_array[mid];
		xy_array[mid] = xy_array[start];
		i = start;
		j = end;
		while(i<j)
		{
			while(i<j && (point[xy_array[j]].x>point[tmp].x||(point[xy_array[j]].x==point[tmp].x&&point[xy_array[j]].y>=point[tmp].y)))
				j--;
			xy_array[i] = xy_array[j];
			while(i<j && (point[xy_array[i]].x<point[tmp].x||(point[xy_array[i]].x==point[tmp].x&&point[xy_array[i]].y<=point[tmp].y)))
				i++;
			xy_array[j] = xy_array[i];
		}
		xy_array[i] = tmp;
		quicksortxy(start, i-1);
		quicksortxy(i+1, end);
	}
}
void quicksortyx( int start, int end)
{
	int i,j,mid,tmp;
	if(start<end)
	{
		mid = (start + end) / 2;
		tmp = yx_array[mid];
		yx_array[mid] = yx_array[start];
		i = start;
		j = end;
		while(i<j)
		{
			while(i<j && (point[yx_array[j]].y>point[tmp].y||(point[yx_array[j]].y==point[tmp].y&&point[yx_array[j]].x>=point[tmp].x)))
				j--;
			yx_array[i] = yx_array[j];
			while(i<j && (point[yx_array[i]].y<point[tmp].y||(point[yx_array[i]].y==point[tmp].y&&point[yx_array[i]].x<=point[tmp].x)))
				i++;
			yx_array[j] = yx_array[i];
		}
		yx_array[i] = tmp;
		quicksortyx(start, i-1);
		quicksortyx(i+1, end);
	}
}
void quicksort(int *array, int start, int end)
{
	int i,j,mid,tmp;
	if(start<end)
	{
		mid = (start + end) / 2;
		tmp = array[mid];
		array[mid] = array[start];
		i = start;
		j = end;
		while(i<j)
		{
			while(i<j && array[j]>=tmp)
				j--;
			array[i] = array[j];
			while(i<j && array[i]<=tmp)
				i++;
			array[j] = array[i];
		}
		array[i] = tmp;
		quicksort(array, start, i-1);
		quicksort(array, i+1, end);
	}
}
void quicksort_starthorline(int start, int end)
{
	int i,j,mid;
	struct Line linetmp;
	if(start<end)
	{
		mid = (start + end) / 2;
		linetmp = start_horline[mid];
		start_horline[mid] = start_horline[start];
		i = start;
		j = end;
		while(i<j)
		{
			while(i<j && start_horline[j].x1>=linetmp.x1)
				j--;
			start_horline[i] = start_horline[j];
			while(i<j && start_horline[i].x1<=linetmp.x1)
				i++;
			start_horline[j] = start_horline[i];
		}
		start_horline[i] = linetmp;
		quicksort_starthorline(start, i-1);
		quicksort_starthorline(i+1, end);
	}
}
void quicksort_endhorline(int start, int end)
{
	int i,j,mid;
	struct Line linetmp;
	if(start<end)
	{
		mid = (start + end) / 2;
		linetmp = end_horline[mid];
		end_horline[mid] = end_horline[start];
		i = start;
		j = end;
		while(i<j)
		{
			while(i<j && end_horline[j].x2>=linetmp.x2)
				j--;
			end_horline[i] = end_horline[j];
			while(i<j && end_horline[i].x2<=linetmp.x2)
				i++;
			end_horline[j] = end_horline[i];
		}
		end_horline[i] = linetmp;
		quicksort_endhorline(start, i-1);
		quicksort_endhorline(i+1, end);
	}
}
void quicksort_verline(int start, int end)
{
	int i,j,mid;
	struct Line linetmp;
	if(start<end)
	{
		mid = (start + end) / 2;
		linetmp = verline[mid];
		verline[mid] = verline[start];
		i = start;
		j = end;
		while(i<j)
		{
			while(i<j && verline[j].x1>=linetmp.x1)
				j--;
			verline[i] = verline[j];
			while(i<j && verline[i].x1<=linetmp.x1)
				i++;
			verline[j] = verline[i];
		}
		verline[i] = linetmp;
		quicksort_verline(start, i-1);
		quicksort_verline(i+1, end);
	}
}
int unique(int *array, int length)
{
	int i,j;
	for(i=0,j=0;j<length;)
	{
		if(array[j]==array[i])
			j++;
		else
			array[++i]=array[j++];
	}
	return i+1;
}
void snake(int entry)
{
	int pos = entry;
	while(1)
	{
		if(pos==-1 || point[pos].next_hor==-1 || point[pos].next_ver==-1)
			return;
		visit[pos] = 1;
		if(visit[point[pos].next_hor]==0)
			pos = point[pos].next_hor;
		else if(visit[point[pos].next_ver]==0)
			pos = point[pos].next_ver;
		else
			return;
	}
}
void buildedge(int entry)
{
	int pre = -1;
	int pos = entry;
	memset(visit,0,sizeof(visit));
	while(1)
	{
		if(pre!=-1)
		{
			if(point[pre].x == point[pos].x)
			{
				verline[verlinecnt].x1 = point[pre].x;
				verline[verlinecnt].x2 = point[pre].x;
				verline[verlinecnt].y1 = point[pre].y<point[pos].y?point[pre].y:point[pos].y;
				verline[verlinecnt].y2 = point[pre].y>point[pos].y?point[pre].y:point[pos].y;
				result += verline[verlinecnt].y2 - verline[verlinecnt].y1;
				verlinecnt++;
			}
			else
			{
				start_horline[horlinecnt].y1 = point[pre].y;
				start_horline[horlinecnt].y2 = point[pre].y;
				start_horline[horlinecnt].x1 = point[pre].x<point[pos].x?point[pre].x:point[pos].x;
				start_horline[horlinecnt].x2 = point[pre].x>point[pos].x?point[pre].x:point[pos].x;
				end_horline[horlinecnt].y1 = point[pre].y;
				end_horline[horlinecnt].y2 = point[pre].y;
				end_horline[horlinecnt].x1 = point[pre].x<point[pos].x?point[pre].x:point[pos].x;
				end_horline[horlinecnt].x2 = point[pre].x>point[pos].x?point[pre].x:point[pos].x;
				result += end_horline[horlinecnt].x2 - end_horline[horlinecnt].x1;
				horlinecnt++;
			}
		}
		visit[pos] = 1;
		pre = pos;
		if(visit[point[pos].next_hor]==0)
			pos = point[pos].next_hor;
		else if(visit[point[pos].next_ver]==0)
			pos = point[pos].next_ver;
		else
			break;
	}
	pre = entry;
	pos = point[entry].next_ver;
	verline[verlinecnt].x1 = point[pre].x;
	verline[verlinecnt].x2 = point[pre].x;
	verline[verlinecnt].y1 = point[pre].y<point[pos].y?point[pre].y:point[pos].y;
	verline[verlinecnt].y2 = point[pre].y>point[pos].y?point[pre].y:point[pos].y;
	result += verline[verlinecnt].y2 - verline[verlinecnt].y1;
	verlinecnt++;
	quicksort_starthorline(0, horlinecnt-1);
	quicksort_endhorline(0, horlinecnt-1);
	quicksort_verline(0, verlinecnt-1);
}
int search(int y)
{
	int i,j,mid;
	i = 0;
	j = ytotal - 1;
	while(i<=j)
	{
		mid = (i+j) / 2;
		if(yyy[mid]==y)
			return mid;
		else if(yyy[mid]<y)
			i = mid+1;
		else
			j = mid-1;
	}
	return -1;
}
int main()
{
	int i,j,k,yl,yu;
	scanf("%d",&N);
	for(i=0; i<N; i++)
	{
		scanf("%d %d",&point[i].x,&point[i].y);
		point[i].next_hor = point[i].next_ver = -1;
		xy_array[i] = yx_array[i] = i;
		xxx[i] = point[i].x;
		yyy[i] = point[i].y;
	}
	quicksortxy(0,N-1);
	quicksortyx(0,N-1);
	quicksort(xxx,0,N-1);
	xtotal = unique(xxx, N);
	quicksort(yyy,0,N-1);
	ytotal = unique(yyy, N);
	for(i=0; i<N; i=j)
	{
		for(j=i+1; j<N && point[xy_array[j]].x == point[xy_array[i]].x; j++)
		{
			if(point[xy_array[j]].y==point[xy_array[i]].y)
			{
				printf("0\n");
				return 0;
			}
		}
		if((j-i)&1)
		{
			printf("0\n");
			return 0;
		}
		for(k=i; k<j; k+=2)
		{
			point[xy_array[k]].next_ver = xy_array[k+1];
			point[xy_array[k+1]].next_ver = xy_array[k];
		}
	}
	for(i=0; i<N; i=j)
	{
		for(j=i+1; j<N && point[yx_array[j]].y == point[yx_array[i]].y; j++)
		{
			if(point[yx_array[j]].x==point[yx_array[i]].x)
			{
				printf("0\n");
				return 0;
			}
		}
		if((j-i)&1)
		{
			printf("0\n");
			return 0;
		}
		for(k=i; k<j; k+=2)
		{
			point[yx_array[k]].next_hor = yx_array[k+1];
			point[yx_array[k+1]].next_hor = yx_array[k];
		}
	}
	snake(0);
	for(i=0; i<N; i++)
	{
		if(visit[i]==0||point[i].next_hor==-1||point[i].next_ver==-1)
		{
			printf("0\n");
			return 0;
		}
	}
	buildedge(0);
	for(i=0;i<xtotal;i++)
	{
		while(end_horlinepos<horlinecnt && end_horline[end_horlinepos].x2 == xxx[i])
		{
			color[search(end_horline[end_horlinepos].y1)] --;
			end_horlinepos++;
		}
		while(verlinepos<verlinecnt && verline[verlinepos].x1 == xxx[i])
		{
			yl = search(verline[verlinepos].y1);
			yu = search(verline[verlinepos].y2);
			yl++;
			yu--;
			for(j=yl;j<=yu;j++)
			{
				if(color[j])
				{
					printf("0\n");
					return 0;
				}
			}
			verlinepos++;
		}
		while(start_horlinepos<horlinecnt && start_horline[start_horlinepos].x1 == xxx[i])
		{
			color[search(start_horline[start_horlinepos].y1)] ++;
			start_horlinepos++;
		}
	}
	printf("%d\n",result);
	return 0;
}
