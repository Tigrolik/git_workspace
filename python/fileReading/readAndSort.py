#fname = raw_input("Enter file name: ")
fh = open('romeo.txt')
lst = list()
for line in fh:
    for w in line.split():
        if not w in lst:
            lst.append(w)

lst.sort()
print lst 
