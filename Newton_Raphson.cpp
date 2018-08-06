//Newton - Raphson method
//f(x) and f'(x) are defined in the source code
//The program checks [a,b] in which the method is applied
//Checks either f'(x) == 0 or f'(x) ~ 0 and acts appropriately

#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdlib>
#include<string>

using namespace std;

//Method's parameters
const double ACCURACY = 1E-10;
const double dx = 1E-3;
const double MIN_GRADIENT = 5E-2;
const short MAX_ITERATIONS = 50;
const short MAX_DIGITS = 10;

double f(double x) //f(x)
{
    return 2*exp(x)-3*pow(x,2);
}

double df(double x) //f'(x)
{
    return 2*exp(x)-6*x;
}

void NewtonRaphson(const double a, const double b)
{
    //Prediction for slow convergence or
    //no convergence at all
    for (double x = a; x <= b; x+=dx)
    {
        if (fabs(df(x)) <= MIN_GRADIENT) //f'(x)~0
        {
            cout << "Avoid the region near " << x << " Method might not converge.";
            cout << "f'(" << x << ") ~ 0" << endl;
        }
    }
    double x0, x1; //Initial guess, final guess (root estimation)
    double error = 9999.0; //Assuming a nonsense - long initial error
    short counter = 0; //counts iterations
    do // x0 validation
    {
        cout << "x0 = "; cin >> x0;
        if (x0 < a || x0 > b)
            cout << x0 << " does not belong to [" << a << "," << b << "]\n";
    }
    while (x0 < a || x0 > b);
    short tmp = 1;
    do
    {
        if (df(x0) == 0)
        {
            cout << "f'(x0 = " << x0 << ") = 0" << endl;
            cout << "Method cannot be applied. Exiting...\n\n";
            exit(EXIT_FAILURE);
        }
        x1 = x0 - f(x0)/df(x0); //N-R sequence
        if ((x1 < a || x1 > b) && (tmp == 1))
        {
            cout << "x1 exceeded [a,b] during the calculation and function f(x)\n";
            cout << "might not be defined outside [a,b]. The method will proceed.\n";
            cout << "In case 'nan' or 'inf' arises, consider the method as a failure.\n";
            tmp++;
        }
        error = fabs(x1-x0);
        counter++;
        x0 = x1;
    }
    while ((error > ACCURACY) && (counter < MAX_ITERATIONS));
    if(counter < MAX_ITERATIONS)
    {
        cout << "root = " << x1 << endl;
        cout << "error = " << error << endl;
        cout << "counter = " << counter << endl;
    }
    else
        cout << "Method failed\n\n";
}

int main()
{
    cout << fixed << setprecision(MAX_DIGITS);

    double a,b;
    cout << "Define interval [a,b]" << "\n";
    cout << "a = "; cin >> a;
    cout << "b = "; cin >> b;
    if (a > b) //auto correct [b,a] -> [a,b]
    {
        double temp = a;
        a = b;
        b = temp;
    }
    NewtonRaphson(a,b);
    return 0;
}
