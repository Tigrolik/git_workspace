from re import findall 

'''
fd = open('regex_sum_167853.txt', 'r')
s = 0
for txt in fd:
    t = findall('[0-9]+', txt);
    for j in t:
        s = s + int(j)
print s
'''

print sum( [ int(x) for x in findall('[0-9]+', open('regex_sum_167853.txt', 'r').read()) ] )

