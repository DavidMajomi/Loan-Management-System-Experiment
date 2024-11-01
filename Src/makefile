sqliteOfile = $(CURDIR)/'sqlite3 Executables'/sqlite3.o
testingFolder = $(CURDIR)/'Test Files'

loanManagementServerLibrary.dll: loanManagementLibraryForServer.o 
	g++ -fpic -shared -o loanManagementServerLibrary.dll loanManagementLibraryForServer.o $(sqliteOfile)
# g++ -Q --help=warning -fpic -shared -o loanManagementServerLibrary.dll loanManagementLibraryForServer.o sqlite3.o

loanManagementServerLibraryLinux: loanManagementLibraryForServer.o $(sqliteOfile)
	g++ -fpic -shared -o loanManagementServerLibrary.so loanManagementLibraryForServer.o $(sqliteOfile)
# g++ -Q --help=warning -fpic -shared -o loanManagementServerLibrary.so loanManagementLibraryForServer.o sqlite3.o

testLoanManagementServerLibrary.dll: loanManagementLibraryForServer.o 
	g++ -fpic -shared -o $(testingFolder)/Executables/loanManagementServerLibrary.dll loanManagementLibraryForServer.o $(sqliteOfile)

loanManagementLibraryForServer.o: loanManagementLibraryForServer.cpp
	g++ -c loanManagementLibraryForServer.cpp
	


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

runtests:
	make testLoanDbManager
	make testDbAbstraction
	make testLogger
	make testServer
	make testTimeManip
	
	$(testingFolder)/Executables/testServer.exe
	$(testingFolder)/Executables/testLoanDbManager.exe
	$(testingFolder)/Executables/testLogger.exe
	$(testingFolder)/Executables/testDbAbstraction.exe
	$(testingFolder)/Executables/testTimeManip.exe
# make runTestDbAbstraction

runTestDbAbstraction:
	make testDbAbstraction
	$(testingFolder)/Executables/testDbAbstraction.exe
	
testLoanDbManager: testLoanDatabaseManager.o testLoanManagementServerLibrary.dll
	g++ $(testingFolder)/Executables/loanManagementServerLibrary.dll $(testingFolder)/Executables/testLoanDatabaseManager.o $(sqliteOfile) -o $(testingFolder)/Executables/testLoanDbManager.exe

testLoanDatabaseManager.o:
	g++ -c $(testingFolder)/testLoanDatabaseManager.cpp -o $(testingFolder)/Executables/testLoanDatabaseManager.o
	
testDbAbstraction: testDbAbstraction.o
	g++ $(testingFolder)/Executables/testDbAbstraction.o $(sqliteOfile) -o $(testingFolder)/Executables/testDbAbstraction.exe

testDbAbstraction.o:
	g++ -c $(testingFolder)/testDbAbstraction.cpp -o $(testingFolder)/Executables/testDbAbstraction.o

testLogger: testLogger.o
	g++ $(testingFolder)/Executables/testLogger.o $(sqliteOfile) -o $(testingFolder)/Executables/testLogger.exe

testLogger.o:
	g++ -c $(testingFolder)/testLogger.cpp -o $(testingFolder)/Executables/testLogger.o
	
testServer: testServer.o testLoanManagementServerLibrary.dll
	g++ $(testingFolder)/Executables/loanManagementServerLibrary.dll $(tedstingFolder)/Executables/testServer.o $(sqliteOfile) -o $(testingFolder)/Executables/testServer.exe

testServer.o:
	g++ -c $(testingFolder)/testServer.cpp -o $(testingFolder)/Executables/testServer.o

testTimeManip: testTimeManip.o
	g++ $(testingFolder)/Executables/testTimeManip.o $(sqliteOfile) -o $(testingFolder)/Executables/testTimeManip.exe

testTimeManip.o:
	g++ -c $(testingFolder)/testTimeManip.cpp -o $(testingFolder)/Executables/testTimeManip.O


.PHONY clean:
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