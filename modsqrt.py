""" This contains two different functions for calculating square roots
modulo a prime.  This first is sqrt1(a,p) which calculates a value for
x where x^2 = a (mod p) where p is a prime and where the variable a is a
quadratic residue in GF(p).  The function sqrt1(a,p) is an implementation of
the Cipolla-Lehmer algorithm.  The second square root function sqrt2(a,p) is
is a different square root algorithm based on exponentiation in GF(p^3).
sqrt1(a,p) is based primarily on the function CL(c,b,p) and sqrt2(a,p) is
based primarily on the function S(d,b,p).

More information on these two functions can be found in the paper
"On Calculating Square Roots in GF(p)" written by David S. Knight
which is available at www.arxiv.org
"""


""" This calculates g^e (mod n) for integers e,g, and n """
def exp1(e,g,n):
    t = 1
    sq = g
    e1 = e
    while(e1!=0):
        if (e1%2)==1:
            t = (sq*t)%n
            e1 = (e1-1)//2
        else:
            e1 = e1//2
        sq = (sq*sq)%n
    return(t)


""" This multiplies two polynomials in GF(p^2)
that is it calculates c(x) = a(x)*b(x) <mod q(x)>
where a(x) = a[0]x + a[1] and b(x) = b[0]x + b[1] and
q(x) = x^2 + q[0]x + q[1]
"""
def mult2(a,b,q,n):
    t1 = (a[0]*b[1])%n
    t2 = (a[1]*b[0])%n
    t1 = (t1+t2)%n
    t2 = (a[1]*b[1])%n
    t3 = ((n-1)*q[0])%n
    t4 = ((n-1)*q[1])%n
    t5 = (a[0]*b[0])%n
    t3 = (t5*t3)%n
    t4 = (t5*t4)%n
    c = [(t1+t3)%n , (t2+t4)%n]
    return(c)


""" This multiplies two polynomials in GF(p^3)
that is it calculates c(x) = a(x)*b(x) <mod q(x)>
where a(x) = a[0]x^2 + a[1]x + a[2] and b(x) = b[0]x^2 + b[1]x + b[2]
and q(x) = x^3 + q[0]x^2 + q[1]x + q[2]
"""
def mult3(a,b,q,n):
    t1 = (a[0]*b[2])%n
    t2 = (a[1]*b[1])%n
    t3 = (a[2]*b[0])%n
    t1 = (t1+t2)%n
    t1 = (t1+t3)%n
    t2 = (a[1]*b[2])%n
    t3 = (a[2]*b[1])%n
    t2 = (t2+t3)%n
    t3 = (a[2]*b[2])%n
    t4 = (a[0]*b[1])%n
    t5 = (a[1]*b[0])%n
    t4 = (t4+t5)%n
    t5 = (a[0]*b[0])%n
    t6 = ((n-1)*q[2])%n
    t6 = (t4*t6)%n
    t7 = (q[0]*q[2])%n
    t7 = (t5*t7)%n
    t6 = (t6+t7)%n
    t10 = (t6+t3)%n
    t6 = ((n-1)*q[1])%n
    t6 = (t4*t6)%n
    t7 = (q[0]*q[1])%n
    t8 = ((n-1)*q[2])%n
    t7 = (t7+t8)%n
    t7 = (t5*t7)%n
    t6 = (t6+t7)%n
    t11 = (t6+t2)%n
    t6 = ((n-1)*q[0])%n
    t6 = (t4*t6)%n
    t7 = (q[0]*q[0])%n
    t8 = ((n-1)*q[1])%n
    t7 = (t7+t8)%n
    t7 = (t5*t7)%n
    t6 = (t6+t7)%n
    t12 = (t6+t1)%n
    c = [t12 , t11, t10]
    return(c)

    
""" exp2 exponentiates in GF(p^2) by calculating (g(x))^e mod <q(x)> """
def exp2(e,g,q,n):
    t = [0,1]
    sq = g
    e1 = e
    while(e1!=0):
        if (e1%2)==1:
            t = mult2(sq,t,q,n)
            e1 = (e1-1)//2
        else:
            e1 = e1//2
        sq = mult2(sq,sq,q,n)
    return(t)


