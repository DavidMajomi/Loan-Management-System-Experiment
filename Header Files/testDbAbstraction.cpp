#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <filesystem>// cpp 17 reference https://en.cppreference.com/w/cpp/filesystem/current_paths
#include "databaseAbstraction.h"


namespace fs = std::filesystem;
using namespace std;

// FILE NAMES
const string CURRENT_FULL_PATH = fs::current_path().string();
const string DATABASE_NAME_WITH_PATH = CURRENT_FULL_PATH + "\\Header Files\\bam_bam.db";       // Has to be a constant char to be compatibe with sqlite
const char* DATABASE_NAME = DATABASE_NAME_WITH_PATH.c_str();

template <typename T>
void printMatrixValues(vector<vector <T>> dBDataMatrix)
{
    int matrixSize = dBDataMatrix.size();
    for(int count = 0; count < matrixSize; count++)
    {
        for(int j = 0; j < dBDataMatrix[count].size(); j++)
        {
            cout << dBDataMatrix[count][j] << endl;
        }

        cout << endl << endl;
        
    }
}

void getData()
{
    vector <vector<string>> dBDataMatrix;
    try
    {
        dBDataMatrix = databaseAbstraction::retrieveAllUserDataFromDatabaseForMatrix(DATABASE_NAME, "uers");
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    catch(string exception)
    {
        cout << " Error exception caught: " << endl;
        cout << " Exception value: " << exception << endl;
        printMatrixValues(dBDataMatrix);
    }
    catch(const char * exception)
    {
        cout << " Error exception caught: " << endl;
        cout << " Exception value: " << exception << endl;
        printMatrixValues(dBDataMatrix);
    }
}



int main()
{
    getData();
    
    return 0;
}


