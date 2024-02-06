#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>


using std::endl;
using std::cout;
using std::cin;
using std::vector;
using std::string;
// using std::int;

void testActualAlgo()
{
    string inputInMatlabFormat;
    double matrix[2][3];
    // double rowOneColumnOne = 2, rowOneColumnTwo = 3, rowOneColumnThree = 4, rowTwoColumnOne = 3, rowTwoColumnTwo = 1, rowTwoColumnThree = 6;
    double rowOneColumnOne = 0.597085, rowOneColumnTwo = 1, rowOneColumnThree = 131.037, rowTwoColumnOne = 0.114787, rowTwoColumnTwo = 1, rowTwoColumnThree = 55.0846;

    // cout << " Enter row one column one: ";
    // cin >> rowOneColumnOne;
    
    matrix[0][0] = rowOneColumnOne;

    // cout << " Enter row one column two: ";
    // cin >> rowOneColumnTwo;
    
    matrix[0][1] = rowOneColumnTwo;

    // cout << " Enter row one column three: ";
    // cin >> rowOneColumnThree;

    matrix[0][2] = rowOneColumnThree;

    // cout << " Enter row 2 column one: ";
    // cin >> rowTwoColumnOne;

    matrix[1][0] = rowTwoColumnOne;

    // cout << " Enter row 2 column 2: ";
    // cin >> rowTwoColumnTwo;

    matrix[1][1] = rowTwoColumnTwo;

    // cout << " Enter row 2 column one3: ";
    // cin >> rowTwoColumnThree;

    matrix[1][2] = rowTwoColumnThree;

    // cout << endl;
    // cout << " [" << matrix[0][0] << " " << matrix[0][1] << " " << matrix[0][2] << "]" << endl;
    // cout << " [" << matrix[1][0] << " " << matrix[1][1] << " " << matrix[1][2] << "]" << endl;

    cout << " Input in matlab format: A = " << "[" << matrix[0][0] << " " << matrix[0][1] << " " << matrix[0][2] << "; ";
    cout << matrix[1][0] << " " << matrix[1][1] << " " << matrix[1][2] << "]" << endl;

    // cout << " Test matrix size: " <<  matrix.size() << endl;

    // Make the first value 1 and adjust the first row.
    double firstPosition = matrix[0][0];

    for(int count = 0; count < 3; count++)
    {
        // if(firstPosition != 0)
        {

            matrix[0][count] = (1 / firstPosition) * matrix[0][count];
        }

        cout << endl;

    // cout << " this is count: " << count << " This is matrix[0][count]: " << matrix[0][count] << endl;

    //  cout << " [" << firstPosition << " " << matrix[0][1] << " " << matrix[0][2] << "]" << endl;
    // cout << " [" << matrix[1][0] << " " << matrix[1][1] << " " << matrix[1][2] << "]" << endl;

    }

    cout << endl;


    cout << " [" << matrix[0][0] << " " << matrix[0][1] << " " << matrix[0][2] << "]" << endl;
    cout << " [" << matrix[1][0] << " " << matrix[1][1] << " " << matrix[1][2] << "]" << endl;

    double currentRowOneColumnOne = matrix[0][0];

    for(int count = 1; count < 2; count++)
    {
        for(int j = 0; j < 3; j++)
        {
            matrix[count][j] = ((rowTwoColumnOne * matrix[count -1][j])) - ((currentRowOneColumnOne * matrix[count][j]));
        }

    }

    // cout << endl;

    //  cout << " [" << matrix[0][0] << " " << matrix[0][1] << " " << matrix[0][2] << "]" << endl;
    // cout << " [" << matrix[1][0] << " " << matrix[1][1] << " " << matrix[1][2] << "]" << endl;

    double currentRow2FirstPosition = matrix[1][0];

    for(int count = 0; count < 3; count++)
    {
        if(currentRow2FirstPosition != 0)
        {
            matrix[1][count] = (1 / currentRow2FirstPosition) * matrix[1][count];
        }
    }


    // cout << endl;
    // cout << " This is the marker " << endl;

    // cout << " [" << matrix[0][0] << " " << matrix[0][1] << " " << matrix[0][2] << "]" << endl;
    // cout << " [" << matrix[1][0] << " " << matrix[1][1] << " " << matrix[1][2] << "]" << endl;

    double currentRowTwoColumnTwo = matrix[1][1];

    for (int count = 1; count < 3; count++)
    {
        matrix[1][count] = (1 / currentRowTwoColumnTwo) * (matrix[1][count]);
        // matrix[0][count] = (matrix[0][count] * matrix[1][count]) - matrix[0][count];

    }

    // cout << endl;

    //  cout << " [" << matrix[0][0] << " " << matrix[0][1] << " " << matrix[0][2] << "]" << endl;
    // cout << " [" << matrix[1][0] << " " << matrix[1][1] << " " << matrix[1][2] << "]" << endl;

    firstPosition = matrix[0][0];

    for (int count = 0; count < 3; count++)
    {
        if(firstPosition != 0)
        {
            matrix[0][count] = (1 / firstPosition * matrix[0][count]);
        }

    }

    cout << endl;
    double current1Row2SecondPosition = matrix[0][1];

    for(int count = 0; count < 3; count++)
    {
        matrix[0][count] = (current1Row2SecondPosition * matrix[1][count]) - matrix[0][count];

    }


    double currentFirstPosition = matrix[0][0];

    for(int count = 0; count < 3; count++)
    {
        if (currentFirstPosition != 0)
        {
            matrix[0][count] = (1/ currentFirstPosition) * matrix[0][count];

        }
    }


    cout << " Row 1: " << endl;
    cout << " First value: " << matrix[0][0] << " second value: " << matrix[0][1] << " third value: " << matrix[0][2] << endl;
    cout << " Row 2: " << endl;
    cout << " First value: " << matrix[1][0] << " second value: " << matrix[1][1] << " third value: " << matrix[1][2] << endl;

    cout << " [" << matrix[0][0] << " " << matrix[0][1] << " " << matrix[0][2] << "]" << endl;
    cout << " [" << matrix[1][0] << " " << matrix[1][1] << " " << matrix[1][2] << "]" << endl;

    






    
}

