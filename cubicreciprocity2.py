from modsqrt21 import *
 
""" This function checks the validity of the Cubic Reciprocity conjecture
in the paper "On Calculating Square Roots in GF(p)" written by David S. Knight
This conjecture is listed as Conjecture 7 in section 5.2 of that paper.
This considers the case q = 5 mod 6 mentioned in that paper but also
generalizes to the case q = 1 mod 6 which wasn't mentioned in that paper.
The input is x,y, and q where x^2 + xy + y^2 = p where p is a prime and q is
any prime such that q > 3 and gcd(x^2-y^2,q) = 1 """
def CubicReciprocity(x,y,q):
    if (x%3==2) and (y%3==1):
        x,y = y,x
    if (y%3==0):
        x,y = y,x
    p = x**2+x*y+y**2
    t1 = is_prime(q)
    t2 = is_prime(p)
    if (t1==False) or (q<5):
        print("\n \n error in CubicReciprocity q must be a prime > 3")
    if (t2==False) or (p%6!=1):
        print("\n \n error in CubicReciprocity p must be prime = 1 mod 6")
    t1 = abs(x**2-y**2)
    t1 = t1%q
    if (t1==0):
        print("\n \n error in CubicReciprocity x^2 = y^2 (mod q)")
    print()
    print("x = {0}  y = {1}  p = x^2 + xy + y^2 = {2}  q = {3}".format(x,y,p,q))
    d = 81*(x+y)**2
    d = d%q
    b = (y+(q-x))%q
    s1 = S4(d,b,q)
    s2 = 9*(x+y)
    s2 = s2%q
    t1 = exp1((p-1)//3,q,p)
    t2 = inverse(y,p)
    t2 = x*t2%p
    print("\n \n",s1,s2,t1,t2)
    print("\n d = {0}  b = {1}  q = {2}".format(d,b,q))
    print("\n d = (81*(x+y)^2) mod q =",d)
    print(" b = (y-x) mod q =",b)
    print("\n S({0},{1},{2}) = {3}".format(d,b,q,s1))
    print(" 9(x+y) mod q = {0} mod {1} = {2}".format(9*(x+y),q,s2))
    print(" q^((p-1)/3) mod p  =",t1)
    print(" (x)(y^-1) mod p =",t2)
    t3 = t2**2%p
    c1 = 0
    if (s1==0):
        c1 = 0
    if (s1==s2):
        c1 = 1
    if (s1==(q-s2)):
        c1 = 2
    c2 = 0
    if (t1==1):
        c2 = 0
    if (t1==t2):
        c2 = 1
    if (t1==t3):
        c2 = 2
    if (x%3==1):
        c3 = 0
    if (x%3==0) and (q%3==1):
        c3 = ((q-1)//3)%3
        c3 = 2*c3%3
    if (x%3==0) and (q%3==2):
        c3 = ((q+1)//3)%3
    print("\n c1 = {0}  c2 = {1}  c3 = {2}".format(c1,c2,c3))
    print()
    t = False
    t1 = (c1+c3)%3
    if (t1==c2):
        t = True
    return(t)

def message1(t1):
    if (t1==True):
        print("The cubic reciprocity identity which is conjecture 7 in the paper")
        print("'On Calculating Square Roots in GF(p)' is correct in this case")
        print("since (c1+c3) = c2 (mod 3)")
    else:
        print("Either conjecture 7 is false or the input was invalid.")    
            

# Example 1
x,y = 1,5
q = 53
p = x**2+x*y+y**2
print("\n\n      Example 1  q = {0}  p = {1}".format(q,p))
t1 = CubicReciprocity(x,y,q)
message1(t1)

# Example 2
print("\n\n")
x,y = 7,12
q = 101
p = x**2+x*y+y**2
print("\n\n      Example 2  q = {0}  p = {1}".format(q,p))
t2 = CubicReciprocity(x,y,q)
message1(t2)

# Example 3
print("\n\n")
x,y = 3,8
q = 79
p = x**2+x*y+y**2
print("\n\n      Example 3  q = {0}  p = {1}".format(q,p))
t3 = CubicReciprocity(x,y,q)
message1(t3)

# Example 4
print("\n\n")
x,y = 6,7
q = 97
p = x**2+x*y+y**2
print("\n\n      Example 4  q = {0}  p = {1}".format(q,p))
t4 = CubicReciprocity(x,y,q)
message1(t4)

# Example 5
print("\n\n")
x,y = 1,8
q = 61
p = x**2+x*y+y**2
print("\n\n      Example 5  q = {0}  p = {1}".format(q,p))
t5 = CubicReciprocity(x,y,q)
message1(t5)

