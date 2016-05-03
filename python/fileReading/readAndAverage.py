fname = raw_input('Enter a file name: ')
try:
    fh = open(fname, 'r')
except:
    print 'Wrong file name'
    quit()

check_str = 'X-DSPAM-Confidence:'
x = len(check_str)
tot = 0
i = 0
for txt in fh:
    if txt.startswith(check_str):
        i += 1
        tot += float(txt[x:].strip())
print tot / i
