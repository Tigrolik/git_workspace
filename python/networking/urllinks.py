import urllib
from BeautifulSoup import BeautifulSoup

url = raw_input('Enter - ')
w = int(raw_input('Enter position: '))
for j in range(0, int(raw_input('Enter count: '))):
    i = 0
    html = urllib.urlopen(url).read()
    soup = BeautifulSoup(html)
    tags = soup('a')
    for tag in tags:
        i += 1
        if i == w:
            url = tag.get('href', None)
            break
print url
