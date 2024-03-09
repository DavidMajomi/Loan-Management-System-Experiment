#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <typeinfo>
#include <utility>
#include "sqlite3.h"


namespace databaseAbstraction
{
    using namespace std;

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


    vector <vector<string>> retreiveDataWithMatchingValue(const char * databaseFullPath, string tableName, string id, string idValue) 
    {
        string fullStatement = "SELECT * FROM " + tableName + " where " + id + "=" + idValue + ";";
        const char * sql = fullStatement.c_str();
        sqlite3* db;
        int rc = sqlite3_open(databaseFullPath, &db);
        vector<vector<string>> dBDataMatrix;

        if (rc != SQLITE_OK)
        {
            throw " FAILURE OPENING DATABASE";
        }
        else
        {

            sqlite3_stmt* stmt;
            
            rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

            if (rc != SQLITE_OK) {
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


    bool validateStringIsDigit(string value)
    {
        bool validNumber = true;
        for(int count = 0; count < value.size(); count++)
        {
            if(!(isdigit(value[count]) == true))
            {
                value = false;
            }
        }

        return validNumber;
    }


    template <typename T>
    bool isValidNumber(T value)
    {
        bool isNumber = false;
        
        if(((value)) == typeid(int).name())
        {
            isNumber = true;           
        }
        else if(((value)) == typeid(float).name())
        {
            isNumber = true;           
        }
        if(((value)) == typeid(double).name())
        {
            isNumber = true;           
        }
        else if(((value)) == typeid(unsigned int).name())
        {
            isNumber = true;           
        }
        else if(((value)) == typeid(long int).name())
        {
            isNumber = true;           
        }

        return isNumber;
    }


    template <typename T>
    double storeDataInDbUsingSingleTransaction(const char * databaseFullPath, string sqlInsertFormat, string sqlInsertTableNames, vector<vector <pair <T, string>>> matrixData)
    {
        clock_t time;

        time = clock();

        sqlite3* db;
        int numberOFInsertions;
        int rc = sqlite3_open(databaseFullPath, &db);
        char charFinalSqlInsertStatement;
        double timeDouble;
        const char* sqlInsertLine;
        char * sqliteErrorMessage;
        string stringSql = "BEGIN TRANSACTION; " + sqlInsertFormat;
        const char* sql = stringSql.c_str();
        vector <string> allInsertStatements;
        string insertToSql, stringFinalSqlInsertStatement, completedSqlStatement;
        sqlite3_stmt* stmt;

        if (rc != SQLITE_OK)
        {
            throw " FAILURE OPENING DATABASE";
        }
        else
        {
            rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);

            if (rc != SQLITE_OK) {
                sqlite3_close(db);
                throw " FAILURE COMPILING SQL STATEMENT";
            }
            rc = sqlite3_exec(db, sql, 0, 0, &sqliteErrorMessage);

            if (rc != SQLITE_OK) {
                sqlite3_close(db);
                throw sqliteErrorMessage;
            }

            int numRowsToAdd = matrixData.size();
            for (int count = 0; count < numRowsToAdd; count++)
            {
                string rowDataString;

                for(int delta = 0; delta < matrixData[count].size(); delta++)
                {
                    
                    if(((matrixData[count][delta].second)) == typeid(string).name())
                    {
                        rowDataString = rowDataString + "'" + (matrixData[count][delta].first) + "'";

                    }
                    else if(((isValidNumber((matrixData[count][delta].second))) == true))
                    {
                        string val = (string)(matrixData[count][delta].first);
                        rowDataString = rowDataString + (val);
                    }
                    else     
                    {
                        throw "DATA TYPE TO INSERT NOT SUPPORTED, CANNOT ADD VALUE TO DATABASE";
                    }


                    if((delta <= ( matrixData[count].size() - 2)))
                    {
                        rowDataString = rowDataString + ",";
                    }

                }

                insertToSql = sqlInsertTableNames + " VALUES (" + rowDataString + ");";
               // cout << insertToSql;

                allInsertStatements.push_back(insertToSql);
            }

            numberOFInsertions = allInsertStatements.size();

            for(int count = 0; count < numberOFInsertions; count++)
            {
                completedSqlStatement = completedSqlStatement + allInsertStatements[count];
            }


            completedSqlStatement = completedSqlStatement + "COMMIT;";

            sqlInsertLine = completedSqlStatement.c_str();
            sql = sqlInsertLine;

            // cout << endl << sql <<endl;
            rc = sqlite3_exec(db, sql, 0, 0, &sqliteErrorMessage);

            if (rc != SQLITE_OK) {
                throw sqliteErrorMessage;
                sqlite3_close(db);
            }


            sqlite3_finalize(stmt);
            sqlite3_close(db);

            time = clock() - time;

            timeDouble = (double)(time);
            
        }

        return timeDouble;

    }


    double update(const char * databaseFullPath, string tableName, string columnName, string newColumnValue, string primaryKey, int keyValue)
    {
        clock_t time;

        time = clock();

        sqlite3* db;
        int numberOFInsertions;
        int rc = sqlite3_open(databaseFullPath, &db);
        double timeDouble;
        char * sqliteErrorMessage;
        string stringSql = "UPDATE " + tableName + " set " + columnName + " = '" + newColumnValue + "' WHERE " + primaryKey + "=" + to_string(keyValue) + "; ";
        const char* sql = stringSql.c_str();
        sqlite3_stmt* stmt;

        if (rc != SQLITE_OK)
        {
            throw " FAILURE OPENING DATABASE";
        }
        else
        {
            rc = sqlite3_exec(db, sql, 0, 0, &sqliteErrorMessage);

            if (rc != SQLITE_OK) {
                sqlite3_close(db);
                throw sqliteErrorMessage;
            }

            sqlite3_close(db);

            time = clock() - time;

            timeDouble = (double)(time);
        }


        return timeDouble;
    }


    double deleteRow(const char * databaseFullPath, string tableName, string columnName, string primaryKey, int keyValue)
    {
        clock_t time;

        time = clock();

        sqlite3* db;
        int numberOFInsertions;
        int rc = sqlite3_open(databaseFullPath, &db);
        double timeDouble;
        char * sqliteErrorMessage;
        string stringSql = "DELETE from " + tableName + " WHERE " + primaryKey + "=" + to_string(keyValue) + "; ";
        const char* sql = stringSql.c_str();
        sqlite3_stmt* stmt;

        if (rc != SQLITE_OK)
        {
            throw " FAILURE OPENING DATABASE";
        }
        else
        {
            rc = sqlite3_exec(db, sql, 0, 0, &sqliteErrorMessage);

            if (rc != SQLITE_OK) {
                sqlite3_close(db);
                throw sqliteErrorMessage;
            }

            sqlite3_close(db);

            time = clock() - time;

            timeDouble = (double)(time);
        }


        return timeDouble;
    }


    double addNewColumn(const char * databaseFullPath, string tableName, string columnName, string sqliteDataType)
    {
        clock_t time;

        time = clock();

        sqlite3* db;
        int numberOFInsertions;
        int rc = sqlite3_open(databaseFullPath, &db);
        double timeDouble;
        char * sqliteErrorMessage;
        string stringSql = "ALTER TABLE " + tableName + " ADD COLUMN " + columnName + " " + sqliteDataType + "; ";
        const char* sql = stringSql.c_str();
        sqlite3_stmt* stmt;

        if (rc != SQLITE_OK)
        {
            throw " FAILURE OPENING DATABASE";
        }
        else
        {
            rc = sqlite3_exec(db, sql, 0, 0, &sqliteErrorMessage);

            if (rc != SQLITE_OK) {
                sqlite3_close(db);
                throw sqliteErrorMessage;
            }

            sqlite3_close(db);

            time = clock() - time;

            timeDouble = (double)(time);
        }


        return timeDouble;
    }


    double deleteColumn(const char * databaseFullPath, string tableName, string columnName)
    {
        clock_t time;

        time = clock();

        sqlite3* db;
        int numberOFInsertions;
        int rc = sqlite3_open(databaseFullPath, &db);
        double timeDouble;
        char * sqliteErrorMessage;
        string stringSql = "ALTER TABLE " + tableName + " DROP COLUMN " + columnName + "; ";
        const char* sql = stringSql.c_str();
        sqlite3_stmt* stmt;

        if (rc != SQLITE_OK)
        {
            throw " FAILURE OPENING DATABASE";
        }
        else
        {
            rc = sqlite3_exec(db, sql, 0, 0, &sqliteErrorMessage);

            if (rc != SQLITE_OK) {
                sqlite3_close(db);
                throw sqliteErrorMessage;
            }

            sqlite3_close(db);

            time = clock() - time;

            timeDouble = (double)(time);
        }


        return timeDouble;
    }


    double storeSingleRowInDbUsingSingleInsert(const char * databaseFullPath, string sqlInsertFormat, string sqlInsertTableNames, string singleValueToInsert)
    {
        clock_t time;

        time = clock();

        sqlite3* db;
        int numberOFInsertions;
        int rc = sqlite3_open(databaseFullPath, &db);
        char charFinalSqlInsertStatement;
        double timeDouble;
        const char* sqlInsertLine;
        char * sqliteErrorMessage;
        string stringSql = "BEGIN TRANSACTION; " + sqlInsertFormat;
        const char* sql = stringSql.c_str();
        vector <string> allInsertStatements;
        string insertToSql, stringFinalSqlInsertStatement, completedSqlStatement;
        sqlite3_stmt* stmt;

        if (rc != SQLITE_OK)
        {
            throw " FAILURE OPENING DATABASE";
        }
        else
        {
            rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);

            if (rc != SQLITE_OK) {
                sqlite3_close(db);
                throw " FAILURE COMPILING SQL STATEMENT";
            }
            rc = sqlite3_exec(db, sql, 0, 0, &sqliteErrorMessage);

            if (rc != SQLITE_OK) {
                sqlite3_close(db);
                throw sqliteErrorMessage;
            }


            completedSqlStatement = singleValueToInsert + "COMMIT;";

            sqlInsertLine = completedSqlStatement.c_str();
            sql = sqlInsertLine;

            // cout << endl << sql <<endl;
            rc = sqlite3_exec(db, sql, 0, 0, &sqliteErrorMessage);

            if (rc != SQLITE_OK) {
                throw sqliteErrorMessage;
                sqlite3_close(db);
            }

            sqlite3_finalize(stmt);
            sqlite3_close(db);

            time = clock() - time;

            timeDouble = (double)(time);
            
        }

        return timeDouble;

    }
    
}
