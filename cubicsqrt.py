""" This is a deteministic O(log^3 p) algorithm for calculating the
modular square root of the discriminant d mod a prime p of a cubic polynomial
provided that cubic polynomial is irreducible mod p

More information can be found in the paper
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



""" This determines the value of the discriminant d mod p of
the cubic polynomial q(x) where q(x) = x^3 + q[0]x+2 + q[1]x + q[2]
"""
def ds(q,p):
    b = q[0]
    c = q[1]
    d = q[2]
    t1 = (18*b)%p
    t2 = (c*d)%p
    s1 = (t1*t2)%p
    t1 = (b*b)%p
    t2 = (b*d)%p
    t3 = (t1*t2)%p
    t1 = (4*t3)%p
    s2 = ((p-1)*t1)%p
    t1 = (b*c)%p
    s3 = (t1*t1)%p
    t1 = (c*c)%p
    t2 = (c*t1)%p
    t3 = (4*t2)%p
    s4 = ((p-1)*t3)%p
    t1 = (d*d)%p
    t2 = (27*t1)%p
    s5 = ((p-1)*t2)%p
    t1 = (s1+s2)%p
    t2 = (s3+s4)%p
    t1 = (t1+t2)%p
    t1 = (t1+s5)%p
    return(t1)



def S3(q,p):
    t1 = 0
    if (ir(q,p)==0):
        print("error in S3 function")
        print("the polynomial q(x) is not irreducible mod",p)
    if (ir(q,p)==1):
        g = [0,1,0]
        t = exp3(p,g,q,p)
        c2 = t[0]
        t1 = (q[0]*q[0])%p
        t2 = (3*q[1])%p
        t2 = ((p-1)*t2)%p
        t1 = (t1+t2)%p
        t2 = inverse(c2,p)
        t1 = (t1*t2)%p
    return(t1)
          
     

""" Examples """

""" First example
p is any odd prime and c is any quadratic residue mod p """
p = 41
q = [1,2,7]
t = S3(q,p)
d = ds(q,p)
print ("For the polynomial x^3 + {0}x^2 + {1}x + {2}".format(q[0],q[1],q[2]))
print ("the discriminant d =",d,"mod p where p =",p)
print ("Using the GF(p^3) square root algorithm the square root of")
print ("the discriminant is",t,"mod",p)
print ()



""" Second example """
p = 101
q = [73,27,87]
t = S3(q,p)
d = ds(q,p)
print ("For the polynomial x^3 + {0}x^2 + {1}x + {2}".format(q[0],q[1],q[2]))
print ("the discriminant d =",d,"mod p where p =",p)
print ("Using the GF(p^3) square root algorithm the square root of")
print ("the discriminant is",t,"mod",p)

