/*
This is the program SquareRoot
It is a program for calculating square roots in GF(p)
if p is prime and p = 5 mod 6, or p = 4 mod 9, or p = 7 mod 9

It is based on exponentiation in GF(p^3)
It calculates the function S(d,b,p) mentioned in the
paper "On Calculating Square Roots in GF(p)"

The algorithm exponentiates in GF(p^3) by calculating
	x^p (mod x^3 + ax + b) where the integer a is chosen such that
	d = -(4a^3 + 27b^2) (mod p) where d is the quadratic residue
	whose square root is to be determined by the algorithm

If the polynomial x^3 + ax + b is not irreducible or if an appropriate
value for a cannot be determined, the algorithm outputs 0.  Otherwise the
algorithm will calculate a square root of d in GF(p) assuming d is a quadratic
residue and assuming that 0 < b < p.

Also a version of the Cipolla-Lehmer function presented for comparison.
*/


/* This has been changed from sqr2a14.cpp in test directory */
/* p-b has been changed to b */


#include <stdio.h>


const m = 40;
const m1 = 5;

const max = 15000;

long int inverse(long int a, long int b);
long int exp1 (long int e, long int g, long int n);
void display2a (int d1, long int h1[]);
void display2b (int d1, int t, long int h1[]);
void addp (int d1, long int h1[], long int h2[], long int h3[],
			  long int n);
void subtp (int d1, long int h1[], long int h2[], long int h3[],
			  long int n);
void multc (int d1, long int c, long int h1[], long int h3[], long int n);
void mult1 (int d1, long int h1[], long int h3[]);
void equal (int d2, int d1, long int h1[], long int h3[]);
void equal2 (int d1, long int h1[], long int h3[]);
void equal2a (int d1, long int h1[], long int h3[]);
void setzero (int d1, long int h1[]);
void multp (int d1, long int h1[], long int h2[], long int h4[],
				long int n);
void twodiv (int d1, long int h1[], int d2[], long int ans1[]);
void divide (int d1, long int h1[], long int h2[], long int h5[],
				 long int r[], long int n);
void multm (int d1, long int h1[], long int h2[], long int m[],
				long int a0[], long int n);
void exp2a (int d1, int c, long int e, long int h1[],
				long int h2[],	long int m1[], long int p);
long int sqr2a(int d1, int c, long int c1, long int b, long int e[],long int p);
long int sqr2a1 (int d1, int c, long int c1, long int b, long int p);
long int cl (int d1, int c, long int d, long int b, long int p);
long int findncr (long int p);
long int s2 (int d1, int c, long int c1, long int b, long int b2[],
				 long int e1[], long int p);




void main()

