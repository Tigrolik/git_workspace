import urllib
import json

while True:
    address = raw_input('Enter location: ')
    if len(address) < 1 : break

    sumv = 0
    for i in json.loads(urllib.urlopen(address).read())['comments']:
        sumv += int(i['count'])
    print sumv
