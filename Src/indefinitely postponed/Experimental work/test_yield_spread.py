import os
import requests

change_base_rate = True

if os.path.exists("alphaVantageApiKey.txt"):
    with open("alphaVantageApiKey.txt", "r") as file:
        api_key = file.readline()
else:
    change_base_rate = False

url = f'https://www.alphavantage.co/query?function=TREASURY_YIELD&interval=daily&maturity=10year&apikey={api_key}'

returnedData = requests.get(url)
data_for_ten_year = returnedData.json()

# print(data_for_ten_year)

# data_for_ten_year

# last_month = data["data"][0]["date"]
last_months_ten_year_yield = float(data_for_ten_year["data"][0]["value"])

url = f'https://www.alphavantage.co/query?function=TREASURY_YIELD&interval=daily&maturity=3month&apikey={api_key}'


returnedData = requests.get(url)
data_for_three_month = returnedData.json()

# print(data_for_three_month)
last_months_three_month_yield = float(data_for_three_month["data"][0]["value"])


print(" Interval = daily")
print(f" Last months 3 month yield = {last_months_three_month_yield}")
print(f" Last months 10 year yield = {last_months_ten_year_yield}")

print(f" Yield Spread = { last_months_ten_year_yield - last_months_three_month_yield}")

if ((last_months_ten_year_yield - last_months_three_month_yield) < 0):
    print(" There is a yield curve inversion which suggests lowered investor confidence in long term economic success. There should be increased tightening on loan grants.")
else:
    print(" This is a normal yield result suggesting normal economic activities. ")

# jsonData = json.dumps(data, indent = 2)

# print(last_month)
# print(last_months_prime_rate)
