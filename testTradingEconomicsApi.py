import os
import requests
from pathlib import Path

PATH = str(Path.cwd())

FORMAT = 'utf-8'
STAND_ALONE_CPP_EXECUTABLE = PATH + "\\just c++.exe"  
MAIN_CPP_FILE = PATH + "\\main.cpp"
SQLITE3_DATABASE_PATH = PATH + "\\Database files\\bam_bam.db"
# SQLITE3_OBJECT_FILE_PATH = PATH + "\\sqlite3.o"
LIBRARY_CPP_FILE_PATH = PATH + "\\loanManagementLibrary.cpp"
LIBRARY_CPP_FILE_PATH_FOR_SERVER = PATH + "\\loanManagementLibraryForServer.cpp"
OUTPUT_DLL_FILE_PATH = PATH + "\\loanManagementLibrary.dll"  
OUTPUT_DLL_FILE_FOR_SERVER_PATH = PATH + "\\loanManagementServerLibrary.dll"
CPP_EXECUTABLE_FROM_PYTHON_PATH = PATH + "\\executable from python interface.exe"  
CSV_FILE_FOR_ALL_GENERATED_DATA_THROUGHOUT_PROGRAM_HISTORY = PATH + "\\Folder with Generated Data\\allGeneratedLoanData.csv"

if os.path.exists(PATH + "\\API keys\\tradingEconomicsApiKey.txt"):
    with open((PATH + "\\API keys\\tradingEconomicsApiKey.txt"), "r") as file:
        api_key = file.readline()
else:
    changed_base_rate = False
    
    
print(api_key)
    
url = f"https://api.tradingeconomics.com/fred/historical/recprousm156n?c={api_key}"

returnedData = requests.get(url)
data = returnedData.json()


print(data)
print(f" Data size: {len(data)} \n \n \n")
print(f" todays data as a dict: {data[len(data) - 1]} \n \n \n")
