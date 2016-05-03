import urllib
import xml.etree.ElementTree as ET

while True:
    address = raw_input('Enter location: ')
    if len(address) < 1 : break

    params = urllib.urlencode({'find': 'count'})
    print 'Retrieving', address
    uh = urllib.urlopen(address + '?', params)
    data = uh.read()
    print 'Retrieved',len(data),'characters'
    print data
    tree = ET.fromstring(data)

    sumv = 0
    results = tree.findall('.//count')
    print len(results)
    for r in results:
        sumv += int(r.text)
    print sumv
