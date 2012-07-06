#include <iostream>
#include "Orbit.h"
#include "Lambert.h"
#include "Ephemeris.h"
#include "KeplersEquations.h"
#include "Conversions.h"
#include "Base.h"

/**
 * Main entry point.
 */
int main(int argc, char *argv[])
{
    Orbit orbit(ASTRO_MU_SUN);

    double eccentricity = 0.5;
    double M = 1000.0;
    double E = SolveKeplersEquationE(eccentricity, M);

    Vector3 initialPosition(2.5, 0.0, 0.0); // units are ER
    Vector3 finalPosition(1.915111, 1.606969, 0.0); // units are ER
    double timeOfFlight = 5 * 5.6519; // units are TU
    int numberRevolutions = 0;
    Vector3 initialVelocity, finalVelocity;
    LambertManager::SetLambertType(LAMBERT_EXP_SINUSOID);
    LambertManager::Evaluate(initialPosition, finalPosition, timeOfFlight, ORBIT_DIR_PROGRADE, numberRevolutions, &initialVelocity, &finalVelocity);

    int objectId = PLANET_EARTH;
    double epoch = 2455195;
    OrbitalElements orbitalElements;
    StateVector stateVector;
    EphemerisManager::SetEphemerisType(EPHEMERIS_ANALYTICAL);
    EphemerisManager::GetOrbitAtEpoch(objectId, epoch, &orbitalElements, &stateVector);

    orbit.SetStateVector(stateVector);
    OrbitType orbitType = orbit.GetType();
    OrbitalElements orbitalElements2 = orbit.GetOrbitalElements();

    StateVector stateVector2;
    ConvertOrbitalElements2StateVector(orbitalElements, &stateVector2);

    std::cin.get();
    return 0;
}