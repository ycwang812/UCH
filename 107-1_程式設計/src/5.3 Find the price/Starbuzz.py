import urllib.request

page = urllib.request.urlopen("http://beans-r-us.appspot.com/prices.html")
text = page.read().decode("utf8")

where = text.find(">$")

start_of_price = where + 2
end_of_price = start_of_price + 4

price = text[start_of_price:end_of_price]

print(price)