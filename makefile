loanManagementServerLibrary: loanManagementLibraryForServer.o sqlite3.o
	g++ -Q --help=warning -fpic -shared -o loanManagementServerLibrary.dll loanManagementLibraryForServer.o sqlite3.o

loanManagementLibraryForServer.o: loanManagementLibraryForServer.cpp
	g++ --extra-warnings -c loanManagementLibraryForServer.cpp
	
# g++ -Q --help=warning -c loanManagementLibraryForServer.cpp

# testStatisticsLib: statisticsLibrary.o testStatisticsLibrary.o
# 	g++ statisticsLibrary.cpp testStatisticsLibrary.cpp -o  outputStatistics.exe

# statisticsLibrary.o: statisticsLibrary.cpp
# 	g++ -c statisticsLibrary.cpp

# testStatisticsLibrary.o: testStatisticsLibrary.cpp
# 	g++ -c testStatisticsLibrary.cpp

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
