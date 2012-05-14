/*****************************************************************************
 *   IGATO - Interplanetary Gravity Assist Trajectory Optimizer              *
 *   Copyright (C) 2012 Jason Bryan (Jmbryan10@gmail.com)                    *
 *                                                                           *
 *   IGATO is free software; you can redistribute it and/or modify           *
 *   it under the terms of the GNU General Public License as published by    *
 *   the Free Software Foundation; either version 2 of the License, or       *
 *   (at your option) any later version.                                     *
 *                                                                           *
 *   IGATO is distributed in the hope that it will be useful,                *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 *   GNU General Public License for more details.                            *
 *                                                                           *
 *   You should have received a copy of the GNU General Public License       *
 *   along with IGATO; if not, see http://www.gnu.org/licenses/              *
 *****************************************************************************/

#include "Lambert.h"

namespace Lambert
{

void ExponentialSinusoids(const Vector3& initialPosition,
                          const Vector3& finalPosition,
                          double timeOfFlight,
                          OrbitDirection orbitDirection,
                          int numberRevolutions,
                          Vector3* initialVelocity,
                          Vector3* finalVelocity)
{
    assert(timeOfFlight > 0.0);
    assert(orbitDirection == Prograde || orbitDirection == Retrograde);

    // Non-dimensional units
    double R, V, T;
    R = initialPosition.length();
    V = sqrt(1.0 / R);
    T = R / V;

     // Non-dimensionalize the position vectors
    static Vector3 R1, R2;
    R1 = initialPosition;
    R2 = finalPosition;
    R1 *= 1.0 / R;
    R2 *= 1.0 / R;

    double r2 = R2.length();

    // Non-dimensionalize the time of flight
    double tof = timeOfFlight / T;

    // Cross product of initial and final position.
    static Vector3 CrossR1R2;
    Vector3::cross(R1, R2, &CrossR1R2);
    double crossR1R2 = CrossR1R2.length();

    double theta = acos(R1.dot(R2) / r2);

    // Direction of travel
    if (orbitDirection == Prograde && CrossR1R2.z <= 0.0)
    {
        theta = MATH_2_PI - theta;
    }
    else if (orbitDirection == Retrograde && CrossR1R2.z >= 0.0)
    {
        theta = MATH_2_PI - theta;
    }

    int longway = 1.0;
    if (theta > MATH_PI)
    {
        longway = -1.0;
    }

    double c      = sqrt(1.0 + r2*r2 - 2.0*r2*cos(theta));
    double s      = 0.5*(1.0 + r2 + c);
    double aMin   = 0.5*s;
    double lambda = sqrt(r2)*cos(0.5*theta)/s;

    double input1 = -0.5233;
    double input2 =  0.5233;
    double x1     = log(1.0 + input1);
    double x2     = log(1.0 + input2);

    double logt   = log(tof);

    double y1, y2;
    CalculateTimeOfFlight(input1, s, c, longway, numberRevolutions, &y1);
    CalculateTimeOfFlight(input2, s, c, longway, numberRevolutions, &y2);
    y1 = log(y1) - logt;
    y2 = log(y2) - logt;

    // Newton-Raphson iteration
    double error = 1.0;
    int iteration = 0;
    double xnew, ynew, x;
    while (error > MATH_TOLERANCE && iteration < 60)
    {
        xnew = (x1*y2 - y1*x2) / (y2 - y1);
        if (numberRevolutions == 0)
        {
            x = exp(xnew) - 1.0;
        }
        else
        {
            x = 2.0 * MATH_1_OVER_PI * atan(xnew);
        }

        CalculateTimeOfFlight(x, s, c, longway, numberRevolutions, &ynew);

        if (numberRevolutions == 0)
        {
            ynew = log(ynew) - logt;
        }
        else
        {
            ynew = ynew - tof;
        }

        x1 = x2;    x2 = xnew;
        y1 = y2;    y2 = ynew;

        error = abs(x1 - xnew);
        iteration++;
    }

    double a = aMin / (1.0 - x*x);

    double alpha, beta, sinpsi, sinhpsi, eta, eta2;
    if (x < 1.0) // ellipse
    {
        alpha   = 2.0 * acos(x);
        beta    = 2.0 * longway * asin(sqrt(0.5 * (s - c) / a));
        sinpsi  = sin(0.5 * (alpha - beta));
        eta2    = 2.0 * a * sinpsi * sinpsi / s;
        eta     = sqrt(eta2);
    }
    else // hyperbolic
    {
        alpha   = 2.0 * acosh(x);
        beta    = 2.0 * longway * asinh(sqrt(0.5 * (c - s) / a));
        sinhpsi = sinh(0.5 * (alpha - beta));
        eta2    = -2.0 * a * sinhpsi * sinhpsi / s;
        eta     = sqrt(eta2);
    }

    static Vector3 Ih, R2u;
    Ih = (longway / crossR1R2) * CrossR1R2; 
    R2u = R2;
    R2u.normalize();

    static Vector3 CrossIhR1, CrossIhR2u;
    Vector3::cross(Ih, R1, &CrossIhR1);
    Vector3::cross(Ih, R2u, &CrossIhR2u);

    double sinHalfTheta = sin(0.5 * theta);

    // Radial and tangential departure velocity
    double vr1 = (1.0 / eta / sqrt(aMin)) * ((2.0 * lambda * aMin) - lambda - (x * eta));
    double vt1 = sqrt((r2 / aMin / eta2) * (sinHalfTheta * sinHalfTheta));

    // Radial and tangential arr1val velocity
    double vt2 = vt1 / r2;
    double vr2 = (vt1 - vt2) / tan(0.5 * theta) - vr1;

    // Velocity vectors
    *initialVelocity = V * ((vr1 * R1)  + (vt1 * CrossIhR1));
    *finalVelocity =   V * ((vr2 * R2u) + (vt2 * CrossIhR2u));
}

void CalculateTimeOfFlight(double x, double s, double c, int longway, double N, double* tof)
{
    double a = 0.5*s / (1.0 - x*x);
    
    double alpha, beta;   
    if (x < 1.0) // ellipse
    {
        alpha = 2.0*acos(x);
        beta  = 2.0*longway*asin(sqrt(0.5*(s - c) / a));
        *tof  = a*sqrt(a)*((alpha - sin(alpha)) - (beta - sin(beta)) + MATH_2_PI * N); 
    }
    else // hyperbola
    {
        alpha = 2.0*acosh(x);
        beta  = 2.0*longway*asinh(sqrt(-0.5*(s - c) / a));
        *tof  = -a*sqrt(-a)*((sinh(alpha) - alpha) - (sinh(beta) - beta));
    }
}

void BattinsMethod(const Vector3& initialPosition,
                   const Vector3& finalPosition,
                   double timeOfFlightDays,
                   OrbitDirection orbitDirection,
                   int numberRevolutions,
                   Vector3* initialVelocity,
                   Vector3* finalVelocity)
{
}

void UniversalVariables(const Vector3& initialPosition,
                        const Vector3& finalPosition,
                        double timeOfFlightDays,
                        OrbitDirection orbitDirection,
                        int numberRevolutions,
                        Vector3* initialVelocity,
                        Vector3* finalVelocity)
{
    // Convert time of flight from days to seconds.
    double tofSeconds = timeOfFlightDays * MATH_DAY_TO_SEC;

     // Position vectors and magnitudes.
    const Vector3& Ri = initialPosition;
    const Vector3& Rf = finalPosition;
    double r1 = Ri.length();
    double r2 = Rf.length();

    // Cross product of initial and final position.
    static Vector3 C;
    Vector3::cross(Ri, Rf, &C);

    // True anomaly
    double theta = acos(Ri.dot(Rf) / r1 / r2);

    // Direction of travel
    if (orbitDirection == Prograde && C.z <= 0.0)
    {
        theta = MATH_2_PI - theta;
    }
    else if (orbitDirection == Retrograde && C.z >= 0.0)
    {
        theta = MATH_2_PI - theta;
    }

    double A = sin(theta) * sqrt(r1 * r2 / (1.0 - cos(theta)));
    
    double z = -1.0;
}

void UniversalVariablesGPU(const Vector3& initialPosition,
                           const Vector3& finalPosition,
                           double timeOfFlightDays,
                           OrbitDirection orbitDirection,
                           int numberRevolutions,
                           Vector3* initialVelocity,
                           Vector3* finalVelocity)
{
}

} // namespace