#include<stdio.h>
long long x,y,gcd;
void Ext_GCD(long long a, long long b)
{
	long long tmp;
	if(b==0)
	{
		x = 1;
		y = 0;
		gcd = a;
	}
	else
	{
		Ext_GCD(b, a%b);
		tmp = x;
		x = y;
		y = tmp - a/b * y;
	}
}
long long floordiv(long long a, long long b)
{
	if((a>0&&b>0)||(a<0&&b<0))
		return a/b;
	else
		return a/b - !!(a%b);
}
int main()
{
	long long a,b,c,x1,x2,y1,y2,xstep,ystep;
	long long x1x,x2x,y1x,y2x;
	long long result=0;

	scanf("%lld %lld %lld",&a,&b,&c);
	scanf("%lld %lld",&x1,&x2);
	scanf("%lld %lld",&y1,&y2);
	if(a==0&&b==0)
	{
		if(c==0)
			result = (x2-x1+1) * (y2-y1+1);
	}
	else if(a==0)
	{
		if(c%b==0&&((-c/b)>=y1&&(-c/b)<=y2))
			result = x2-x1+1;
	}
	else if(b==0)
	{
		if(c%a==0&&((-c/a)>=x1&&(-c/a)<=x2))
			result = y1-y1+1;
	}
	else
	{
		Ext_GCD(a,b);
		if(c%gcd==0)
		{
			x = - x * (c/gcd);
			y = - y * (c/gcd);
			xstep = b / gcd;
			ystep = - a / gcd;
			if(xstep < 0)
			{
				xstep = -xstep;
				ystep = -ystep;
			}
			x1x = x - floordiv((x - x1),xstep) * xstep;
			x2x = x + floordiv((x2 - x),xstep) * xstep;

			if(ystep < 0)
			{
				xstep = -xstep;
				ystep = -ystep;
			}
			y1x = x - floordiv((y - y1),ystep) * xstep;
			y2x = x + floordiv((y2 - y),ystep) * xstep;

			if(y1x>y2x)
			{
				y1x^=y2x;
				y2x^=y1x;
				y1x^=y2x;
			}
			result = ((x2x>y2x?y2x:x2x) - (x1x>y1x?x1x:y1x))/(xstep>0?xstep:-xstep) + 1;
			result = result < 0 ? 0:result;
		}
	}
	printf("%lld\n",result);
	return 0;
}
