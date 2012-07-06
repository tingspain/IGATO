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

#include "Orbit.h"
#include "KeplersEquations.h"
#include "Conversions.h"

Orbit::Orbit(double mu)
{
    _init = false;
    _type = ORBIT_INVALID_TYPE;
    _orbitalElementsState = STATE_DIRTY;
    _stateVectorState = STATE_DIRTY;
    _mu = mu;
}

Orbit::Orbit(const StateVector& stateVector, double mu)
{
    _mu = mu;
    SetStateVector(stateVector);
}

Orbit::Orbit(const Vector3& position, const Vector3& velocity, double mu)
{
    _mu = mu;
    SetStateVector(position, velocity);
}

Orbit::Orbit(const OrbitalElements& orbitalElements, double mu)
{
    _mu = mu;
    SetOrbitalElements(orbitalElements);
}

void Orbit::SetStateVector(const StateVector& stateVector)
{
    SetStateVector(stateVector.position, stateVector.velocity);
}

void Orbit::SetStateVector(const Vector3& position, const Vector3& velocity)
{
    if (position == _stateVector.position && velocity == _stateVector.velocity)
        return;

    _stateVector.position = position;
    _stateVector.velocity = velocity;

    _orbitalElementsState = STATE_DIRTY;

    _init = true; 
}

void Orbit::SetOrbitalElements(const OrbitalElements& orbitalElements)
{
    if (orbitalElements == _orbitalElements)
        return;

    _orbitalElements = orbitalElements;

    _stateVectorState = STATE_DIRTY;
    _init = true;
}

const StateVector& Orbit::GetStateVector() const
{
    assert(_init);

    if (_stateVectorState == STATE_DIRTY)
    {
        UpdateStateVector();
    }

    return _stateVector;
}

const OrbitalElements& Orbit::GetOrbitalElements() const
{
    assert(_init);

    if (_orbitalElementsState == STATE_DIRTY)
    {
        UpdateOrbitalElements();
    }

    return _orbitalElements;
}

OrbitType Orbit::GetType() const
{
    assert(_init);

    if (_orbitalElementsState == STATE_DIRTY)
    {
        UpdateOrbitalElements();
    }

    double eccentricity = _orbitalElements.eccentricity;
    if (eccentricity == ASTRO_ECC_CIRCULAR)
    {
        return ORBIT_CIRCULAR;
    }
    else if (eccentricity > ASTRO_ECC_CIRCULAR &&
             eccentricity < ASTRO_ECC_PARABOLIC)
    {
        return ORBIT_ELLIPTICAL;
    }
    else if (eccentricity == ASTRO_ECC_PARABOLIC)
    {
        return ORBIT_PARABOLIC;
    }
    else if (eccentricity > ASTRO_ECC_PARABOLIC)
    {
        return ORBIT_HYPERBOLIC;
    }
    else
    {
        throw "Invalid eccentricity value";
    }
}

void Orbit::UpdateStateVector() const
{
    ConvertOrbitalElements2StateVector(_orbitalElements, &_stateVector);   
    _stateVectorState = STATE_CLEAN;
}

void Orbit::UpdateOrbitalElements() const
{
    ConvertStateVector2OrbitalElements(_stateVector, &_orbitalElements);
    _orbitalElementsState = STATE_CLEAN;
}

void Orbit::Propagate(double timeOfFlight)
{
    assert(_init);


}