#pragma once

/// Solver Keplers Equation for elliptical orbits.
/**
 This routine computes the eccentric anomaly of an elliptical orbit using the mean anomaly and eccentricity.
 Kepler's Equation is a transendental equation which is solved using Newton-Raphson iteration.

 Reference: Fundamentals of Astrodynamics and Applications 3rd Edition, David Vallado, Algorithm 2.

 @param ecc : The eccentricity.
 @param M : The mean anomaly (radians).
 @returns : The eccentric anomaly (radians).
*/
double SolveKeplersEquationE(double ecc, double M);