""" exp3 exponentiates in GF(p^3) by calculating (g(x))^e mod <q(x)> """
def exp3(e,g,q,n):
    t = [0,0,1]
    sq = g
    e1 = e
    while(e1!=0):
        if (e1%2)==1:
            t = mult3(sq,t,q,n)
            e1 = (e1-1)//2
        else:
            e1 = e1//2
        sq = mult3(sq,sq,q,n)
    return(t)
            

""" This is the main function used in the Cipolla-Lehmer algorithm for
calculating square roots mod a prime p """
def CL(c,b,p):
    t1 = (b*b)%p
    t2 = (4*c)%p
    t2 = (p-t2)%p
    g = (t1+t2)%p
    e = (p-1)//2
    h = exp1(e,g,p)
    s = 1
    if ((h==0) or (h==1)):
        s = 0
    e = e+1
    t1 = ((p-1)*b)%p
    t2 = c%p
    q = [t1,t2]
    a = [1,0]
    b = exp2(e,a,q,p)
    t = s*b[1]
    return(t)


""" This algorithm calculates cube roots mod p assuming p is a prime
that = 5 ( mod 6) """
def cuberoot(g,p):
    e = (2*p-1)//3
    t = exp1(e,g,p)
    return(t)


""" This determines if a cubic polynomial q(x) is irreducible in GF(p) """
def ir(q,p):
    t = 1
    a = [0,1,0]
    b = exp3(p-1,a,q,p)
    a = exp3(p+1,b,q,p)
    b = exp3(p,a,q,p)
    if (b==[0,0,1]):
        t = 0
    return(t)


""" This calculates the multiplicative inverse of a in GF(p) """
def inverse(a,p):
    t = exp1(p-2,a,p)
    return(t)


""" This is the main function used in the GF(p^3) algorithm for
calculating square roots mod a prime p where p = 5 (mod 6)"""
def S(d,b,p):
    if (p<4):
        p = 2
    t3 = (p%6)
    if (t3!=5):
        print ("error in S function p should = 5 mod 6")
    t = (b*b)%p
    t = (27*t)%p
    t = (d+t)%p
    t1 = 4-(p%4)
    t1 = (t1*p+1)//4
    t1 = ((p-1)*t1)%p
    t = (t*t1)%p
    a = cuberoot(t,p)
    q = [0,a,b]
    g = [0,1,0]
    s = ir(q,p)
    c = exp3(p,g,q,p)
    t1 = (3*a)%p
    t2 = inverse(c[0],p)
    t = (t1*t2)%p
    t = s*t
    if (t3!=5):
        t=0
    return(t)


""" This is the Cipolla-Lehmer algorithm. It calculates a square root
of c mod p assuming c is a quadratic residue mod p where p is a prime > 2"""
def sqrt1(c,p):
    m1 = 50
    t = 0
    c = c%p
    for i in range(m1):
        y = CL(c,((i+1)%p),p)
        t1 = (y*y)%p
        if (t1==c):
            t = y
            break
    return(t)


""" This is GF(p^3) square root algorithm.  It calculates a square root
of d mod p assuming d is a quadratic residue in GF(p) and p is a prime
where p = 5 (mod 6). """
def sqrt2(d,p):
    m2 = 50
    t = 0
    d = d%p
    if ((p%6)==5):
        for i in range(m2):
            y = S(d,(i+1)%p,p)
            t1 = (y*y)%p
            if (t1==d):
                t = y
                break
    return(t)


""" Examples """

""" First example
p is any odd prime and c is any quadratic residue mod p """
p = 101
c = 20
t = sqrt1(c,p)
print ("Using the Cipolla-Lehmer algorithm which is based on the")
print ("function CL(c,b,p) the square root of ",c," mod ",p," is ",t)
print ()       

""" Second example
p is prime such that p = 5 mod 6 and d is any quadratic residue mod p """
p = 53
d = 11
t = sqrt2(d,p)
print ("Using the GF(p^3) square root algorithm which is based on the")
print ("function S(d,b,p) the square root of ",d," mod ",p," is ",t)




