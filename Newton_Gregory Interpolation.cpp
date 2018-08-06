//Newton - Gregory interpolating polynomial
//Input : values (xi,f(xi))
//Output : values P(xi) ~ f(xi)
//Points step h has to be constant

#include<fstream>
#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdlib>
#include<string>

const double interpolationStep = 1E-3;
const short MAX_DIGITS = 4;
const short NDATA = 6;

using namespace std;

//If the input data are calculated from a function,
//then the function is the following (fix it)
double func(double k)
{
    return k;
}

//Returns the factorial of a non-negative integer
long factorial(int number)
{
    if (number == 0) return 1;

    long fact = 1;
    for (int p = 1; p <= number; p++)
        fact *= p;
    return fact;
}

//Returns the binomial coefficient
double Combine(double rpoint, int i)
{
    double product = 1.0;
    for (int j = 1; j <= i; j++)
        product *= rpoint - i + j;
    return product/factorial(i);
}

//Returns the forward difference of i-order
double Delta(double *f, int i)
{
    double sum = 0.0;
    for (int j = 0; j <= i; j++)
        sum += pow(-1,j)*f[i-j]*factorial(i)/(factorial(j)*factorial(i-j));
    return sum;
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

//Verifies that the x-step (h) is constant
void Check_h(double *x)
{
    for (int i = 0; i < NDATA - 1; ++i)
    {
        if ((float)(x[i+1]-x[i]) != (float)(x[1]-x[0]))
        {
            cout << "Non constant step h detected. ";
            cout << "Newton's interpolation cannot apply. Exiting...\n\n";
            exit(EXIT_FAILURE);
        }
    }
}

//Calculates pairs of (x,P(x)) and prints them in a selected
//file named 'Results.txt'. By plotting those pairs (x,P(x)), we
//get the demanded Newton polynomial P(x) ~ func(x)
void InterpolateMany(double *x, double *f, const double h)
{
    double a,b;
    cout << "\nInterval [a,b] in which the interpolation will take place\n\n";
    cout << "a = "; cin >> a;
    cout << "b = "; cin >> b;
    ofstream Polynomial; Polynomial.open("Results.txt");
    Polynomial << "x,\tP(x)\n\n";
    for (double point = a; point <= b; point += interpolationStep)
    {
        double P = 0;
        double rpoint = (point - x[0])/h;
        for (int i = 0; i < NDATA; i++)
        {
            P += Combine(rpoint,i)*Delta(f,i);
        }
        Polynomial << point << "\t" << P << endl;
    }
    cout << "\nResults were calculated in 'Results.txt' file\n";
    Polynomial.close();
}

//Approximates only one value of func() with the interpolating
//polynomial in a specific x (point) that is decided by the user.
void InterpolateOne(double *x, double *f, const double h)
{
    double point, P = 0;
    cout << "Interpolation point x : "; cin >> point;
    double rpoint = (point - x[0])/h;
    for (int i = 0; i < NDATA; i++)
    {
        P = P + Combine(rpoint,i)*Delta(f,i);
    }
    cout << "\n\nInterpolating value (in x = " << point << ") = " << P << endl;
}

int main()
{
    cout << fixed << setprecision(MAX_DIGITS);

    cout << "Expecting " << NDATA << " pairs of data" << endl;
    double x[NDATA], f[NDATA];
    InputData(x,f);
    Check_h(x);
    const double h = fabs(x[1]-x[0]);

    cout << "\nHow many interpolating values?  (one/many) : ";
    string choice;  cin >> choice;
    if (choice == "many" || choice == "Many" || choice == "MANY")
        InterpolateMany(x,f,h);
    else if (choice == "one" || choice == "One" || choice == "ONE")
        InterpolateOne(x,f,h);
    else
    {
        cout << "\nWrong type of interpolation. Exiting...\n";
        exit(EXIT_FAILURE);
    }
    return 0;
}