/*
 * compile usage:
 *	gcc 120.c -lm -L/lib -L/usr/lib
 */
#include<stdio.h>
#include<math.h>
#define PI 3.1415926535898
struct island{double x,y;} islands[65536];
int equal(double a, double b)
{
	if(a-b<0.0000001 || a-b>-0.0000001)
		return 1;
	return 0;
}
void reverse(struct island *islands, int start, int end)
{
	struct island islandtmp;
	while(start<end)
	{
		islandtmp = islands[start];
		islands[start] = islands[end];
		islands[end] = islandtmp;
		start ++;
		end --;
	}
}
void shift(struct island *islands, int length, int distance)
{
	reverse(islands,0,length-distance-1);
	reverse(islands,length-distance,length-1);
	reverse(islands,0,length-1);
}
int main()
{
	int N,N1,N2,total;
	int i,Ntmp;
	struct island island1,island2,islandtmp;
	double ang1,ang2;
	double ini_ang;
	double ang;
	double x,y;
	double length;
	scanf("%d %d %d",&N,&N1,&N2);
	scanf("%lf %lf",&(island1.x),&(island1.y));
	scanf("%lf %lf",&(island2.x),&(island2.y));
	if(N1>N2)
	{
		Ntmp = N1;
		N1 = N2;
		N2 = Ntmp;
		islandtmp = island1;
		island1 = island2;
		island2 = islandtmp;
	}
	ang1 = PI*(N+N1-N2+1)/N;
	ang2 = 2*PI/N;
	ini_ang = atan2((island1.y-island2.y), (island1.x-island2.x));
	ang = ini_ang - ang1;
	x = y =0;
	x = cos(ang);
	y = sin(ang);
	for(i=1;N1+i!=N2;i++)
	{
		ang -= ang2;
		x += cos(ang);
		y += sin(ang);
	}
	if(island2.y!=island1.y)
		length = (island2.y-island1.y)/y;
	else
		length = (island2.x-island1.x)/x;
	total = 0;
	islands[total++]=island1;
	ini_ang = atan2((island1.y-island2.y), (island1.x-island2.x));
	ang = ini_ang - ang1;
	for(i=1;i<N;i++)
	{
		islands[total].x = islands[total-1].x + length*cos(ang);
		islands[total].y = islands[total-1].y + length*sin(ang);
		ang -= ang2;
		total++;
	}
	shift(islands, N, N1-1);
	for(i=0;i<N;i++)
		printf("%0.6lf %0.6lf\n",islands[i].x,islands[i].y);
	return 0;
}
