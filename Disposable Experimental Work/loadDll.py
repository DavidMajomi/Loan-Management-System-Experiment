import ctypes
from pathlib import Path




PATH = str(Path.cwd())

FORMAT = 'utf-8'

OUTPUT_DLL_FILE_FOR_SERVER_PATH = PATH + "\\experimentalDLL.dll"



cpp_library = ctypes.CDLL(OUTPUT_DLL_FILE_FOR_SERVER_PATH, winmode = 0)

test = cpp_library.bro(5)

print(f" This is a test return value = { test}")