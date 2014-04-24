/*
 * Silly, every line is with sides parallel to coordinate axes.
 */
#include<stdio.h>
int K;
struct Line{int x1, y1, x2, y2;} lines[10008];

int max(int a, int b)
{
	return a>b?a:b;
}
int min(int a, int b)
{
	return a<b?a:b;
}
int on(struct Line line, int x, int y)
{
	if(line.x1==line.x2)
	{
		if(line.x1==x && line.y1<=y && line.y2>=y)
			return 1;
	}
	else
	{
		if(line.y1==y && line.x1<=x && line.x2>=x)
			return 1;
	}
	return 0;
}
int cross(struct Line line1, struct Line line2)
{
	if(line1.x1 == line1.x2)
	{
		if(line2.x1 == line2.x2)
		{
			if(line1.x1 == line2.x1)
			{
				if(max(line1.y1,line2.y1)<=min(line1.y2,line2.y2))
					return -1;
			}
		}
		else
		{
			if(line2.y1>=line1.y1&&line2.y2<=line1.y2&&line2.x1<=line1.x1&&line2.x2>=line1.x2)
				return 1;
		}
	}
	else
	{
		if(line2.x1 == line2.x2)
		{
			if(line1.y1>=line2.y1&&line1.y2<=line2.y2&&line1.x1<=line2.x1&&line1.x2>=line2.x2)
				return 1;
		}
		else
		{
			if(line1.y1 == line2.y1)
			{
				if(max(line1.x1,line2.x1)<=min(line1.x2,line2.x2))
					return -1;
			}
		}
	}
	return 0;
}
int connect_hori(struct Line l1, struct Line l_horiz)
{
	if(l1.y1==l1.y2)
		return 0;
	if(l1.x1==l_horiz.x1 && l1.y1==l_horiz.y1)
		return 1;
	if(l1.x2==l_horiz.x1 && l1.y2==l_horiz.y1)
		return -1;
	if(l1.x1==l_horiz.x2 && l1.y1==l_horiz.y2)
		return 1;
	if(l1.x2==l_horiz.x2 && l1.y2==l_horiz.y2)
		return -1;
	return 0;
}
int main()
{
	int i,j,pos1,pos2;
	int cro,tmp;
	scanf("%d\n",&K);
	for(i=1;i<=K;i++)
	{
		scanf("%d %d %d %d",&lines[i].x1,&lines[i].y1,&lines[i].x2,&lines[i].y2);
		if((lines[i].x1==lines[i].x2 && lines[i].y1>lines[i].y2) || (lines[i].y1==lines[i].y2 && lines[i].x1>lines[i].x2))
		{
			lines[i+1] = lines[i];
			lines[i].x1 = lines[i+1].x2;
			lines[i].y1 = lines[i+1].y2;
			lines[i].x2 = lines[i+1].x1;
			lines[i].y2 = lines[i+1].y1;
		}
	}
	scanf("%d %d",&lines[0].x1,&lines[0].y1);
	lines[0].x2 = 11111;
	lines[0].y2 = lines[0].y1;
	for(i=1;i<=K;i++)
	{
		if(on(lines[i],lines[0].x1,lines[0].y1))
		{
			printf("BORDER\n");
			return 0;
		}
	}
	for(i=1,cro=0;i<=K;i++)
	{
		tmp = cross(lines[0],lines[i]);
		if(tmp==-1)
		{
			for(j=1;j<=K;j++)
			{
				if((pos1=connect_hori(lines[j],lines[i]))!=0)
					break;
			}
			for(j++;j<=K;j++)
			{
				if((pos2=connect_hori(lines[j],lines[i]))!=0)
					break;
			}
			if(!(pos1&pos2))
			{
				printf("FUCK\n");
				return 0;
			}
			if(pos1 != pos2)
				cro-=1;
		}
		else if(tmp==1)
			cro++;
	}
	if(cro&1)
		printf("INSIDE\n");
	else
		printf("OUTSIDE\n");
	return 0;
}
