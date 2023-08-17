import ctypes
import subprocess
from header_file import generate_data


STAND_ALONE_CPP_EXECUTABLE = "C:\\Users\\David\\Documents\\Github\\Loan-Management-System-Experiment\\just c++.exe"  
MAIN_CPP_FILE = "C:\\Users\\David\\Documents\\Github\\Loan-Management-System-Experiment\\main.cpp"
SQLITE3_DATABASE_PATH = 'C:\\Users\\David\\Documents\\Github\\Loan-Management-System-Experiment\\sham_bam.db'
SQLITE3_OBJECT_FILE_PATH = "C:\\Users\\David\\Documents\\Github\\Loan-Management-System-Experiment\\sqlite3.o"
LIBRARY_CPP_FILE_PATH = "C:\\Users\\David\\Documents\\Github\\Loan-Management-System-Experiment\\loanManagementLibrary.cpp"
OUTPUT_DLL_FILE_PATH = "C:\\Users\\David\\Documents\\Github\\Loan-Management-System-Experiment\\loanManagementLibrary.dll"  
CPP_EXECUTABLE_FROM_PYTHON_PATH = "C:\\Users\\David\\Documents\\loanManagementSystem\\executable from python interface.exe"  


compile_commands = "g++ -fPIC -shared -o"

complete_command_instruction = compile_commands + " " + OUTPUT_DLL_FILE_PATH + " " + LIBRARY_CPP_FILE_PATH + " " + SQLITE3_OBJECT_FILE_PATH
subprocess.run(complete_command_instruction, check=True)

cppLibrary = ctypes.CDLL(OUTPUT_DLL_FILE_PATH)
initialMenuResponse = cppLibrary.setInitialMenuResponse()

if (initialMenuResponse == 1):
    devMenuResponse = cppLibrary.showDevMenuFromCpp()

if (devMenuResponse == 1):
    generate_data()
        
cppLibrary.getValuesFromPython(initialMenuResponse, devMenuResponse)