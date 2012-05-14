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

#include "Conversions.h"
#include "Transformation.h"
#include "Base.h"

void CalculateCanonicalUnits(double radius, double mu, double* DU, double* TU, double* VU)
{
    double du, tu, vu;
    du = radius;                    // distance unit
    tu = sqrt(du * du * du / mu);   // time unit
    vu = du / tu;                   // velocity unit

    // Calculate conversions from physical units to canonical
    *DU = 1.0 / du;
    *TU = 1.0 / tu;
    *VU = 1.0 / vu;
}

void ConvertStateVector2OrbitalElements(const StateVector& stateVector, OrbitalElements* coes)
{
    // Position and velocity vectors, magnitudes, and dot product.
    const Vector3& R = stateVector.position;
    const Vector3& V = stateVector.velocity;
    double r = R.length();
    double v = V.length();
    double rv = R.dot(V);

    // Precalculate for speed.
    //double oneOverR = 1.0 / r;

    // Specific angular momentum
    static Vector3 H;
    Vector3::cross(R, V, &H);
    double h = H.length();

    // Node vector
    static Vector3 N;
    Vector3::cross(MATH_UNIT_VEC_K, H, &N); 
    double n = N.length();

    // Eccentricity
    static Vector3 Ecc;
    Ecc = (v*v - 1.0/r)*R - rv*V;
    double ecc = Ecc.length();

    // Semimajor axis (a) and semiparameter (p)
    double a, p;
    if (ecc != 1.0) // non parabolic orbit
    {
        double xi = 0.5*v*v - 1.0/r; // specific mechanical energy
        a = -0.5/xi;
        p = a*(1 - ecc*ecc);
    }
    else // parabolic orbit
    {
        a = MATH_INFINITY;
        p = h*h;
    }

    // Inclination
    double incl = acos(H.z / h);

    // Right ascension of the ascending node
    double raan = acos(N.x / n);
    if (N.y < 0)
    {
        raan = MATH_2_PI - raan;
    }

    // Arguement of perigee
    double necc = N.dot(Ecc);
    double omega = acos(necc / n / ecc);
    if (Ecc.z < 0.0)
    {
        omega = MATH_2_PI - omega;
    }

    // True anomaly
    double eccr = Ecc.dot(R);
    double theta = acos(eccr / ecc / r);
    if (rv < 0.0)
    {
        theta = MATH_2_PI - theta;
    }

    // Pack up the calculated orbital elements
    coes->a = a;
    coes->ecc = ecc;
    coes->omega = omega;
    coes->incl = incl;
    coes->raan = raan;
    coes->theta = theta;
}

void ConvertOrbitalElements2StateVector(const OrbitalElements& coes, StateVector* stateVector)
{
    // Unpack the orbital elements.
    double a = coes.a;
    double ecc = coes.ecc;
    double omega = coes.omega;
    double incl = coes.incl;
    double raan = coes.raan;
    double theta = coes.theta;

    // Calculate the semiparameter
    double p = a*(1.0 - ecc*ecc);

    // Precalculate common trig functions.
    double cosTheta = cos(theta);
    double sinTheta = sin(theta);

    // Build state vectors in perifocal reference frame
    static Vector3 R, V;
    R.x = p*cosTheta / (1.0 + ecc*cosTheta);
    R.y = p*sinTheta / (1.0 + ecc*cosTheta);
    R.z = 0.0;
    V.x = -sqrt(1.0/p)*sinTheta;
    V.y = sqrt(1.0/p)*(ecc + cosTheta);
    V.z = 0.0;

    // Transform state vectors from perifocal reference frame to inertial.
    TransformPerifocal2Inertial(R, incl, raan, omega, &stateVector->position);
    TransformPerifocal2Inertial(V, incl, raan, omega, &stateVector->velocity);
}