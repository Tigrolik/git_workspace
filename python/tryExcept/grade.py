# testing try-except block
try:
    inp = raw_input('Enter score: ')
    n = float(inp)
except:
    print 'Error: please enter a valid numeric value in range [0, 1]'
    quit()

if n > 1:
    print 'Error: the value should not be greater than 1'
elif n >= 0.9:
    print 'A'
elif n >= 0.8:
    print 'B'
elif n >=  0.7:
    print 'C'
elif n >= 0.6:
    print 'D'
elif n >= 0:
    print 'F'
else:
    print 'Error: the value cannot be negative'
