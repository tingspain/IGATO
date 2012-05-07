#pragma once

/// Solves Keplers Equation for elliptical orbits.
/**
 This routine computes the eccentric anomaly of an elliptical orbit using the eccentricity and mean anomaly.
 Kepler's Equation is a transendental equation which is solved using Newton-Raphson iteration. An exception
 is thrown if more than 10,000 iterations are performed.

 Reference: Fundamentals of Astrodynamics and Applications 3rd Edition, David Vallado, Algorithm 2.

 @param ecc : The eccentricity.
 @param M : The mean anomaly (radians).
 @returns : The eccentric anomaly (radians).
*/
double SolveKeplersEquationE(double ecc, double M);

/// Solves Keplers Equation for hyperbolic orbits.
/**
 This routine computes the hyperbolic anomaly of an hyperbolic orbit using the eccentricity and mean anomaly.
 Kepler's Equation is a transendental equation which is solved using Newton-Raphson iteration. An exception
 is thrown if more than 10,000 iterations are performed.

 Reference: Fundamentals of Astrodynamics and Applications 3rd Edition, David Vallado, Algorithm 4.

 @param ecc : The eccentricity.
 @param M : The mean anomaly (radians).
 @returns : The hyperbolic anomaly (radians).
*/
double SolveKeplersEquationH(double ecc, double M);