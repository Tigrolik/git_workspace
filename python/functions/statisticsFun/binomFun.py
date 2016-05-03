# script to calculate the propability of event happenning at least
# m times out of n (m > n)

# factorial recursive function
def f(n):
    if (n == 0) or (n == 1):
        return 1
    elif (n > 1):
        return n * f(n - 1)
    else:
        # numbers below zero are fed to the function as positive
        # values and the result is given back with the minus sign
        return -f(-n)

# binomial function (probability mass function)
def binomFun(n, m, p):
    return  p ** m * (1 - p) ** (n - m) * f(n) / (f(m) * f(n - m))

s = 0.0;
n = 35;
m = 11;
p = 0.1;

for j in range(m, n + 1):
    s += binomFun(n, j, p) 

print s
