#include <iostream>
#include "Orbit.h"
#include "KeplersEquations.h"
#include "Base.h"

/**
 * Main entry point.
 */
int main(int argc, char *argv[])
{
    Orbit orbit(ASTRO_MU_SUN);

    double ecc = 0.5;
    double M = 1000.0;
    double E = SolveKeplersEquationE(ecc, M);

    std::cin.get();
    return 0;
}