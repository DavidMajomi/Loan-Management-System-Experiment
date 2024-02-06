
double calculateMatrixBasedALVS(double rowOneColumnOne, double rowOneColumnTwo, double rowOneColumnThree, double rowTwoColumnOne, 
                            double rowTwoColumnTwo, double rowTwoColumnThree, double loanViabilityScore)
{
    static int counter = 0;
    static bool hasBeenRunTwice = false;

    // For y = mx + b where y = alvs, m = slope, x = lvs
    static double m = 0;
    static double b = 0;
    double matrixBasedALVS;

    double matrix[2][3];

    matrix[0][0] = rowOneColumnOne;
    matrix[0][1] = rowOneColumnTwo;
    matrix[0][2] = rowOneColumnThree;
    matrix[1][0] = rowTwoColumnOne;
    matrix[1][1] = rowTwoColumnTwo;
    matrix[1][2] = rowTwoColumnThree;

    double firstPosition = matrix[0][0];
    // cout << endl;

    // cout << " [" << matrix[0][0] << " " << matrix[0][1] << " " << matrix[0][2] << "]" << endl;
    // cout << " [" << matrix[1][0] << " " << matrix[1][1] << " " << matrix[1][2] << "]" << endl;


    for(int count = 0; count < 3; count++)
    {
        if(firstPosition != 0)
        {

            matrix[0][count] = (1 / firstPosition) * matrix[0][count];
        }

    }

    double currentRowOneColumnOne = matrix[0][0];

    // cout << endl;

    // cout << " [" << matrix[0][0] << " " << matrix[0][1] << " " << matrix[0][2] << "]" << endl;
    // cout << " [" << matrix[1][0] << " " << matrix[1][1] << " " << matrix[1][2] << "]" << endl;


    for(int count = 1; count < 2; count++)
    {
        for(int j = 0; j < 3; j++)
        {
            matrix[count][j] = ((rowTwoColumnOne * matrix[count -1][j])) - ((currentRowOneColumnOne * matrix[count][j]));
        }

    }

    double currentRow2FirstPosition = matrix[1][0];

    // cout << endl;

    // cout << " [" << matrix[0][0] << " " << matrix[0][1] << " " << matrix[0][2] << "]" << endl;
    // cout << " [" << matrix[1][0] << " " << matrix[1][1] << " " << matrix[1][2] << "]" << endl;

    for(int count = 0; count < 3; count++)
    {
        if(currentRow2FirstPosition != 0)
        {
            matrix[1][count] = (1 / currentRow2FirstPosition) * matrix[1][count];
        }
    }

    double currentRowTwoColumnTwo = matrix[1][1];

    // cout << endl;

    // cout << " [" << matrix[0][0] << " " << matrix[0][1] << " " << matrix[0][2] << "]" << endl;
    // cout << " [" << matrix[1][0] << " " << matrix[1][1] << " " << matrix[1][2] << "]" << endl;

    for (int count = 1; count < 3; count++)
    {
        matrix[1][count] = (1 / currentRowTwoColumnTwo) * (matrix[1][count]);

    }

    firstPosition = matrix[0][0];

    // cout << endl;

    // cout << " [" << matrix[0][0] << " " << matrix[0][1] << " " << matrix[0][2] << "]" << endl;
    // cout << " [" << matrix[1][0] << " " << matrix[1][1] << " " << matrix[1][2] << "]" << endl;


    for (int count = 0; count < 3; count++)
    {
        if(firstPosition != 0)
        {
            matrix[0][count] = (1 / firstPosition * matrix[0][count]);
        }

    }

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
    
    // cout << endl;

    // cout << " [" << matrix[0][0] << " " << matrix[0][1] << " " << matrix[0][2] << "]" << endl;
    // cout << " [" << matrix[1][0] << " " << matrix[1][1] << " " << matrix[1][2] << "]" << endl;


    m = matrix[0][2];
    b = matrix[1][2];
    
    // cout << " This is m: " << m << " This is b: " << b << endl;

    matrixBasedALVS = (loanViabilityScore * m) + b;

    return matrixBasedALVS;
}

