//Gauss Elimination for an NxN system of linear equations
//Possible cases :
//Case 1: Unique solution
//Case 2: Infinite number of solutions
//Case 3: No solution at all

#include<iostream>
#include<cstdlib>
#include<cmath>

using namespace std;

const int N = 4; //Order

//Aa -> Augmented matrix of the system
void PrintSystem(float Aa[][N+1])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N+1; j++)
        {
            cout << Aa[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

void InputSystem(float Aa[][N+1])
{
    cout << "Expecting " << N*(N+1) << " number of data N*(N+1)\n\n";
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N+1; ++j)
        {
            cout << "a" << i << j << " = ";
            cin >> Aa[i][j];
        }
        cout << "\n";
    }
}

//Calculates the rank of the augmented matrix (Aa)
int rank_Aa(float Array[][N+1])
{
    int rank = N; //initial assumption
    for (int i = 0; i < N; i++)
    {
        int countZeros = 0;
        for (int j = 0; j < N+1; j++)
        {
            if (Array[i][j] == 0)
                countZeros++;
        }
        if (countZeros == N+1) //if all the elements of the i-row are zeros, then
            rank--;
    }
    return rank;
}

//Calculates the rank of the non - augmented matrix (A)
int rank_A(float Array[][N])
{
    int rank = N;
    for (int i = 0; i < N; i++)
    {
        int countZeros = 0;
        for (int j = 0; j < N; j++)
        {
            if (Array[i][j] == 0)
                countZeros++;
        }
        if (countZeros == N) //if all the elements of the i-row are zeros, then
            rank--;
    }
    return rank;
}

void GaussElimination(float Aa[][N+1])
{
    for (int i = 0; i < N; i++)
    {
        //Search for maximum in this column
        float max = fabs(Aa[i][i]);
        int row = i;
        for (int k = i+1; k < N; k++)
        {
            if (fabs(Aa[k][i]) > max)
            {
                max = fabs(Aa[k][i]);
                row = k;
            }
        }

        //Swap maximum row with current row (column by column)
        for (int k = i; k < N+1; k++)
        {
            float temp = Aa[row][k];
            Aa[row][k] = Aa[i][k];
            Aa[i][k] = temp;
        }

        //Make all rows below this one 0 in current column
        for (int k = i+1; k < N; k++)
        {
            float c = -Aa[k][i]/Aa[i][i];
            for (int j = i; j < N+1; j++)
            {
                if (i==j)
                    Aa[k][j] = 0;
                else
                    Aa[k][j] += c*Aa[i][j];
            }
        }
    }
    //Now A is upper triangular.

    float A[N][N];
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
                A[i][j] = Aa[i][j];
        }
    }
    PrintSystem(Aa);

    //Checking for solvability of the system considering the ranks
    if (rank_Aa(Aa) != rank_A(A))
    {
        cout << "rank(Aa) = " << rank_Aa(Aa) << endl;
        cout << "rank(A) = " << rank_A(A) << endl;
        cout << "rank(Aa) != rank(A)\n";
        cout << "No solution exists. Exiting...\n\n";
        exit(EXIT_FAILURE);
    }
    int parameters = N - rank_Aa(Aa);
    if (parameters > 0)
    {
        cout << "\n\nThe solution contains " << parameters << " parameter(s).";
        cout << " Infinite number of solutions. Exiting...\n\n";
        exit(EXIT_FAILURE);
    }

    //Back substitution
    float sol[N];
    for (int i = N-1; i >= 0; i--)
    {
        sol[i] = Aa[i][N]/Aa[i][i];
        for (int k = i-1; k >= 0; k--)
            Aa[k][N] -= Aa[k][i]*sol[i];
    }
    //Print the solution
    for (int i = 0; i < N; i++)
        cout << "x[" << i << "] = " << sol[i] << endl;
}

//Driver function
int main()
{
    float Aa[N][N+1]; //Augmented matrix
    InputSystem(Aa);
    PrintSystem(Aa);
    GaussElimination(Aa);
    return 0;
}