#include "Utility.h"
#include "Base.h"

double SolveKeplersEquationE(double ecc, double M)
{
    double E; // eccentric anomaly (radians)
    if (M < MATH_PI)
    {
        E = M + 0.5*ecc;
    }
    else
    {
        E = M - 0.5*ecc;
    }
 
    int counter = 0;
    const int MAX_COUNTER = 10000; // The max number of iteration attempts allowed.

    double ratio = 1.0;
    while (fabs(ratio) > MATH_EPSILON && counter < MAX_COUNTER)
    {
        ratio = (M - E + ecc*sin(E)) / (1 - ecc*cos(E));
        E += ratio;
        counter++;
    }

    if (counter >= MAX_COUNTER)
    {
        // log error
        throw "Iteration limit exceeded.";
    }

    return E;
}