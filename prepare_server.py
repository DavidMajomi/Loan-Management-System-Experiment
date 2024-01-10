import os
import csv
import json
import ctypes
import requests
import random
import sqlite3
import datetime
from faker import Faker
from pathlib import Path
from colorama import Fore



PATH = str(Path.cwd())

FORMAT = 'utf-8'
CSV_FILE_FOR_ALL_GENERATED_DATA_THROUGHOUT_PROGRAM_HISTORY = PATH + "\\Folder with Generated Data\\allGeneratedLoanData.csv"
CSV_FILE_FOR_TEMP_GENERATED_DATA_FOR_db = PATH + "\\Folder with Generated Data\\tempGeneratedLoanDataForDbStorage.csv"


def get_economic_data():
    list_of_data = []
    changed_base_rate = True

    if os.path.exists(PATH + "\\API keys\\alphaVantageApiKey.txt"):
        with open((PATH + "\\API keys\\alphaVantageApiKey.txt"), "r") as file:
            api_key = file.readline()
    else:
        changed_base_rate = False

    url = f'https://www.alphavantage.co/query?function=FEDERAL_FUNDS_RATE&interval=monthly&apikey={api_key}'
    returnedData = requests.get(url)
    data = returnedData.json()
    
    list_of_data.append(data)

    last_months_federal_funds_rate = float(data["data"][0]["value"])
    
    print(f" This is last months federal funds rate: {last_months_federal_funds_rate}")
    last_months_federal_funds_rate = ctypes.c_double(last_months_federal_funds_rate)


    url = f'https://www.alphavantage.co/query?function=TREASURY_YIELD&interval=daily&maturity=10year&apikey={api_key}'

    returnedData = requests.get(url)
    data_for_ten_year_yield = returnedData.json()

    list_of_data.append(data_for_ten_year_yield)

    last_months_ten_year_yield = float(data_for_ten_year_yield["data"][0]["value"])

    url = f'https://www.alphavantage.co/query?function=TREASURY_YIELD&interval=daily&maturity=3month&apikey={api_key}'


    returnedData = requests.get(url)
    data_for_three_month_yield = returnedData.json()

    last_months_three_month_yield = float(data_for_three_month_yield["data"][0]["value"])


    print(" Interval = daily")
    print(f" Last months 3 month yield = {last_months_three_month_yield}")
    print(f" Last months 10 year yield = {last_months_ten_year_yield}")

    print(f" Yield Spread = { last_months_ten_year_yield - last_months_three_month_yield}")

    if ((last_months_ten_year_yield - last_months_three_month_yield) < 0):
        print(" There is a yield curve inversion which suggests lowered investor confidence in long term economic success. There should be increased tightening on loan grants.")
    else:
        print(" This is a normal yield result suggesting normal economic activities. ")
        
    print(" This is barrier \n \n  \n")
    url = f'https://www.alphavantage.co/query?function=REAL_GDP&interval=annual&apikey={api_key}'
    returnedData = requests.get(url)
    data = returnedData.json()
    
    list_of_data.append(data)

    print(data)
    
    return list_of_data

list_of_data = get_economic_data()