{
int d1,c;
long int t1,t2,t3,t4,t5;
long int p;
long int j;
long int c1;
long int b;
long int h2[12];
long int h3[12];
long int h10[12];
long int a2[2];
long int e1[2];
long int b2[2];


d1 = 12;
c = 7;


printf("\n \n This is the program modsqrt.c written by David S. Knight");


printf("\n \n This program calculates the values of \n (1) S(d,b,p) ");
printf("\n (2) S2(d,b,p) \n (3) CL(d,b,p)");
printf("\n \n The prime modulus p must meet one of the following criteria");
printf("\n (1) p = 5 mod 6");
printf("\n (2) p = 4 mod 9");
printf("\n (3) p = 7 mod 9");



p = 23;
b = 1;
for (j=0;j<100;j++)
{
printf("\n \n \n \n          p = %ld",p);
printf("   b = %ld",b);
printf("\n \n          Choose one of the following 4 options:");
printf("\n \n ");
printf("\n           (1) Enter 0 to change the prime p");
printf("\n           (2) Enter -1 to change b");
printf("\n           (3) Enter -2 to quit program");
printf("\n           (4) Enter a positive integer for d");
printf("\n               where d is a quadratic residue mod p");
printf("\n \n>");
scanf("%ld",&c1);
if ((c1<-2)||(c1>max))
	{
	printf("\n \n invalid input for d thus d is being set to 9");
	c1 = 9;
	}

if (c1==0)
	{
	printf("\n \n Enter a new prime >");
	scanf("%ld",&p);
	if ((p<4)||((p%2)==0)||((p%3)==0)||((p%9)==1)||(p>max))
		{
		printf("\n \n  the prime p is invalid input thus p is being set to 59");
		p = 59;
		}
	printf("\n    Enter a value for d where d is a quadratic residue mod p >");
	scanf("%ld",&c1);
	if (c1<1)
		{
		c1 = 9;
		}
	}


if (c1==-1)
	{
	printf("\n \n Enter new b  ");
	scanf("%ld",&b);
	if ((b<1)||(b>max)||((b%p)==0))
		{
		printf("\n \n  invalid input for b thus b is being set to 1");
		b = 1;
		}
	printf("\n    Enter a value for d where d is a quadratic residue mod p >");
	scanf("%ld",&c1);
	if (c1<1)
		{
		c1 = 9;
		}
	}


if (c1<-1)
	{
	printf("\n \n end of program");
	j = 100;
	}

if(c1!=-2)
	{
	printf("\n \n (1) for the function S(d,b,p)");
	c1 = c1%p;
	b = b%p;
	t1 = sqr2a1(d1,c,c1,b,p);
	printf("\n       S(%ld",c1);
	printf(",%ld",b);
	printf(",%ld)",p);
	printf(" = %ld",t1);

	printf("\n \n (2) for the function S2(d,b,p)");
	t1 = s2(d1,c,c1,b,b2,e1,p);
	printf("\n       S2(%ld",c1);
	printf(",%ld",b);
	printf(",%ld)",p);
	printf(" = %ld",t1);

    printf("\n \n");
	printf("      the cubic polynomial modulus q(x) = x^3 + %ldx + %ld",e1[0],e1[1]);


	t2 = (p+1)/3;
	t2 = (t2*t2)%p;
	t3 = (p+1)/2;
	t4 = (p-b2[0])%p;
	a2[0] = (t3*t4)%p;
	t4 = (t1*t2)%p;
	a2[1] = (t3*t4)%p;

	a2[1] = (a2[1]*b2[1])%p;


	setzero(d1,h10);
	h10[2+c] = 1;
	h10[3+c] = 0;
	h10[4+c] = 3;

	setzero(d1,h2);
	h2[3+c] = a2[1];
	h2[4+c] = a2[0];

    t5 = (p*p-1)/3;
	exp2a(d1,c,t5,h2,h3,h10,p);

	printf("\n \n        y = %ldx + ",a2[1]);
	printf("%ld",a2[0]);
	printf("\n        y^e mod q(x) = %ldx + %ld",h3[3+c],h3[4+c]);
	printf("\n        where e = (p^2-1)/3 = %ld",t5);

    if ((p%6)==1)
        {
        t1 = findncr(p);
        printf("\n         noncubic residue mod %ld",p);
        printf(" is %d",t1);
        }


	printf("\n \n");
	printf("\n \n (3) for the Cipolla-Lehmer function CL(d,b,p)");
	t1 = cl(d1,c,c1,b,p);
	printf("\n       CL(%ld",c1);
	printf(",%ld",b);
	printf(",%ld)",p);
	printf(" = %ld",t1);
	}


}


}


long int inverse(long int a, long int b)

{
long int temp;

if (a == 1) { return (1);}
else
	{
	 temp = (b - ((b * inverse(b % a , a)) / a));
	 return (temp);

	}

}

long int exp1 (long int e, long int g, long int n)

{

long int e1,sq,t;

t = 1;
sq = g;
e1 = e;
while (e1 != 0)
	{
	if ((e1 % 2) == 1)
		{
		t = (sq * t) % n;
		e1 = (e1 - 1) / 2;
		}
	else
		{
		e1 = e1 / 2;
		}
	sq = (sq * sq) % n;
	}
return(t);


}

void display2a (int d1, long int h1[])

