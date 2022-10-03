import urllib.request
import time
import facebook

access_token = "EAAFgd5ereZAkBAAjnoYMcAc7MnkQcDi0ViGfoNs5syZA6ZBHkuZCr0eacCaNnHCRJ88Ode56HN4FeZBr2htrtWlKJl2PpKbm9GfTpcFwVzXEFCH4JZBr4nkbCe29YcVZAzyRLiy2Ngmzvi7ZAgBhaIWpoZAIIMUKYl3A2rznhEd51iDSxYxWUfpotVtuqIz7G5CziGWb9EK4S5lxQsAajqhuk"

def get_facebook_api():
  graph = facebook.GraphAPI(access_token)
  return graph

def send_to_facebook(msg):
        api = get_facebook_api()
        status = api.put_object(parent_object = 'me', connection_name = 'feed', message = msg)
        
        print(status)

def get_price():
  page = urllib.request.urlopen("http://beans-r-us.appspot.com/prices.html")
  text = page.read().decode("utf8")
  
  where = text.find(">$")
  start_of_price = where + 2
  end_of_price = start_of_price + 4
  
  return float(text[start_of_price:end_of_price])

def main():
  price_now = input("Do you want to see the price now (Y/N)? ")
  
  if price_now == "Y":
    send_to_facebook("Current price of coffee beans = $" + get_price())
  else:
    price = 99.99

    while price > 4.74:
      time.sleep(900)
    
      price = get_price()

    send_to_facebook("Buy!")

if __name__ == "__main__":
  main()