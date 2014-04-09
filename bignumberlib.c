#include<stdio.h>
#define MAXCAPACITY 1024

struct BigNum{char num[MAXCAPACITY];int length;int flag;};

/*
 * initialize BigNum
 */
void biginit(struct BigNum * bn);

/*
 * bn = small
 * bn is of struct BigNum type
 * small is of int type
 */
void small2big(int small,struct BigNum *bn);

/*
 * output the bn
 */
void bigoutput(struct BigNum *bn);

/*
 * dst = src
 */
void bigcpy(struct BigNum *src, struct BigNum *dst);

/*
 * return -1 when bn1 > bn2
 *         0 when bn1 == bn2
 *         1 when bn1 < bn2
 */
int bigcmp(struct BigNum *bn1,struct BigNum *bn2);

/*
 * result = bn1 - bn2
 */
void bigminus(struct BigNum *bn1, struct BigNum *bn2, struct BigNum *result);

/*
 * result = bn1 + bn2
 */
void bigplus(struct BigNum *bn1, struct BigNum *bn2, struct BigNum *result);

/*
 * result = bn1 * bn2
 */
void bigmul(struct BigNum *bn1, struct BigNum *bn2, struct BigNum *result);

/*
 * result = bn1^pow
 * bn1 is of struct BigNum type
 * pow is of int type
 */
void bigsmallpow(struct BigNum *bn1, int pow, struct BigNum *result);

/*
 * result = bn1 + bn2 / 2
 */
void bigmid(struct BigNum *bn1, struct BigNum *bn2, struct BigNum *result);

/*
 * result = bn1 + 1;
 */
void biginc(struct BigNum *bn1, struct BigNum *result);

/*
 * result = bn1 - 1
 */
void bigdec(struct BigNum *bn1, struct BigNum *result);

/*
 * result = floor(sqrt(bn))
 */
void bigfloorsqrt(struct BigNum *bn, struct BigNum *result);

/*
 * result = floor(sqrt(bn))
 */
void big_quick_floorsqrt(struct BigNum *bn, struct BigNum *result);

int main()
{
	/*int Sa,Sb;*/
	/*struct BigNum Ba,Bb,res1,res2,result;*/
	/*biginit(&Ba);*/
	/*biginit(&Bb);*/
	/*scanf("%d %d",&Sa,&Sb);*/
	/*small2big(Sa,&Ba);*/
	/*small2big(Sb,&Bb);*/
	/*bigsmallpow(&Ba, Sb, &res1);*/
	/*bigsmallpow(&Bb, Sa, &res2);*/
	/*bigminus(&res1,&res2,&result);*/
	/*bigoutput(&result);*/
	return 0;
}

