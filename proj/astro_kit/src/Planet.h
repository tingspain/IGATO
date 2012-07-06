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
#include "OrbitalBody.h"
#include <map>
#include <string>

// Forward declarations
struct OrbitalElements;

class Planet : public OrbitalBody
{
public:
    Planet();
    Planet(int planetId);
    Planet(std::string planetName);

    virtual void GetOrbitAtEpoch(const Epoch& epoch, int ephemerisType, OrbitalElements* orbitalElements, StateVector* stateVector) const;
    
    static void GetPlanetNameFromId(int planetId, std::string* planetName);
    static void GetPlanetIdFromName(const std::string& planetName, int* planetId);

private:
    typedef std::map<int, std::string> PlanetMap;

    static PlanetMap CreatePlanetMap();

protected:
    int _planetId;

private:    
    static const PlanetMap _planetMap;  
};