std::string verifyUserInput(const std::string);

void testActualAlgo(int test);

int main()
{
    std::string userInput;

    testActualAlgo();
    // while(userInput != "exit")
    // {
    //     std::cout << " Enter a 2 by 3 matrix in matlab / octave format: ";
    //     std::cin >> userInput;

    //     std::cout << " This is your input: " << userInput << endl;



    // }
    
    return 0;
}



// void testActualAlgo(int test)
// {
//     string inputInMatlabFormat;
//     double matrix[2][3];
//     // double rowOneColumnOne = 0.597085, rowOneColumnTwo = 1, rowOneColumnThree = 131.037, rowTwoColumnOne = 0.114787, rowTwoColumnTwo = 1, rowTwoColumnThree = 55.0846;
//     double rowOneColumnOne = 2, rowOneColumnTwo = 3, rowOneColumnThree = 4, rowTwoColumnOne = 3, rowTwoColumnTwo = 1, rowTwoColumnThree = 6;
    

//     // cout << " Enter row one column one: ";
//     // cin >> rowOneColumnOne;
    
//     matrix[0][0] = rowOneColumnOne;

//     // cout << " Enter row one column two: ";
//     // cin >> rowOneColumnTwo;
    
//     matrix[0][1] = rowOneColumnTwo;

//     // cout << " Enter row one column three: ";
//     // cin >> rowOneColumnThree;

//     matrix[0][2] = rowOneColumnThree;

//     // cout << " Enter row 2 column one: ";
//     // cin >> rowTwoColumnOne;

//     matrix[1][0] = rowTwoColumnOne;


//     // cout << " Enter row 2 column 2: ";
//     // cin >> rowTwoColumnTwo;

//     matrix[1][1] = rowTwoColumnTwo;


//     // cout << " Enter row 2 column one3: ";
//     // cin >> rowTwoColumnThree;

//     matrix[1][2] = rowTwoColumnThree;

//     cout << endl;
//     cout << " [" << matrix[0][0] << " " << matrix[0][1] << " " << matrix[0][2] << "]" << endl;
//     cout << " [" << matrix[1][0] << " " << matrix[1][1] << " " << matrix[1][2] << "]" << endl;

//     cout << " Input in matlab format: A = " << "[" << matrix[0][0] << " " << matrix[0][1] << " " << matrix[0][2] << "; ";
//     cout << matrix[1][0] << " " << matrix[1][1] << " " << matrix[1][2] << "]" << endl;

