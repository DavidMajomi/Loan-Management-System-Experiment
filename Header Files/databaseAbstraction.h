#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include "sqlite3.h"

using namespace std;

namespace databaseAbstraction
{
    vector <vector<string>> retrieveAllUserDataFromDatabaseForMatrix(const char * databaseFullPath, string tableName) 
    {
        string fullStatement = "SELECT * FROM " + tableName;
        const char * sql = fullStatement.c_str();
        sqlite3* db;
        int rc = sqlite3_open(databaseFullPath, &db);
        vector<vector<string>> dBDataMatrix;

        if (rc != SQLITE_OK)
        {
            // Handle error
            // cout << "Step 1 error." << endl;
            throw " FAILURE OPENING DATABASE";
        }
        else
        {
            // cout << " This is File path for analyzed data: " << databaseFullPath << endl;

            sqlite3_stmt* stmt;
            
            rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

            if (rc != SQLITE_OK) {
                // Handle error
                // cout << " Step 5 error. " << endl;
                throw " FAILURE COMPILING SQL STATEMENT";
                sqlite3_close(db);
            }

            int row = 0;
            vector <string> temp;
            // dBDataMatrix.resize(sqlite3_column_count(stmt));
            while (sqlite3_step(stmt) == SQLITE_ROW) {
                for(int count = 0; count < sqlite3_column_count(stmt); count++)     // Populate temp with row values in preparation to pushback to data matrix
                {
                    string tempString;
                    if(sqlite3_column_type(stmt, count) == SQLITE_INTEGER)
                    {
                        temp.push_back(to_string(sqlite3_column_int(stmt, count)));

                    }
                    else if(sqlite3_column_type(stmt, count) == SQLITE_TEXT)
                    {
                        tempString.assign((const char *)(sqlite3_column_text(stmt, count)));
                        temp.push_back(tempString);
                    }
                    else if(sqlite3_column_type(stmt, count) == SQLITE_FLOAT)
                    {
                        temp.push_back(to_string(sqlite3_column_double(stmt, count)));
                    }
                    // else if(sqlite3_column_type(stmt, count) == SQLITE_BLOB)
                    // {
                            // temp.push_back(to_string(sqlite3_column_blob(stmt, count)));
                    // }
                    else
                    {
                        throw " ERROR SEARCHING DATABASE, VALUE OUTSIDE OF CURRENT RETRIEVEABLE SQLITE DATATYPES";
                    }
                        
                }

                // dBDataMatrix.resize(row + 1);
                dBDataMatrix.push_back(temp);
                temp.clear();
                
            }

            sqlite3_finalize(stmt);
            sqlite3_close(db);
        }


        return dBDataMatrix;

    }

   
}
