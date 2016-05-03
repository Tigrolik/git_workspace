# implementing Sieve of Eratosthenes algorithm
from math import sqrt
n = int(input("Enter an integer number greater than one: "))
# initialize vector for storing prime numbers
P = range(0, n + 1)
# go through potential numbers
for i in range(2, int(sqrt(n))+1):
    if P[i]:
        for j in range(i*i, n+1, i):
            P[j] = 0
# few ways to remove zeros from the array
# P = filter(lambda a: a, P)
P.remove(1)
P = [x for x in P if x]
print P
