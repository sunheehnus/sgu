#include<stdio.h>
struct BigNum{char num[256];int length;int flag;};
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
		printf("%c",bn->num[256-i]);
	printf("\n");
}
void small2big(int small,struct BigNum *bn)
{
	bn->flag = (small>=0?1:-1);
	bn->length = 0;
	small *= bn->flag;
	while(small)
	{
		bn->num[255-(bn->length++)] = small%10 + '0';
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
				for(i=256-bn1->length;i<256;i++)
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
						result->num[255-i] = bn2->num[255-i] - '0' + c;
					else if(i>=bn2->length)
						result->num[255-i] = bn1->num[255-i] - '0' + c;
					else
						result->num[255-i] = bn1->num[255-i] - '0' + bn2->num[255-i] - '0' + c;
					c = result->num[255-i]/10;
					result->num[255-i] = result->num[255-i]%10 + '0';
				}
				if(c)
					result->num[255-i++] = c + '0';
				result->length = i;
			}
			else
			{
				for(i=0,c=0;i<bn1->length;i++)
				{
					if(i>=bn2->length)
						result->num[255-i] = bn1->num[255-i] - '0' - c;
					else
						result->num[255-i] = bn1->num[255-i] - bn2->num[255-i] - c;
					if(result->num[255-i]<0)
					{
						result->num[255-i]+=10;
						c = 1;
					}
					else
						c = 0;
					result->num[255-i] = result->num[255-i] + '0';
				}
				while(i>0&&result->num[256-i]=='0')
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
	dst->length = src->length;
	for(i=0;i<src->length;i++)
	{
		dst->num[255-i] = src->num[255-i];
	}
}
void bigmul_onestep(struct BigNum *bn1, char n2, int offset, struct BigNum *result)
{
	int i,j,c,tmp;
	biginit(result);
	for(i=0;i<offset;i++)
		result->num[255-i]='0';
	for(j=0,c=0;j<bn1->length;j++)
	{
		tmp = (bn1->num[255-j]-'0') * (n2-'0') + c;
		c = tmp/10;
		result->num[255-i++] = tmp%10 + '0';
	}
	if(c)
		result->num[255-i++] = c + '0';
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
		bigmul_onestep(bn1,bn2->num[255-i],i,&tmp1);
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
int main()
{
	int Sa,Sb;
	struct BigNum Ba,Bb,res1,res2,result;
	biginit(&Ba);
	biginit(&Bb);
	scanf("%d %d",&Sa,&Sb);
	small2big(Sa,&Ba);
	small2big(Sb,&Bb);
	bigsmallpow(&Ba, Sb, &res1);
	bigsmallpow(&Bb, Sa, &res2);
	bigminus(&res1,&res2,&result);
	bigoutput(&result);
	return 0;
}
