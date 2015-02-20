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

This function uses the *GF(p<sup>3</sup>)* square root algorithm to deterministically calculate the square root of *d mod p* where *d* is the discriminant of the cubic polynomial *q(x) = x<sup>3</sup> + q[0]x<sup>2</sup> + q[1]x + q[2]* in *O(log<sup>3</sup>p)* time where *p* is a prime such that *p = 5 mod 6*.
