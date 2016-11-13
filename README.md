Number theory
=============


This contains algorithms for calculating square roots modulo a prime *p* using methods described in the paper
"On Calculating Square Roots in *GF(p)*" 


**modsqrt.py**

This contains two different methods of calculating square roots in *GF(p)*: the Cipolla-Lehmer algorithm and the *GF(p<sup>3</sup>)* square root algorithm.  The four main functions in modsqrt.py are the following:

**CL(c,b,p)** 

This function is the Cipolla-Lehmer algorithm for calculating the square root of *c mod p* assuming that *c* is a quadratic residue, that *p* is any prime *> 3* and that *0 < b < p* or it returns the value of *0*.  If the quadratic polynomial selected by the algorithm is irreducible, it will return a square root of *c mod p* otherwise it will return *0*.

        
**S(d,b,p)**

This is the *GF(p<sup>3</sup>)* square root algorithm that calculates the square root of *d mod p* assuming that *d* is a quadratic residue, that *p* is prime *= 5 mod 6*, and that *0 < b < p* and that the cubic polynomial selected by the algorithm is irreducible, otherwise it returns the value of *0*.  This algorithm is based on exponentiating in *GF(p<sup>3</sup>)* using the irreducible cubic polynomial *x<sup>3</sup> + ax + b* where *a* is chosen such that *d = -(4a<sup>3</sup> + 27b<sup>2</sup>) mod p*.
        
**sqrt1(c,p)**
  
This function calculates the square root of *c mod p* assuming *p > 3* by calling the function *CL(c,b,p)* until an irreducible quadratic polynomial is found.
        
**sqrt2(d,p)**
  
This function calculates a square root of *d mod p* assuming *p = 5 mod 6* by calling *S(d,b,p)* until an irreducible cubic polynomial is found.


**cubicsqrt.py**

This is a deterministic algorithm for calculating the square root of the discriminant of a cubic polynomial that is irreducible *mod p*.  The two main functions in cubicsqrt.py are:

**ds(q,p)**

This determines the discriminant *d mod p* of the cubic polynomial *q(x) = x<sup>3</sup> + q[0]x<sup>2</sup> + q[1]x + q[2]*.

**S3(q,p)**

This function uses the *GF(p<sup>3</sup>)* square root algorithm to deterministically calculate the square root of *d mod p* where *d* is the discriminant of the cubic polynomial *q(x) = x<sup>3</sup> + q[0]x<sup>2</sup> + q[1]x + q[2]* in *O(log<sup>3</sup>p)* time for *p = 5 mod 6* where *p* is the prime modulus.

**cubicreciprocity.py**

This program can be used to verify the correctness of the cubic reciprocity identity in the paper "On Calculating Square Roots in *GF(p)*" which is listed as conjecture 7.  The main function is CubicReciprocity(x,y,q) which checks the correctness of a cubic reciprocity identity for two primes *p* and *q* where *p = x<sup>2</sup> + xy + y<sup>2</sup>* for positive integers *x* and *y* and where *q = 5 mod 6*.

**cubicreciprocity2.py**

This is an improved version of cubicreciprocity.py since the value of the prime *q* in the function CubicReciprocity(x,y,q) can be equal to *5 mod 6* as in cubicreciprocity.py but also generalizes to the case where *q = 1 mod 6*.

**modsqrt21.py**

This is the newest version of modsqrt.py and has the following added functions:

(1) *verify(a,b,p)* This function can be used to verify the correctness of conjecture 4 in the paper "On Calculating Square Roots in *GF(p)*"

(2) *sqrt2(d,p)* and *S(d,b,p)* have been improved to work in the cases *p = 4 mod 9* or *p = 7 mod 9* in addition to working in the case that *p = 5 mod 6* where *p* refers to the prime modulus.

(3) *sqrt4(d,p)* and *S4(d,b,p)* have been added.  These are improved versions of *sqrt2(d,p)* and *S(d,b,p)* respectively and work in all cases for *p = 1 mod 6* as well as *p = 5 mod 6*.  Unlike *sqrt2(d,p)*, *sqrt4(d,p)* while calculating the modular square root of a quadratic residue *d mod p* avoids having to calculate cube roots which improves the efficiency if *p = 1 mod 6*.
