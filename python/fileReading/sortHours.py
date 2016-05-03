fh = open('mbox-short.txt')

d= dict()

for txt in fh:
    if txt.startswith('From '):
        w = (txt.split()[5]).split(':')[0]
        d[w] = d.get(w, 0) + 1
        print w

for k, v in sorted(d.items()):
    print k, v
