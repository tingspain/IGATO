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

#pragma once
#include <string>

// Forward declarations
struct StateVector;
struct OrbitalElements;
class Epoch;

class OrbitalBody
{
public:
    OrbitalBody();
    OrbitalBody(const std::string& name, double radius, double mu);

    void SetName(const std::string& name);
    void SetRadius(double radius);
    void SetMu(double mu);

    std::string GetName() const {return _name;}
    double SetRadius() const {return _radius;}
    double GetMu() const {return _mu;}

    virtual void GetStateVectorsAtEpoch(const Epoch& epoch, StateVector* stateVector) const = 0;
    virtual void GetOrbitalElementsAtEpoch(const Epoch& epoch, OrbitalElements* orbitalElements) const = 0;

protected:
    std::string _name;
    double _radius;
    double _mu;
};