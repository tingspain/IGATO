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

void ConvertStateVector2OrbitalElements(const StateVector& stateVector, OrbitalElements* orbitalElements)
{
    // Position and velocity vectors, magnitudes, and dot product.
    const Vector3& Pos = stateVector.position;
    const Vector3& Vel = stateVector.velocity;
    double pos = Pos.length();
    double vel = Vel.length();
    double posDotVel = Pos.dot(Vel);

    // Specific angular momentum
    static Vector3 SpecificAngularMomentum;
    Vector3::cross(Pos, Vel, &SpecificAngularMomentum);
    double specificAngularMomentum = SpecificAngularMomentum.length();

    // Node vector
    static Vector3 NodeVector;
    Vector3::cross(MATH_UNIT_VEC_K, SpecificAngularMomentum, &NodeVector); 
    double nodeVector = NodeVector.length();

    // Eccentricity
    static Vector3 Eccentricity;
    Eccentricity = (SQR(vel) - 1.0/pos)*Pos - posDotVel*Vel;
    double eccentricity = Eccentricity.length();

    // Semimajor axis (a) and semiparameter (p)
    double semimajorAxis, semiParameter;
    if (eccentricity != ASTRO_ECC_PARABOLIC) // non parabolic orbit
    {
        double specificMechEnergy = 0.5*SQR(vel) - 1.0/pos; // specific mechanical energy
        semimajorAxis = -0.5 / specificMechEnergy;
        semiParameter = semimajorAxis*(1 - SQR(eccentricity));
    }
    else // parabolic orbit
    {
        semimajorAxis = MATH_INFINITY;
        semiParameter = SQR(specificAngularMomentum);
    }

    // Inclination
    double inclination = 0.0;
    if (specificAngularMomentum > 0.0)
    {
        inclination = acos(SpecificAngularMomentum.z / specificAngularMomentum);
    }

    // Right ascension of the ascending node
    double raan = 0.0;
    if (nodeVector > 0.0)
    {
        raan = acos(NodeVector.x / nodeVector);
        if (NodeVector.y < 0)
        {
            raan = MATH_2_PI - raan;
        }
    }

    // Arguement of perigee
    double argPerigee = 0.0;
    if (eccentricity != ASTRO_ECC_CIRCULAR && inclination != ASTRO_INCL_EQUATORIAL) // non-circular and non-equatorial orbit
    {
        double nodeVecDotEcc = NodeVector.dot(Eccentricity);
        argPerigee = acos(nodeVecDotEcc / nodeVector / eccentricity);
        if (Eccentricity.z < 0.0)
        {
            argPerigee = MATH_2_PI - argPerigee;
        }
    }
    else if (eccentricity != ASTRO_ECC_CIRCULAR) // non-circular equatorial orbit (line of nodes is undefined)
    {
        argPerigee = acos(Eccentricity.x / eccentricity);
    }
    
    // True anomaly
    double trueAnomaly;
    if (eccentricity != ASTRO_ECC_CIRCULAR) // non-circular orbit
    {
        double eccDotPos = Eccentricity.dot(Pos);
        trueAnomaly = acos(eccDotPos / eccentricity / pos);
        if (posDotVel < 0.0)
        {
            trueAnomaly = MATH_2_PI - trueAnomaly;
        }
    }
    else if (inclination != ASTRO_INCL_EQUATORIAL) // circular orbit with non-equatorial orbit
    {
        double nodeVecDotPos = NodeVector.dot(Pos);
        double nodeVecDotVel = NodeVector.dot(Vel);
        trueAnomaly = acos(nodeVecDotPos / nodeVector / pos);
        if (nodeVecDotVel > 0.0)
        {
            trueAnomaly = MATH_2_PI - trueAnomaly; // argument of latitude
        }
    }
    else // circular equatorial orbit (line of nodes is undefined)
    {
        trueAnomaly = acos(Pos.x / pos); // true longitude
        if (Vel.x > 0.0)
        {
            trueAnomaly = MATH_2_PI - trueAnomaly;
        }
    }
    
    // Pack up the calculated orbital elements
    orbitalElements->semimajorAxis = semimajorAxis;
    orbitalElements->eccentricity = eccentricity;
    orbitalElements->argPerigee = argPerigee;
    orbitalElements->inclination = inclination;
    orbitalElements->raan = raan;
    orbitalElements->trueAnomaly = trueAnomaly;
}

void ConvertOrbitalElements2StateVector(const OrbitalElements& orbitalElements, StateVector* stateVector)
{
    // Unpack the orbital elements.
    double semimajorAxis = orbitalElements.semimajorAxis;
    double eccentricity = orbitalElements.eccentricity;
    double argPerigee = orbitalElements.argPerigee;
    double inclination = orbitalElements.inclination;
    double raan = orbitalElements.raan;
    double trueAnomaly = orbitalElements.trueAnomaly;

    // Calculate the semiparameter
    double semiParameter = semimajorAxis*(1.0 - SQR(eccentricity));

    // Precalculate common trig functions.
    double cosTrueAnomaly = cos(trueAnomaly);
    double sinTrueAnomaly = sin(trueAnomaly);

    // Build state vectors in perifocal reference frame
    static Vector3 Pos, Vel;
    Pos.x = semiParameter*cosTrueAnomaly / (1.0 + eccentricity*cosTrueAnomaly);
    Pos.y = semiParameter*sinTrueAnomaly / (1.0 + eccentricity*cosTrueAnomaly);
    Pos.z = 0.0;
    Vel.x = -sqrt(1.0/semiParameter)*sinTrueAnomaly;
    Vel.y = sqrt(1.0/semiParameter)*(eccentricity + cosTrueAnomaly);
    Vel.z = 0.0;

    // Transform state vectors from perifocal reference frame to inertial.
    TransformPerifocal2Inertial(Pos, inclination, raan, argPerigee, &stateVector->position);
    TransformPerifocal2Inertial(Vel, inclination, raan, argPerigee, &stateVector->velocity);
}