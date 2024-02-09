loanManagementServerLibrary.dll: loanManagementLibraryForServer.o sqlite3.o
	g++ -fpic -shared -o loanManagementServerLibrary.dll loanManagementLibraryForServer.o sqlite3.o
# g++ -Q --help=warning -fpic -shared -o loanManagementServerLibrary.dll loanManagementLibraryForServer.o sqlite3.o

loanManagementServerLibraryLinux: loanManagementLibraryForServer.o sqlite3.o
	g++ -fpic -shared -o loanManagementServerLibrary.so loanManagementLibraryForServer.o sqlite3.o
# g++ -Q --help=warning -fpic -shared -o loanManagementServerLibrary.so loanManagementLibraryForServer.o sqlite3.o

loanManagementLibraryForServer.o: loanManagementLibraryForServer.cpp
	g++ -c loanManagementLibraryForServer.cpp
	
# 
testServer: testServer.o
# g++ -fpic -shared -o loanManagementServerLibrary.dll loanManagementLibraryForServer.o sqlite3.o
	g++ loanManagementServerLibrary.dll testserver.o -o testServer

testServer.o: testServer.cpp
	g++ -c testServer.cpp


testBro: experimentalDLL.dll testExport.o
	g++ experimentalDLL.dll testExport.cpp -o  testExport.exe

testExport.o:
	g++ -c testExport.cpp


experimentalDLL.dll: experimentalDLL.o
	g++ -fpic -shared -o experimentalDLL.dll experimentalDLL.o

experimentalDLL: experimentalDLL.o
	g++ -fpic -shared -o experimentalDLL.dll experimentalDLL.o

experimentalDLL.o:
	g++ -c experimentalDLL.cpp


testLinktimeDebugger: externDebugger.dll
	g++ linktimeUseDebugger.cpp externDebugger.dll -o linktimeUseDebugger.exe

externDebugger.dll:
	g++ -fpic -shared -o externDebugger.dll externalDebugger.cpp


# experimentalDLL: experimentalDLL.cpp
# 	g++ -fpic -shared -o experimentalDLL.dll 



clean:
	del "statisticsLibrary.o"
	del "loanManagementLibraryForServer.o"
	del "testStatisticsLibrary.o"
	del "experimentalDLL.o"
	del "experimentalDLL.dll"
	del "externDebugger.dll"
	del "testExport.o"
	del "testLoadinDll.exe"
	del "testExport.exe"
	del "runtimeConsumeDebugger.exe"
	del "linktimeUseDebugger.exe"

cleanLinux:
	rm "statisticsLibrary.o"
	rm "loanManagementLibraryForServer.o"
	rm "testStatisticsLibrary.o"
	rm "experimentalDLL.o"
	rm "experimentalDLL.dll"
	rm "externDebugger.dll"
	rm "testExport.o"
	rm "testLoadinDll.exe"
	rm "testExport.exe"
	rm "runtimeConsumeDebugger.exe"
	rm "linktimeUseDebugger.exe"


# g++ -Q --help=warning -c loanManagementLibraryForServer.cpp

# testStatisticsLib: statisticsLibrary.o testStatisticsLibrary.o
# 	g++ statisticsLibrary.cpp testStatisticsLibrary.cpp -o  outputStatistics.exe

# statisticsLibrary.o: statisticsLibrary.cpp
# 	g++ -c statisticsLibrary.cpp

# testStatisticsLibrary.o: testStatisticsLibrary.cpp
# 	g++ -c testStatisticsLibrary.cpp