//     // cout << " Test matrix size: " <<  matrix.size() << endl;

//     // Make the first value 1 and adjust the first row.
//     double firstPosition = matrix[0][0];

//     for(int count = 0; count < 3; count++)
//     {
//         // if(firstPosition != 0)
//         {

//             matrix[0][count] = (1 / firstPosition) * matrix[0][count];
//         }

//         cout << endl;

//     cout << " this is count: " << count << " This is matrix[0][count]: " << matrix[0][count] << endl;

//      cout << " [" << firstPosition << " " << matrix[0][1] << " " << matrix[0][2] << "]" << endl;
//     cout << " [" << matrix[1][0] << " " << matrix[1][1] << " " << matrix[1][2] << "]" << endl;

//     }

//     cout << endl;


//      cout << " [" << matrix[0][0] << " " << matrix[0][1] << " " << matrix[0][2] << "]" << endl;
//     cout << " [" << matrix[1][0] << " " << matrix[1][1] << " " << matrix[1][2] << "]" << endl;

//     // int row2firstposition matrix[1][0]
//     for(int count = 1; count < 2; count++)
//     {
//         for(int j = 0; j < 3; j++)
//         {
//             matrix[count][j] = ((rowTwoColumnOne * matrix[count -1][j]) - (matrix[count][j]));
//         }

//     }

//     cout << endl;

//      cout << " [" << matrix[0][0] << " " << matrix[0][1] << " " << matrix[0][2] << "]" << endl;
//     cout << " [" << matrix[1][0] << " " << matrix[1][1] << " " << matrix[1][2] << "]" << endl;

//     double currentRow2FirstPosition = matrix[1][0];

//     for(int count = 0; count < 3; count++)
//     {
//         if(currentRow2FirstPosition != 0)
//         {
//             matrix[1][count] = (1 / currentRow2FirstPosition) * matrix[1][count];
//         }
//     }


//     cout << endl;
//     cout << " This is the marker " << endl;

//     cout << " [" << matrix[0][0] << " " << matrix[0][1] << " " << matrix[0][2] << "]" << endl;
//     cout << " [" << matrix[1][0] << " " << matrix[1][1] << " " << matrix[1][2] << "]" << endl;

//     double currentRowTwoColumnTwo = matrix[1][1];

//     for (int count = 1; count < 3; count++)
//     {
//         matrix[1][count] = (1 / currentRowTwoColumnTwo) * (matrix[1][count]);
//         // matrix[0][count] = (matrix[0][count] * matrix[1][count]) - matrix[0][count];

//     }

//     cout << endl;

//      cout << " [" << matrix[0][0] << " " << matrix[0][1] << " " << matrix[0][2] << "]" << endl;
//     cout << " [" << matrix[1][0] << " " << matrix[1][1] << " " << matrix[1][2] << "]" << endl;

//     firstPosition = matrix[0][0];

//     for (int count = 0; count < 3; count++)
//     {
//         if(firstPosition != 0)
//         {
//             matrix[0][count] = (1 / firstPosition * matrix[0][count]);
//         }

//     }

//     cout << endl;
//     double current1Row2SecondPosition = matrix[0][1];

//     for(int count = 0; count < 3; count++)
//     {
//         matrix[0][count] = (current1Row2SecondPosition * matrix[1][count]) - matrix[0][count];

//     }


//     double currentFirstPosition = matrix[0][0];

//     for(int count = 0; count < 3; count++)
//     {
//         if (currentFirstPosition != 0)
//         {
//             matrix[0][count] = (1/ currentFirstPosition) * matrix[0][count];

//         }
//     }


//     cout << " Row 1: " << endl;
//     cout << " First value: " << matrix[0][0] << " second value: " << matrix[0][1] << " third value: " << matrix[0][2] << endl;
//     cout << " Row 2: " << endl;
//     cout << " First value: " << matrix[1][0] << " second value: " << matrix[1][1] << " third value: " << matrix[1][2] << endl;

//     cout << " [" << matrix[0][0] << " " << matrix[0][1] << " " << matrix[0][2] << "]" << endl;
//     cout << " [" << matrix[1][0] << " " << matrix[1][1] << " " << matrix[1][2] << "]" << endl;

    






    
// }