//Gauss-Seidel iterative method for an NxN system of linear equations
//The algorithm checks whether the matrix is diagonally dominant or not

#include<iostream>
#include<cstdlib>
#include<cmath>

using namespace std;

const int N = 5; //Order of the system
const int MAX_ITERATIONS = 10; //method iterations

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

void GaussSeidel(float Aa[][N+1])
{
    //check diagonal dominance
    for (int i = 0; i < N; i++)
    {
        float sum = 0.0;
        for (int j = 0; j < N; j++)
        {
            if (i!=j)
                sum += abs(Aa[i][j]);
        }
        if (abs(Aa[i][i]) < sum)
        {
            cout << "Non diagonally dominant matrix as input. Method might not converge.\n";
            cout << "Exiting...\n";
            exit(EXIT_FAILURE);
        }
    }
    //assume an initial solution x[]
    float x[N];
    for (int i = 0; i < N; i++)
        x[i] = 0.0; //initial assumption
    //repeat the method for a certain number of iterations
    for (int k = 0; k < MAX_ITERATIONS; k++)
    {
        //Gauss-Seidel method
        for (int i = 0; i < N; i++)
        {
            float sum = 0.0;
            for (int j = 0; j < N; j++)
            {
                if (i!=j)
                {
                    sum += Aa[i][j]*x[j];
                }
            }
            x[i] = (Aa[i][N] - sum)/Aa[i][i];
        }
    }
    //print the estimated solution x[]
    for (int i = 0; i < N; i++)
        cout << "x[" << i << "] = " << x[i] << endl;
}

int main()
{
    float Aa[N][N+1]; //Augmented matrix
    InputSystem(Aa);
    PrintSystem(Aa);
    GaussSeidel(Aa);
    return 0;
}
