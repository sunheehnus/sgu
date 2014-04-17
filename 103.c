#include<stdio.h>
struct Info{char startcolor; int starttime,bluetime,purpletime;};
struct Info info[304];
int pre[304];
int time[304];
int visit[304];
int output[304];
int map[304][304];
char shine1[40104];
char shine2[40104];
int N,M,total;
int gcd(int a, int b)
{
	if(a==0)
		return b;
	if(a>b)
		return gcd(b,a);
	else
		return gcd(b%a,a);
}
int lcm(int a, int b)
{
	return a*b/gcd(a,b);
}
void fillin(int pos, char *target, int cnt)
{
	int i,j,k;
	for(i=0;i<info[pos].starttime;i++)
		target[i] = info[pos].startcolor;
	if(info[pos].startcolor == 'B')
	{
		for(i=0,k=info[pos].starttime;i<cnt;i++)
		{
			for(j=0;j<info[pos].purpletime;j++)
				target[k++] = 'P';
			for(j=0;j<info[pos].bluetime;j++)
				target[k++] = 'B';
		}
	}
	else
	{
		for(i=0,k=info[pos].starttime;i<cnt;i++)
		{
			for(j=0;j<info[pos].bluetime;j++)
				target[k++] = 'B';
			for(j=0;j<info[pos].purpletime;j++)
				target[k++] = 'P';
		}
	}
}
int find(int pos1, int pos2, int time)
{
	int period, minstart, i;
	int cnt,left;
	period = lcm(info[pos1].bluetime+info[pos1].purpletime,info[pos2].bluetime+info[pos2].purpletime);
	fillin(pos1, shine1, period/(info[pos1].bluetime+info[pos1].purpletime));
	fillin(pos2, shine2, period/(info[pos2].bluetime+info[pos2].purpletime));
	minstart = info[pos1].starttime > info[pos2].starttime ? info[pos2].starttime:info[pos1].starttime;
	if(time < minstart)
	{
		for(i=time; i<minstart+period; i++)
		{
			if(shine1[i]==shine2[i])
				return i;
		}
		return -1;
	}
	else
	{
		cnt = (time - minstart)/period;
		left = (time - minstart)%period;
		for(i=minstart+left; i<minstart+period; i++)
		{
			if(shine1[i]==shine2[i])
				return i+cnt*period;
		}
		for(i=minstart; i<minstart+left; i++)
		{
			if(shine1[i]==shine2[i])
				return i+(cnt+1)*period;
		}
		return -1;
	}
}
int main()
{
	int start,end,i,j,lij,k,min,pos;
	int riC,tiB,tiP;
	char tmp[8];
	scanf("%d %d",&start,&end);
	scanf("%d %d",&N,&M);
	for(i=1;i<=N;i++)
	{
		scanf("%s %d %d %d",tmp,&riC,&tiB,&tiP);
		info[i].startcolor = tmp[0];
		info[i].starttime = riC;
		info[i].bluetime = tiB;
		info[i].purpletime = tiP;
	}
	for(k=1;k<=M;k++)
	{
		scanf("%d %d %d",&i,&j,&lij);
		map[i][j] = map[j][i] = lij;
	}
	for(i=1;i<=N;i++)
		time[i] = 0x7fffffff;
	pre[start] = -1;
	time[start] = 0;
	while(visit[end]==0)
	{
		pos = 0;
		min = 0x7fffffff;
		for(i=1;i<=N;i++)
		{
			if(visit[i]==0&&time[i]<min)
			{
				pos = i;
				min = time[i];
			}
		}
		if(pos==0)
			break;
		visit[pos] = 1;
		for(i=1;i<=N;i++)
		{
			if(visit[i]==0&&map[pos][i])
			{
				j = find(i,pos,time[pos]);
				if(j!=-1&&time[i]>map[pos][i]+j)
				{
					time[i] = map[pos][i] + j;
					pre[i] = pos;
				}
			}
		}
	}
	if(visit[end]==0)
		printf("0\n");
	else
	{
		printf("%d\n",time[end]);
		i = end;
		while(i!=-1)
		{
			output[total++] = i;
			i = pre[i];
		}
		for(i=total-1;i>=0;i--)
			printf("%d ",output[i]);
		printf("\n");
	}
	return 0;
}