void biginit(struct BigNum * bn)
{
	bn->length=0;
	bn->flag=1;
}
void bigoutput(struct BigNum *bn)
{
	int i;
	if(bn->flag==-1)
		printf("-");
	for(i=bn->length;i>0;i--)
		printf("%c",bn->num[MAXCAPACITY-i]);
	printf("\n");
}
void small2big(int small,struct BigNum *bn)
{
	bn->flag = (small>=0?1:-1);
	bn->length = 0;
	small *= bn->flag;
	while(small)
	{
		bn->num[MAXCAPACITY-1-(bn->length++)] = small%10 + '0';
		small /= 10;
	}
}
int bigcmp(struct BigNum *bn1,struct BigNum *bn2)
{
	int i;
	if(bn1->flag!=bn2->flag)
	{
		return bn1->flag==1?-1:1;
	}
	else
	{
		if(bn1->flag==1)
		{
			if(bn1->length!=bn2->length)
			{
				return bn1->length>bn2->length?-1:1;
			}
			else
			{
				for(i=MAXCAPACITY-bn1->length;i<MAXCAPACITY;i++)
				{
					if(bn1->num[i]==bn2->num[i])
						continue;
					return bn1->num[i]>bn2->num[i]?-1:1;
				}
				return 0;
			}
		}
		else
		{
			bn1->flag=1;
			bn2->flag=1;
			i=bigcmp(bn1,bn2);
			bn1->flag=-1;
			bn2->flag=-1;
			return -i;
		}
	}
}
void bigminus(struct BigNum *bn1, struct BigNum *bn2, struct BigNum *result)
{
	int i,c;
	biginit(result);
	if(bigcmp(bn1,bn2)==1)
	{
		bigminus(bn2,bn1,result);
		result->flag=-1;
	}
	else
	{
		if(bn1->flag==-1)
		{
			bn1->flag=-1;
			bn2->flag=-1;
			bigminus(bn2,bn1,result);
			bn1->flag=1;
			bn2->flag=1;
		}
		else
		{
			if(bn2->flag==-1)
			{
				for(i=0,c=0;i<bn2->length||i<bn1->length;i++)
				{
					if(i>=bn1->length)
						result->num[MAXCAPACITY-1-i] = bn2->num[MAXCAPACITY-1-i] - '0' + c;
					else if(i>=bn2->length)
						result->num[MAXCAPACITY-1-i] = bn1->num[MAXCAPACITY-1-i] - '0' + c;
					else
						result->num[MAXCAPACITY-1-i] = bn1->num[MAXCAPACITY-1-i] - '0' + bn2->num[MAXCAPACITY-1-i] - '0' + c;
					c = result->num[MAXCAPACITY-1-i]/10;
					result->num[MAXCAPACITY-1-i] = result->num[MAXCAPACITY-1-i]%10 + '0';
				}
				if(c)
					result->num[MAXCAPACITY-1-i++] = c + '0';
				result->length = i;
			}
			else
			{
				for(i=0,c=0;i<bn1->length;i++)
				{
					if(i>=bn2->length)
						result->num[MAXCAPACITY-1-i] = bn1->num[MAXCAPACITY-1-i] - '0' - c;
					else
						result->num[MAXCAPACITY-1-i] = bn1->num[MAXCAPACITY-1-i] - bn2->num[MAXCAPACITY-1-i] - c;
					if(result->num[MAXCAPACITY-1-i]<0)
					{
						result->num[MAXCAPACITY-1-i]+=10;
						c = 1;
					}
					else
						c = 0;
					result->num[MAXCAPACITY-1-i] = result->num[MAXCAPACITY-1-i] + '0';
				}
				while(i>0&&result->num[MAXCAPACITY-i]=='0')
					i--;
				result->length = i;
			}
		}
		result->flag = 1;
	}
}
void bigplus(struct BigNum *bn1, struct BigNum *bn2, struct BigNum *result)
{
	bn2->flag = -bn2->flag;
	bigminus(bn1,bn2,result);
	bn2->flag = -bn2->flag;
}
void bigcpy(struct BigNum *src, struct BigNum *dst)
{
	int i;
	dst->flag = src->flag;
	dst->length = src->length;
	for(i=0;i<src->length;i++)
	{
		dst->num[MAXCAPACITY-1-i] = src->num[MAXCAPACITY-1-i];
	}
}
void bigmul_onestep(struct BigNum *bn1, char n2, int offset, struct BigNum *result)
{
	int i,j,c,tmp;
	biginit(result);
	if(n2=='0')
		return;
	for(i=0;i<offset;i++)
		result->num[MAXCAPACITY-1-i]='0';
	for(j=0,c=0;j<bn1->length;j++)
	{
		tmp = (bn1->num[MAXCAPACITY-1-j]-'0') * (n2-'0') + c;
		c = tmp/10;
		result->num[MAXCAPACITY-1-i++] = tmp%10 + '0';
	}
	if(c)
		result->num[MAXCAPACITY-1-i++] = c + '0';
	result->length = i;
}
void bigmul(struct BigNum *bn1, struct BigNum *bn2, struct BigNum *result)
{
	int i;
	struct BigNum tmp1,tmp2;
	biginit(result);
	if(bn1->length==0||bn2->length==0)
		return ;
	for(i=0;i<bn2->length;i++)
	{
		bigmul_onestep(bn1,bn2->num[MAXCAPACITY-1-i],i,&tmp1);
		bigplus(result,&tmp1,&tmp2);
		bigcpy(&tmp2,result);
	}
	result->flag = bn1->flag * bn2->flag;
}
void bigsmallpow(struct BigNum *bn1, int pow, struct BigNum *result)
{
	int i;
	struct BigNum tmp;
	biginit(result);
	bigcpy(bn1,result);
	for(i=1;i<pow;i++)
	{
		bigmul(result,bn1,&tmp);
		bigcpy(&tmp,result);
	}
}
void bigmid(struct BigNum *bn1, struct BigNum *bn2, struct BigNum *result)
{
	int i,c,tmp;
	struct BigNum res;
	bigplus(bn1,bn2,result);
	biginit(&res);
	for(i=result->length,c=0;i>0;i--)
	{
		tmp = result->num[MAXCAPACITY-i] - '0' + c*10;
		c = tmp%2;
		tmp /= 2;
		res.num[MAXCAPACITY-i] = tmp + '0';
	}
	res.length = result->length;
	res.flag = result->flag;
	while(res.length&&res.num[MAXCAPACITY-res.length]=='0')
		res.length--;
	if(res.length==0)
		res.flag = 1;
	bigcpy(&res,result);
}
void biginc(struct BigNum *bn1, struct BigNum *result)
{
	struct BigNum bn2;
	biginit(&bn2);
	small2big(1,&bn2);
	bigplus(bn1,&bn2,result);
}
void bigdec(struct BigNum *bn1, struct BigNum *result)
{
	struct BigNum bn2;
	biginit(&bn2);
	small2big(1,&bn2);
	bigminus(bn1,&bn2,result);
}
void bigfloorsqrt(struct BigNum *bn, struct BigNum *result)
{
	int i,start,end,mid;
	struct BigNum tmp;
	result->flag=1;
	result->length = (bn->length + 1) / 2;
	for(i=1;i<=result->length;i++)
	{
		result->num[MAXCAPACITY-i] = '0';
	}
	for(i=result->length;i>=1;i--)
	{
		start = 0;
		end = 9;
		while(start<=end)
		{
			mid = start + (end - start)/2;
			result->num[MAXCAPACITY-i] = mid + '0';
			bigsmallpow(result,2,&tmp);
			if(bigcmp(&tmp,bn)<0)
				end = mid - 1;
			else
				start = mid + 1;
		}
		result->num[MAXCAPACITY-i] = end + '0';
	}
}
void buildnextquotient(struct BigNum *bn, char a)
{
	int i;
	for(i=bn->length;i>0;i--)
	{
		bn->num[MAXCAPACITY-i-1] = bn->num[MAXCAPACITY-i];
	}
	bn->num[MAXCAPACITY-1] = a;
	bn->length+=1;
}
void buildnextremainder(struct BigNum *bn, char a, char b)
{
	int i;
	for(i=bn->length;i>0;i--)
	{
		bn->num[MAXCAPACITY-i-2] = bn->num[MAXCAPACITY-i];
	}
	bn->num[MAXCAPACITY-2] = a;
	bn->num[MAXCAPACITY-1] = b;
	bn->length+=2;
}
void big_quick_floorsqrt(struct BigNum *bn, struct BigNum *result)
{
	int i;
	int pos;
	struct BigNum tmp,tmp1,tmp2;
	struct BigNum quotient,remainder;
	struct BigNum quotient_times_20;
	struct BigNum twenty;
	biginit(&quotient);
	biginit(&remainder);
	biginit(&tmp);
	biginit(&quotient_times_20);
	biginit(&twenty);

	small2big(20,&twenty);

	if(bn->length&1)
	{
		remainder.length = 1;
		remainder.num[MAXCAPACITY-1] = bn->num[MAXCAPACITY - bn->length];
		pos = MAXCAPACITY - bn->length + 1;
	}
	else
	{
		remainder.length = 2;
		remainder.num[MAXCAPACITY-2] = bn->num[MAXCAPACITY - bn->length];
		remainder.num[MAXCAPACITY-1] = bn->num[MAXCAPACITY - bn->length + 1];
		pos = MAXCAPACITY - bn->length + 2;
	}
	for(i=9;i>0;i--)
	{
		small2big(i*i,&tmp);
		if(bigcmp(&tmp,&remainder)!=-1)
			break;
	}
	small2big(i,&quotient);
	bigminus(&remainder,&tmp,&tmp1);
	bigcpy(&tmp1,&remainder);
	while(pos<MAXCAPACITY)
	{
		bigmul(&quotient,&twenty,&quotient_times_20);
		buildnextremainder(&remainder,bn->num[pos],bn->num[pos+1]);
		for(i=9;i>=0;i--)
		{
			small2big(i,&tmp);
			bigplus(&quotient_times_20,&tmp,&tmp1);
			bigmul(&tmp1,&tmp,&tmp2);
			if(bigcmp(&tmp2,&remainder)!=-1)
				break;
		}
		buildnextquotient(&quotient,i+'0');
		bigminus(&remainder, &tmp2, &tmp1);
		bigcpy(&tmp1,&remainder);
		pos+=2;
	}
	bigcpy(&quotient,result);
}
