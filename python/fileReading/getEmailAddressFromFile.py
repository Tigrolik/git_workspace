#fname = raw_input("Enter file name: ")
#if len(fname) < 1 : fname = "mbox-short.txt"

fh = open('mbox-short.txt')
count = 0
for txt in fh:
	if txt.startswith('From:'):
#		x = txt.split()
		print txt.split()[1]
		count += 1

print "There were", count, "lines in the file with From as the first word"
