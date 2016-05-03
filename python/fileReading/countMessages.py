name = raw_input('Enter file:')
if len(name) < 1 : name = 'mbox-short.txt'
handle = open(name)

check_str = 'From:'
str_len = len(check_str)

d = dict()

for txt in handle:
    if txt.startswith(check_str):
        s = txt.split().[1]
        d[s] = d.get(s, 0) + 1

count = 0
s = 'a'
for k,v in d.items():
    if v > count:
        count = v
        s = k
print s,count
