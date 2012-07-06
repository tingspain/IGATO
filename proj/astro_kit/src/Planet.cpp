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

#include "Planet.h"
#include "Ephemeris.h"
#include "Base.h"

// Static fields
const Planet::PlanetMap Planet::_planetMap = Planet::CreatePlanetMap();

Planet::Planet()
    : OrbitalBody()
{
    _planetId = PLANET_INVALID_TYPE;
}

Planet::Planet(int planetId)
    : OrbitalBody()
{
    _planetId = planetId;
}

Planet::Planet(std::string planetName)
    : OrbitalBody()
{
    GetPlanetIdFromName(planetName, &_planetId);
}

void Planet::GetOrbitAtEpoch(const Epoch& epoch, int ephemerisType, OrbitalElements* orbitalElements, StateVector* stateVector) const
{
    double jd = 0.0;
    EphemerisManager::GetOrbitAtEpoch(_planetId, jd, orbitalElements, stateVector);
}

void Planet::GetPlanetNameFromId(int planetId, std::string* planetName)
{
    assert(planetId >= 0 && planetId < PLANET_COUNT);
    *planetName = _planetMap.at(planetId);
}

void Planet::GetPlanetIdFromName(const std::string& planetName, int* planetId)
{
    PlanetMap::const_iterator pit;
    for (pit = _planetMap.begin(); pit != _planetMap.end(); ++pit)
    {
        if (pit->second.compare(planetName) == 0)
        {
            *planetId = pit->first;
            return;
        }
    }
    *planetId = -1;
}

Planet::PlanetMap Planet::CreatePlanetMap()
{
    PlanetMap planetMap;

    planetMap[PLANET_MERCURY]   = "Mercury";
    planetMap[PLANET_VENUS]     = "Venus";
    planetMap[PLANET_EARTH]     = "Earth";
    planetMap[PLANET_MARS]      = "Mars";
    planetMap[PLANET_JUPITER]   = "Jupiter";
    planetMap[PLANET_SATURN]    = "Saturn";
    planetMap[PLANET_URANUS]    = "Uranus";
    planetMap[PLANET_NEPTUNE]   = "Neptune";
    planetMap[PLANET_PLUTO]     = "Pluto";

    return planetMap;
}