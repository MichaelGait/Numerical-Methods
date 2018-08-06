//y' = f(x,y) -> y_k+1 = y_k + h*f(x,y)
//Approximating an ODE's solution with Euler's method (Taylor's 1st order)
//Constant step h

#include<iostream>
#include<fstream>
#include<iomanip>
#include<cmath>
#include<cstdlib>

using namespace std;

const double h = 0.25; //step

double f(double x, double y)
{
    return y*pow(x,2) - 1.1*y;
}

void EulerMethod(const double a, const double b, double y0)
{
    double y1; //next value y
    ofstream ODEdata;
    ODEdata.open("Results_Euler.txt");
    ODEdata << "x\ty\n\n";
    for (double x = a; x <= b; x += h)
    {
        y1 = y0 + h*f(x,y0);
        ODEdata << x << "\t" << y0 << endl;
        y0 = y1;
    }
    ODEdata << "\n\nh = " << h;
    cout << "Results were calculated in 'Results_Euler.txt' file\n";
    ODEdata.close();
}

int main()
{
    double a,b; //interval limits
    cout << "Define interval [a,b] in which the ODE will be solved" << endl;
    cout << "a = "; cin >> a;
    cout << "b = "; cin >> b;
    if (a > b)
    {
        //Auto correction
        double temp = a;
        a = b;
        b = temp;
    }
    else if (a == b)
    {
        cout << "Invalid interval. Exiting...\n\n";
        exit(EXIT_FAILURE);
    }
    double y0; //initial condition y(a)
    cout << "Initial condition y(" << a << ") = "; cin >> y0;
    EulerMethod(a,b,y0);

    return 0;
}
