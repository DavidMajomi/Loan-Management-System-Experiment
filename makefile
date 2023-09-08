loanManagementServerLibrary: loanManagementLibraryForServer.o sqlite3.o
	g++ -fpic -shared -o loanManagementServerLibrary.dll loanManagementLibraryForServer.o sqlite3.o

loanManagementLibraryForServer.o: loanManagementLibraryForServer.cpp
	g++ -c loanManagementLibraryForServer.cpp