{
int i;

printf(" ( ");
for (i=0;i<d1-1;i++)
	{
	printf("%d , ",h1[i]);
	}
printf("%d )",h1[i]);

}

void display2b (int d1, int t, long int h1[])

{
int i;

printf(" ( ");
for (i=t;i<d1-1;i++)
	{
	printf("%d , ",h1[i]);
	}
printf("%d )",h1[i]);

}

void addp (int d1, long int h1[], long int h2[], long int h3[], long int n)

{
int i;

for (i=0;i<d1;i++)
	{
	h3[i] = (h1[i] + h2[i]) % n;
	}

}

void subtp (int d1, long int h1[], long int h2[], long int h3[],
			  long int n)


{
int i;

for (i=0;i<d1;i++)
	{
	h3[i] = (h1[i] + (n - h2[i])) % n;
	}


}

void multc (int d1, long int c, long int h1[], long int h3[], long int n)

{
int i;

for (i=0;i<d1;i++)
	{
	h3[i] = (c*h1[i]) % n;
	}


}


void mult1 (int d1, long int h1[], long int h3[])

{
int i;

for (i=0;i<(d1-1);i++)
	{
	h3[i] = (h1[i+1]);
	}
h3[d1-1] = 0;


}


void equal (int d2, int d1, long int h1[], long int h3[])

{
int i;

for (i=d2;i<d1;i++)
	{
	h3[i] = h1[i];
	}


}


void equal2 (int d1, long int h1[], long int h3[])

{
int i;

for (i=0;i<d1;i++)
	{
	h3[i] = 0;
	h3[d1+i] = h1[i];
	}


}


void equal2a (int d1, long int h1[], long int h3[])

{
int i;

for (i=0;i<d1;i++)
	{
	h3[i] = h1[d1+i];
	}


}


void setzero (int d1, long int h1[])

{
int i;

for (i=0;i<d1;i++)
	{
	h1[i] = 0;
	}


}


void multp (int d1, long int h1[], long int h2[], long int h4[],
				long int n)

{
int i;
int t1;
long int c;
long int temp1[2*12];
long int temp2[2*12];
long int temp3[2*12];
long int temph2[2*12];
long int total[2*12];

setzero(2*d1,temp1);
setzero(2*d1,total);
equal2(d1,h1,temph2);

for (i=0;i<d1;i++)
	{
	t1 = (d1-1)-i;
	c = h2[t1];
	multc(2*d1,c,temph2,temp2,n);
	addp(2*d1,temp2,total,temp3,n);
	equal(0,2*d1,temp3,total);
	mult1(2*d1,temph2,temp1);

	equal(0,2*d1,temp1,temph2);
	}
equal(0,2*d1,total,h4);

}



void twodiv (int d1, long int h1[], int d2[], long int ans1[])

{
int i;

d2[0] = -1;
for (i=0;i<d1;i++)
	{
	if (h1[(d1-1)-i] != 0)
		{
		d2[0] = i;
		ans1[0] = h1[(d1-1)-i];
		}
	}
ans1[1] = 0;


}



void divide (int d1, long int h1[], long int h2[], long int h5[],
				 long int r[], long int n)

{
int i;
int c1;
int d2[1];
int d3[1];
long int c;
long int ans1[2];
long int temp1[2*12];
long int temp2[2*12];
long int temph1[2*12];
long int temph2[2*12];

c1 = 0;
setzero(2*d1,temph1);
setzero(2*d1,temph2);
setzero(2*d1,temp1);
setzero(2*d1,temp2);
setzero(d1,h5);
twodiv(d1,h2,d2,ans1);
twodiv(2*d1,h1,d3,ans1);
equal(0,2*d1,h1,temph1);


while (((d2[0] < d3[0]) || (d2[0] == d3[0])) && (c1 < 200) && (d3[0] > 0))
	{

	equal2(d1,h2,temph2);

	for (i=0;i<(d3[0]-d2[0]);i++)
		{
		mult1(2*d1,temph2,temp1);

		equal(0,2*d1,temp1,temph2);

		}
	c = ans1[0];
	h5[((2*d1-1)-(d3[0]-d2[0]))] = c;
	multc(2*d1,c,temph2,temp1,n);

	subtp(2*d1,temph1,temp1,temp2,n);
	equal(0,2*d1,temp2,temph1);

	twodiv(2*d1,temph1,d3,ans1);
	c1 = c1 + 1;

	}

equal2a(d1,temph1,r);
if (c1 > 197)
	{
	printf("\n \n error in divide c1 = %d",c1);
	}


}


