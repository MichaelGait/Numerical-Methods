//Approximating an integral value via Rectangle Method

#include<iostream>
#include<iomanip>
#include<vector>
#include<cstdlib>
#include<cmath>

using namespace std;

const short MAX_DIGITS = 10;
const double hACCURACY = 1E-4;

//The function that is to be integrated
//fix it
double f(double x)
{
    return sqrt(x);
}

void swap(double &a, double &b)
{
    double temp = a;
    a = b;
    b = temp;
}


double RectangleIntegration(double a, double b, const int N)
{
    double h; //Integration step
    if (N > 1) //The user is expected to count the number of points, STARTING FROM N=1
        h = abs((b-a)/((double)(N-1)));
    else
    {
        cout << "N = " << N << " is not a valid number of points for the current method.";
        cout << " Exiting...\n\n";
        exit(EXIT_FAILURE);
    }
    //if the integration limits are given upside down, then
    //the only thing that changes is the sign of the output value
    bool upsideDown = false;
    if (a > b) {swap(a,b); upsideDown = true;}

    double I = 0.0; //sum
    for (double x = a; x < (b - hACCURACY); x += h)
    {
        I = I + f(x);
    }
    I = I*h;
    if (upsideDown) return -I;
    else return I;
}

int main()
{
    cout << fixed << setprecision(MAX_DIGITS);

    double a,b; //Integration limits
    cout << "Define the integration limits a,b" << endl;
    cout << "a = "; cin >> a;
    cout << "b = "; cin >> b;
    if (a == b)
    {
        cout << "I = 0" << endl;
        exit(EXIT_SUCCESS);
    }
    int N; //Points on x-axis
    cout << "Division via a known number of N-points on x-axis.\n";
    cout << "N = "; cin >> N;
    double I = RectangleIntegration(a,b,N);
    cout << "I = " << I << endl;
    return 0;
}
