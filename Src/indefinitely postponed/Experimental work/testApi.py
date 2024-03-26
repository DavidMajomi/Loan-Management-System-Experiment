import os
import requests
import json
from pathlib import Path

PATH = str(Path.cwd())

print(PATH)
change_base_rate = True


if os.path.exists(PATH + "\\API keys\\alphaVantageApiKey.txt"):
    with open((PATH + "\\API keys\\alphaVantageApiKey.txt"), "r") as file:
        api_key = file.readline()
else:
        change_base_rate = False

url = f'https://www.alphavantage.co/query?function=FEDERAL_FUNDS_RATE&interval=monthly&apikey={api_key}'
returnedData = requests.get(url)
data = returnedData.json()

    # last_month = data["data"][0]["date"]
last_months_federal_funds_rate = float(data["data"][0]["value"])
    
jsonData = json.dumps(data, indent = 2)

print(last_months_federal_funds_rate)
    # print(last_months_prime_rate)