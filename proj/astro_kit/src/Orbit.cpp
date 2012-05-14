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

Orbit::Orbit(const OrbitalElements& coes, double mu)
{
    _mu = mu;
    SetOrbitalElements(coes);
}

void Orbit::SetStateVector(const StateVector& stateVector)
{
    SetStateVector(stateVector.position, stateVector.velocity);
}

void Orbit::SetStateVector(const Vector3& position, const Vector3& velocity)
{
    _stateVector.position = position;
    _stateVector.velocity = velocity;

    _coesState = DIRTY;
}

void Orbit::SetOrbitalElements(const OrbitalElements& coes)
{
    _coes = coes;

    _stateVectorState = DIRTY;
}

const StateVector& Orbit::GetStateVector() const
{
    if (_stateVectorState == DIRTY)
    {
        UpdateStateVector();
    }

    return _stateVector;
}

const OrbitalElements& Orbit::GetOrbitalElements() const
{
    if (_coesState == DIRTY)
    {
        UpdateOrbitalElements();
    }

    return _coes;
}

void Orbit::UpdateStateVector() const
{
    ConvertOrbitalElements2StateVector(_coes, &_stateVector);   
    _stateVectorState = CLEAN;
}

void Orbit::UpdateOrbitalElements() const
{
    ConvertStateVector2OrbitalElements(_stateVector, &_coes);
    _coesState = CLEAN;
}

void Orbit::Propagate(double timeOfFlight)
{

}