//Regula - Falsi method for solving an equation f(x) = 0

#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdlib>

using namespace std;

//Method's constants.
const double ACCURACY = 1E-18;
const short MAX_ITERATIONS = 50;
const short MAX_DIGITS = 19;
const double dx = 1E-3;

double f(double x) //equation to be solved
{
    return pow(x,3) +2*pow(x,2) -3*x - 1;
}

//Determines if [a,b] contains a root.
//If it does, then main() proceeds to Regula - Falsi
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
            cout << "Root found : root = " << b << "   (error = 0)" << endl;
            exit(EXIT_SUCCESS);
        }
    }
}

int main()
{
    cout << fixed << setprecision(MAX_DIGITS);

    double a,b;
    cout << "Define interval [a,b]" << "\n\n";
    cout << "a = "; cin >> a;
    cout << "b = "; cin >> b;
    if (a > b)
    {
        //auto correct
        double temp = a;
        a = b;
        b = temp;
    }

    double root; //final estimation
    double error = 9999.0; //Assuming a big initial error
    double temp;
    short count = 0;
    if (Find(a,b))
    {
        do
        {
            root = b - f(b)*((b-a)/(f(b)-f(a)));
            if (count > 0) error = fabs(root - temp); // error = |x(n+1) - x(n)|
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
        cout <<  "No root found. Exiting...\n\n";
    return 0;
}