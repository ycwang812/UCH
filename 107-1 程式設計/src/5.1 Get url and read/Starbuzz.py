import urllib.request

page = urllib.request.urlopen("http://beans-r-us.appspot.com/prices.html")
text = page.read().decode("utf8")

print(text)