from math import tan, pi
def polygonArea(n, s):
    '''
        Compute the area of a polygon with number of sides (n) and
        side length (s)
    '''
    return 0.25 * n * s * s / tan(pi / n)

n = 7
s = 3
p = 4
print 'Area of', str(n) + '-sided polygon with side length', s, 'equals to', round(polygonArea(n, s), p)