void multm (int d1, long int h1[], long int h2[], long int m[],
				long int a0[], long int n)

{
long int temp1[24];
long int temp2[24];
long int temp3[12];

setzero(2*d1,temp1);
setzero(2*d1,temp2);
setzero(d1,temp3);
multp(d1,h1,h2,temp1,n);


divide(d1,temp1,m,temp2,temp3,n);

equal(0,d1,temp3,a0);



}




void exp2a (int d1, int c, long int e, long int h1[], long int h2[],
				long int m1[], long int p)

{

long int e1;
long int sq[12];
long int t[12];
long int t1[12];

setzero(d1,sq);
setzero(d1,t);
setzero(d1,t1);
t[4+c] = 1;
equal(0,d1,h1,sq);
e1 = e;
while (e1 != 0)
	{
	if ((e1 % 2) == 1)
		{
		multm(d1,sq,t,m1,t1,p);
		equal(0,d1,t1,t);
		e1 = (e1 - 1) / 2;
		}
	else
		{
		e1 = e1 / 2;
		}
	multm(d1,sq,sq,m1,t1,p);
	equal(0,d1,t1,sq);
	}
equal(0,d1,t,h2);


}



long int sqr2a(int d1, int c, long int c1, long int b, long int e[], long int p)

{
long int b2;
long int t1,t2,t3,t4,t5;
long int h2[12];
long int h3[12];
long int h10[12];


b2 = (b*b)%p;
t1 = ((p%4)*p-1)/4;
t2 = c1;
t5 = (27*b2)%p;
t3 = ((t2+t5)*t1)%p;
t4 = exp1((2*p-1)/3,t3,p);

if ((p%3)==1)
	{
	t5 = (p-1)/3;
	t1 = t5%3;
	t1 = 3-t1;
	t1 = (t1*t5+1)/3;
	t4 = exp1(t1,t3,p);
	t2 = exp1(t5,t3,p);
	if (t2!=1)
		{
		t4 = 0;
		}
	}


setzero(d1,h10);
h10[1+c] = 1;
h10[2+c] = 0;
h10[3+c] = t4;
h10[4+c] = b;

setzero(d1,h2);
h2[3+c] = 1;
h2[4+c] = 0;

exp2a(d1,c,p,h2,h3,h10,p);

e[0] = t4;
e[1] = b;

t2 = h3[2+c];
t1 = 0;
if (t2 != 0)
	{
	t1 = inverse(t2,p);
	}


t1 = (3*t1*t4)%p;

return(t1);

}



long int sqr2a1 (int d1, int c, long int c1, long int b, long int p)

{
long int b2;
long int t1,t2,t3,t4,t5;
long int h2[12] = {0};
long int h3[12] = {0};
long int h10[12] = {0};


b2 = (b*b)%p;
t1 = ((p%4)*p-1)/4;
t2 = c1;
t5 = (27*b2)%p;
t3 = ((t2+t5)*t1)%p;
t4 = exp1((2*p-1)/3,t3,p);

if ((p%3)==1)
	{
	t5 = (p-1)/3;
	t1 = t5%3;
	t1 = 3-t1;
	t1 = (t1*t5+1)/3;
	t4 = exp1(t1,t3,p);
	t2 = exp1(t5,t3,p);
	if (t2!=1)
		{
		t4 = 0;
		printf("\n \n      No solution for a can be determined thus output is 0");
		}
	}


setzero(d1,h10);
h10[1+c] = 1;
h10[2+c] = 0;
h10[3+c] = t4;
h10[4+c] = b;

setzero(d1,h2);
h2[3+c] = 1;
h2[4+c] = 0;

exp2a(d1,c,p,h2,h3,h10,p);

if (h10[3+c]!=0)
    {
    printf("\n \n      the cubic polynomial modulus q(x) = x^3 + %ldx + %ld",h10[3+c],h10[4+c]);
    printf("\n       the value of x^%d mod q(x)  = ",p);
    printf("%dx^2 + %dx + %d",h3[2+c],h3[3+c],h3[4+c]);

    }


t2 = h3[2+c];
t1 = 0;
if (t2 != 0)
	{
	t1 = inverse(t2,p);
	}



t1 = (3*t1*t4)%p;



return(t1);

}




