import facebook

access_token = "EAAFgd5ereZAkBAAjnoYMcAc7MnkQcDi0ViGfoNs5syZA6ZBHkuZCr0eacCaNnHCRJ88Ode56HN4FeZBr2htrtWlKJl2PpKbm9GfTpcFwVzXEFCH4JZBr4nkbCe29YcVZAzyRLiy2Ngmzvi7ZAgBhaIWpoZAIIMUKYl3A2rznhEd51iDSxYxWUfpotVtuqIz7G5CziGWb9EK4S5lxQsAajqhuk"

def main():
  api = get_api()
  msg = "Hello, world!"
  status = api.put_object(parent_object = 'me', connection_name = 'feed', message = msg)
  
  print(status)

def get_api():
  graph = facebook.GraphAPI(access_token)
  return graph

if __name__ == "__main__":
  main()