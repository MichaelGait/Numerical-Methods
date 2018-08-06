//Lagrange interpolating polynomial
//Input : values (xi,f(xi))
//Output : values P(xi) ~ f(xi)

#include<fstream>
#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdlib>
#include<string>

const double pi = 3.141592653;
const double interpolationStep = 1E-2;
const short MAX_DIGITS = 4;
const short NDATA = 11;

using namespace std;

//If the input data are calculated from a function,
//then the function is the following (fix it)
double func(double k)
{
    return 1/(1+pow(k,2));
}

//Either reads the data from a known (x,y) - table
//or reads x and calculates y from func()
void InputData(double *x, double *f)
{
    cout << "How are the data going to be stored?  (function/table) : ";
    string choice;  cin >> choice;
    if (choice == "function" || choice == "Function" || choice == "FUNCTION")
    {
        for (int i = 0; i < NDATA; i++)
        {
            cout << "\nx[" << i << "] = "; cin >> x[i];
            f[i] = func(x[i]); cout << "f[" << i << "] = " << f[i] << endl;
        }
    }
    else if (choice == "table" || choice == "Table" || choice == "TABLE")
    {
        for (int i = 0; i < NDATA; i++)
        {
            cout << "\nx[" << i << "] = "; cin >> x[i];
            cout << "f[" << i << "] = "; cin >> f[i];
        }
    }
    else
    {
        cout << "Wrong type of data storing. Exiting...\n";
        exit(EXIT_FAILURE);
    }
}

//Forming the term Li(x)
double Lagrange(double *x, double point, int i)
{
    double L = 1;
    for (int j = 0; j < NDATA; j++)
        if (j!=i)
            L *= (point - x[j])/(x[i] - x[j]);
    return L;
}

//Calculates pairs of (x,P(x)) and prints them in a selected
//file named 'Results.txt'. By plotting those pairs (x,P(x)), we
//get the demanded Lagrange polynomial P(x) ~ func(x)
void InterpolateMany(double *x, double *f)
{
    double a,b;
    cout << "\nInterval [a,b] in which the interpolation will take place\n";
    cout << "a = "; cin >> a;
    cout << "b = "; cin >> b;
    ofstream Polynomial; Polynomial.open("Results.txt");
    //Polynomial << "x,\tP(x)\n\n";
    for (double point = a; point <= b; point += interpolationStep)
    {
        double P = 0;
        for (int i = 0; i < NDATA; i++)
        {
            P +=  f[i]*Lagrange(x, point, i);
        }
        Polynomial << point << "\t" << P << endl;
    }
    cout << "\nResults were calculated in 'Results.txt' file\n";
    Polynomial.close();
}

//Approximates only one value of func() with the interpolating
//polynomial in a specific x (point) that is decided by the user.
void InterpolateOne(double *x, double *f)
{
    double point, P = 0;
    cout << "Interpolation point x : "; cin >> point;
    for (int i = 0; i < NDATA; i++)
    {
        P += + f[i]*Lagrange(x, point, i);
    }
    cout << "\n\nInterpolating value (in x = " << point << ") = " << P << endl;
}

int main()
{
    cout << fixed << setprecision(MAX_DIGITS);

    cout << "Expecting " << NDATA << " pairs of data" << endl;
    double x[NDATA], f[NDATA];
    InputData(x,f);

    cout << "\nHow many interpolating values?  (one/many) : ";
    string choice;  cin >> choice;
    if (choice == "many" || choice == "Many" || choice == "MANY")
        InterpolateMany(x,f);
    else if (choice == "one" || choice == "One" || choice == "ONE")
        InterpolateOne(x,f);
    else
    {
        cout << "\nWrong type of interpolation. Exiting...\n";
        exit(EXIT_FAILURE);
    }
    return 0;
}