long int cl (int d1, int c, long int d, long int b, long int p)

{
long int b2;
long int t1,t2,t4;
long int h2[12] = {0};
long int h3[12] = {0};
long int h10[12] = {0};

b2 = (b*b)%p;
t1 = (4*d)%p;
t1 = p-t1;
t2 = (b2+t1)%p;
t4 = exp1((p-1)/2,t2,p);

if ((t4==1)||(t4==0))
	{
	b2 = 0;
	}
if ((t4!=1)&&(t4!=0))
	{
	b2 = 1;
	}


setzero(d1,h10);
h10[2+c] = 1;
h10[3+c] = p-b;
h10[4+c] = d;

setzero(d1,h2);
h2[3+c] = 1;
h2[4+c] = 0;

exp2a(d1,c,(p+1)/2,h2,h3,h10,p);

printf("\n \n      the quadratic polynomial modulus q(x) = x^2 + %ldx + %ld",h10[3+c],h10[4+c]);
printf("\n       the value of x^((%d+1)/2) mod q(x)  = ",p);
printf("%dx + %d",h3[3+c],h3[4+c]);

t2 = h3[4+c];
t1 = (t2*b2)%p;

return(t1);

}


long int findncr (long int p)

{
long int k;
long int t1,t2,t3,t4;

t1 = (p-1)/3;
t4 = 1;
for(k=2;k<51;k++)
	{
	t2 = exp1(t1,k,p);
	t3 = (t2*t2+t2+1)%p;
	if ((t2!=0)&&(t2!=1)&&(t3==0))
		{
		t4 = k;
		k = 101;
		}
	}

return(t4);

}



long int s2 (int d1, int c, long int c1, long int b, long int b2[],
				 long int e1[], long int p)

{
long int t1,t2,t3,t4,t5,t6;
long int e[2];

b2[0] = b;
b2[1] = 1;
if ((p%6)==5)
	{
	t1 = sqr2a(d1,c,c1,b,e,p);
	e1[0] = e[0];
	e1[1] = e[1];
	}

if ((p%6)==1)
	{
	t1 = findncr(p);
	t2 = sqr2a(d1,c,c1,b,e,p);
	if (t2!=0)
		{
		b2[0] = b;
		b2[1] = 1;
		e1[0] = e[0];
		e1[1] = e[1];
		}

	t5 = (c1*t1)%p;
	t5 = (t1*t5)%p;
	t6 = (b*t1)%p;
	t3 = sqr2a(d1,c,t5,t6,e,p);
	if (t3!=0)
			{
			b2[0] = t6;
			b2[1] = t1;
			e1[0] = e[0];
			e1[1] = e[1];
			}

	t5 = (t1*t5)%p;
	t5 = (t1*t5)%p;
	t6 = (t6*t1)%p;
	t4 = sqr2a(d1,c,t5,t6,e,p);
	if (t4!=0)
		{
		b2[0] = t6;
		b2[1] = (t1*t1)%p;
		e1[0] = e[0];
		e1[1] = e[1];
		}

	t5 = exp1(p-2,t1,p);
	t6 = (t5*t5)%p;

	t5 = (t5*t3)%p;
	t6 = (t6*t4)%p;

	t1 = (t5+t6)%p;
	t1 = (t1+t2)%p;
	}

return(t1);

}


