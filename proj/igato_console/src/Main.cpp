#include <iostream>
#include "Orbit.h"
#include "Lambert.h"
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

    Vector3 initialPosition(2.5, 0.0, 0.0); // units are ER
    Vector3 finalPosition(1.915111, 1.606969, 0.0); // units are ER
    double timeOfFlightDays = 5 * 5.6519; // units are TU
    int numberRevolutions = 0;

    Vector3 initialVelocity, finalVelocity;

    Lambert::ExponentialSinusoids(initialPosition, finalPosition, timeOfFlightDays, Prograde, 1, &initialVelocity, &finalVelocity);

    std::cin.get();
    return 0;
}