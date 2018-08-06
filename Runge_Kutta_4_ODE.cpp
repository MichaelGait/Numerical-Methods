#include<fstream>
#include<iomanip>
#include<cmath>
#include<cstdlib>

using namespace std;

const double h = 0.1; //step

double f(double x, double y)
{
    return y*pow(x,2) - 1.1*y;
}

void RungeKutta4(const double a, const double b)
{
    double y0; //initial condition
    cout << "Initial condition y(" << a << ") = "; cin >> y0;
    double y1;
    double k1,k2,k3,k4;
    cout << "Please wait while calculating...\n";
    ofstream ODEdata;
    ODEdata.open("Results_RK4.txt");
    ODEdata << "x\ty\n\n";
    for (double x = a; x <= b; x += h)
    {
        k1 = f(x,y0);
        k2 = f(x + h/2, y0 + (h/2)*k1);
        k3 = f(x + h/2, y0 + (h/2)*k2);
        k4 = f(x + h, y0 + h*k3);

        y1 = y0 + (h/6)*(k1 + 2*k2 + 2*k3 + k4);
        ODEdata << x << "\t" << y0 << endl;
        y0 = y1;
    }
    ODEdata << "\n\nh = " << h;
    cout << "Results were calculated in 'Results_RK4.txt' file\n";
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
    RungeKutta4(a,b);
    return 0;
}