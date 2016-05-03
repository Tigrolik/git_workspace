# check if the number is prime 
from math import sqrt
def isPrime(n):
    m = int(sqrt(n))
    P = range(0, m + 1)
    b = True;
    P[0::2] = [0] * int(len(P) / 2 + 1);
    print P
    if (n == 2):
        print n,"is a prime number"
    elif (n % 2 == 0):
        print n,"is not a prime number"
    else:
        for i in range(3, m+1, 2):
            if P[i]:
                if (n % i):
                    for j in range(i*i, m+1, i):
                        P[j] = 0
                else:
                    b = False
                    print n,"is not a prime number"
                    break;
    if b:
        print n,"is a prime number"
    return b

n = int(input("Enter an integer number greater than one: "))
isPrime(n)
