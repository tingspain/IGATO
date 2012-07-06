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
#include "Base.h"

// Forward declarations
class Ephemeris;
struct jpl_eph_data;

/// Ephemeris Manager Class.
/** This class is responsible for retrieving ephemeris data for a specified orbital object at a desired epoch.
    The ephemeris may either be interpolated via analytical methods or queried from an established database
    such as the JPL ephemeris.
 */
class EphemerisManager
{
public:

    /// Set the type of ephemeris to use.
    static void SetEphemerisType(EphemerisType ephemerisType);

    /// Get orbital elements and state vectors.
    /**
     This routine retrieves the orbit (orbital elements and state vectors) for a specified orbital object
     at a desired epoch. This routine uses the type of ephemeris that was set using the SetEphemerisType()
     method or throws an exception if one has not been set.

     @param objectId : The orbital object identifier
     @param epoch : The time at which to recieve data at
     @param [out] orbitalElements : The computed orbital elements.
     @param [out] stateVector : The computed state vectors.
     */
    static void GetOrbitAtEpoch(int objectId, double epoch, OrbitalElements* orbitalElements, StateVector* stateVector);

    /// Static destructor.
    /**
     This routine releases any allocated memory for the current ephemeris class.
     */
    static void Cleanup();

private:
    /// Static class only, prevent instatiation
    EphemerisManager();

private:
    /// A pointer to the current ephemeris class.
    static Ephemeris* _ephemeris;
};

/// Abstract base class for all ephemeris classes.
class Ephemeris
{
public:
    virtual void GetOrbitAtEpoch(int objectId, double epoch, OrbitalElements* orbitalElements, StateVector* stateVector) = 0;

protected:
    OrbitalElements _dummyCoes;
    StateVector _dummyStateVector;
};

class AnalyticalEphemeris : public Ephemeris
{
public:
    virtual void GetOrbitAtEpoch(int objectId, double epoch, OrbitalElements* orbitalElements, StateVector* stateVector);

protected:
    /// Calculate the analytical ephemeris
    /**
     This routine analytically interpolates ephemeris data for a specified orbital object at a desired epoch.

     @param objectId : The orbital object identifier
     @param epoch : The time at which to recieve data at
     @param [out] orbitalElements : The computed orbital elements.
     */
    virtual void Calculate(int objectId, double epoch, OrbitalElements* orbitalElements);
};

class JplEphemeris : public Ephemeris
{
public:
    /// Set the JPL ephemeris data file
    /**
     This routine sets the current JPL ephemeris data file which will be used for all future ephemeries queries.

     @param filename : The absolute path to the file
     */
    virtual void SetEphemerisFile(const std::string& filepath);

    virtual void GetOrbitAtEpoch(int objectId, double epoch, OrbitalElements* orbitalElements, StateVector* stateVector);

protected:
    /// Query the JPL ephemeris database.
    /**
     This routine queries a JPL ephemeris database file (e.g DE405, DE423, etc..) for data for a specified
     orbital object at a desired epoch.

     @param objectId : The orbital object identifier
     @param epoch : The time at which to recieve data at
     @param [out] stateVector : The computed state vectors.
     */
    virtual void QueryDatabase(int objectId, double epoch, StateVector* stateVector);

protected:
    std::string _ephemerisFile;
    jpl_eph_data* _ephemerisData;
    State _ephemerisState;
};

