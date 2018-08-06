//Bisection - Bolzano method
//Numerical solution of an equation of the form f(x) = 0

#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdlib>

using namespace std;

//Method's constant parameters
const double ACCURACY = 1E-8;
const short MAX_ITERATIONS = 500;
const short MAX_DIGITS = 8;

//Equation to be solved (f(x) = 0)
double f(double x)
{
    return pow(x,2)+sin(x)+exp(x)-2;
}

//Decides whether or not a root exists in [a,b]
bool Find(double a, double b)
{
    if (f(a)*f(b) < 0)
        return true;
    else if (f(a)*f(b) > 0)
        return false;
    else
    {
        if (f(a) == 0)
        {
            cout << "Root found : root = " << a << "  (error = 0)" << endl;
            exit(EXIT_SUCCESS);
        }
        else
        {
            cout << "Root found : root = " << b << "  (error = 0)" << endl;
            exit(EXIT_SUCCESS);
        }
    }
}

int main()
{
    cout << fixed << setprecision(MAX_DIGITS);

    double a,b;
    cout << "Define interval [a,b]" << "\n";
    cout << "a = "; cin >> a;
    cout << "b = "; cin >> b;
    if (a > b) //auto correct interval [b,a] -> [a,b]
    {
        double temp = a;
        a = b;
        b = temp;
    }
    else if (a == b)
    {
        cout << "Invalid interval. Exiting...\n";
        exit(EXIT_FAILURE);
    }
    double root, error = 9999.0; //Assuming a big initial error
    double temp;
    short count = 0; //number of iterations
    if (Find(a,b))
    {
        do
        {
            root = (a+b)/2.0;  if (count > 0) error = fabs(root - temp); //error = |x(n+1)-x(n)|
            temp = root;
            if (Find(a,root))
                b = root;
            else if (Find(root,b))
                a = root;
            count++;
        }
        while ((error > ACCURACY) && (count < MAX_ITERATIONS));
        cout << "root = " << root << endl;
        cout << "error = " << error << endl;
        cout << "iterations = " << count << endl;
    }
    else
        cout << "No root found in [a,b] \n\n";
    return 0;
}
