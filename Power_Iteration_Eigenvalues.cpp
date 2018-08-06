//Power iteration method for an (NxN) matrix
//Computes the largest (in absolute value) eigenvalue
//and the corresponding eigenvector

#include<iostream>
#include<iomanip>
#include<cstdlib>
#include<cmath>

using namespace std;

//Method's constants
const double ACCURACY = 1E-3;
const int MAX_DIGITS = 5;
const int N = 4;
const int MAX_COUNT = 80; //Max iterations permitted

//Finds the maximum in absolute value coordinate of the eigenvector
//Returns a signed number. NOT the absolute value (unsigned)
double AbsMax(double *x)
{
    double max = fabs(x[0]);
    int position = 0;
    for (int i = 1; i < N; ++i)
        if (fabs(x[i]) > max)
        {
            max = fabs(x[i]);
            position = i;
        }
    if (x[position] > 0)
        return max;
    else
        return -max;
}

//All that is needed is A and an initial eigenvector
void PowerIterationMethod(double A[][N], double *x0)
{
    double x1[N]; // x0[] corresponds to x_k and x1[] corresponds to x_(k+1)
    double eigenValue0 = 1E5;
    double eigenValue1 = 1E5;
    int count = 0; //Total iterations
    do
    {
        eigenValue0 = eigenValue1;
        for (int i = 0; i < N; ++i)
        {
            double sum = 0;
            for (int j = 0; j < N; ++j)
                sum += A[i][j]*x0[j];
            x1[i] = sum;
        }
        eigenValue1 = AbsMax(x1)/AbsMax(x0);
        for (int i = 0; i < N; ++i)
            x0[i] = x1[i];
        count++;
    }
    while ((fabs(eigenValue0 - eigenValue1) >= ACCURACY) && (count <= MAX_COUNT));

    if (count > MAX_COUNT)
    {
        cout << "\nPower iteration method did not converge.\n";
        cout << "Maybe another initial vector x0 would change that. Exiting...\n\n";
        exit(EXIT_FAILURE);
    }
    else
    {
        cout << " \neigenValue = " << eigenValue1 << "\n\n";
        cout << "Corresponding eigenvector's coordinates : \n";
        double m = AbsMax(x1);
        for (int i = 0; i < N; ++i)
        {
            //Normalization of the eigenvector
            x1[i] = x1[i]/m;
            cout << "  x" << i+1 << " = " << x1[i] << endl;
        }
    }
}

int main()
{
    cout << fixed << setprecision(MAX_DIGITS);

    double A[N][N], x0[N];
    cout << "Expecting " << N*N << " number of data (N*N)\n\n";
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            cout << "a" << i+1 << j+1 << " = ";
            cin >> A[i][j];
        }
        cout << "\n";
    }
    for (int i = 0; i < N; ++i)
    {
        cout << "x0[" << i+1 << "] = ";
        cin >> x0[i];
    }
    PowerIterationMethod(A,x0);
    return 0;
}
