//Fixed point iteration x=g(x) method.
//Numerical solution of f(x) = 0
//g(x) and g'(x) are defined in the source code.
//The algorithm checks if g(x) satisfies the convergence theorem conditions.

#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdlib>

using namespace std;

//method's parameters
const double ACCURACY = 1E-7;
const double dx = 1E-4;
const short MAX_ITERATIONS = 100;
const short MAX_DIGITS = 8;

double g(double x) //g(x)
{
    return -sqrt(2*exp(x)/3);
}

double dg(double x) //g'(x)
{
    return -(1/sqrt(6))*exp(x/2);
}

//convergence theorem conditions.
//True if they're satisfied. False otherwise.
bool Conditions(const double a, const double b)
{
    for (double x = a; x <= b; x+=dx)
    {
        //x=g(x) method will NOT converge if one the
        //following conditions applies
        if (/*(g(x) < a) || (g(x) > b) || */fabs(dg(x) >= 1))
            return false;
    }
    return true;
}

int main()
{
    cout << fixed << setprecision(MAX_DIGITS);

    double a,b;
    cout << "Define interval [a,b] for root search\n";
    cout << "a = "; cin >> a;
    cout << "b = "; cin >> b;
    if (a > b)
    {
        //Auto correction
        double temp = a;
        a = b;
        b = temp;
    }

    double x0,x1;
    double error = 9999.0;
    short counter = 0; //counts iterations
    if (Conditions(a,b))
    {
        cout << "\ng(x) satisfies the convergence theorem conditions ";
        cout << "in [" << a << "," << b << "]\n";
        cout << "Beginning x = g(x) method\n";
        do // x0 validation
        {
            cout << "x0 = "; cin >> x0;
            if (x0 < a || x0 > b)
                cout << x0 << " doesn't belong to [" << a << "," << b << "]\n";
        }
        while (x0 < a || x0 > b);
        do //x = g(x) method
        {
            x1 = g(x0); error = fabs(x1 - x0); counter++;
            x0 = x1;
        }
        while ((error > ACCURACY) && (counter < MAX_ITERATIONS));
        cout << "root = " << x1 << endl;
        cout << "error = " << error << endl;
        cout << "counter = " << counter << endl;
    }
    else
    {
        cout << "g(x) doesn't satisfy the convergence theorem conditions ";
        cout << "in [" << a << "," << b << "]\n";
        cout << "\nExiting...\n\n";
    }
    return 0;
}

