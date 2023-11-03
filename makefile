loanManagementServerLibrary: loanManagementLibraryForServer.o sqlite3.o
	g++ -fpic -shared -o loanManagementServerLibrary.dll loanManagementLibraryForServer.o sqlite3.o

loanManagementLibraryForServer.o: loanManagementLibraryForServer.cpp
	g++ -c loanManagementLibraryForServer.cpp

# testStatisticsLib: statisticsLibrary.o testStatisticsLibrary.o
# 	g++ statisticsLibrary.cpp testStatisticsLibrary.cpp -o  outputStatistics.exe

# statisticsLibrary.o: statisticsLibrary.cpp
# 	g++ -c statisticsLibrary.cpp

# testStatisticsLibrary.o: testStatisticsLibrary.cpp
# 	g++ -c testStatisticsLibrary.cpp

experimentalDLL: experimentalDLL.o
	g++ -fpic -shared -o experimentalDLL.dll experimentalDLL.o

experimentalDLL.o:
	g++ -c experimentalDLL.cpp

clean:
	del "statisticsLibrary.o"
	del "loanManagementLibraryForServer.o"
	del "testStatisticsLibrary.o"
	del "experimentalDLL.o"
