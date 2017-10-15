import facebook

access_token = "CAAOILLVtuyMBAIee9LUaxpl5TIwgcpve1aBYri6ne4dFZCHPxrdeojojKjb11mKKiLp48pob8ZBqHfIaeAZBdXsaOkZB7ChIlHNAgVm4eWWsZCqUyoAWVTciCiaHM1yKIq4Xy80jHdflmgq9ZByEgsnYNsr6ULYORm5ZBYBjJglvKXcB9iTvRhNMZCyqrtyZAsMr3NOXZAFKCfCyPHsPdMGsdz"

def main():
  api = get_api()
  msg = "Hello, world!"
  status = api.put_wall_post(msg)
  print(status)

def get_api():
  graph = facebook.GraphAPI(access_token)
  return graph

if __name__ == "__main__":
  main()