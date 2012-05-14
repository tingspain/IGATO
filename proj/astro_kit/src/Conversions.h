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

// Forward declarations
struct StateVector;
struct OrbitalElements;

/// Calculate canonical unit conversions
/**
 This routine calculates the conversion factors for converting real units to canonical units.
 Working in canonical units typically improves computational efficiency and has the benefit
 that the gravitational parameter is unity which saves numerous mathematical operations.

 In Earth-centered reference frames, the equitorial radius of the Earth is typically used as
 the reference radius whereas in a Sun-centered reference frame, one astronomical unit (AU)
 is typically used as the reference radius.

 Canonical units are obtained by multiplying real units by the appropriate conversion factor.
 e.g. R_DU = R_km * DU

 @param radius : The reference radius to be used as the distance unit (DU)
 @param mu : The gravitional parameter of the central body
 @param [out] DU : The conversion factor from real distance units to canonical distance units.
 @param [out] TU : The conversion factor from real time units to canonical time units.
 @param [out] VU : The conversion factor from real velocity units to canonical velocity units.
 */
void CalculateCanonicalUnits(double radius, double mu, double* DU, double* TU, double* VU);

/// Convert state vectors to orbital elements.
/**
 This routine calculates the classical orbital elements (coes) of an object given its position
 and velocity (state) vectors.

 Reference: Fundamentals of Astrodynamics and Applications 3rd Edition, David Vallado, Algorithm 9.

 @param stateVector : The position and velocity vectors.
 @param [out] coes : The computed orbital elements.
*/
void ConvertStateVector2OrbitalElements(const StateVector& stateVector, OrbitalElements* coes);

/// Convert orbital elements to state vectors.
/**
 This routine calculates the position and velocity (state) vectors of an object given its
 classical orbital elements (coes).

 Reference: Fundamentals of Astrodynamics and Applications 3rd Edition, David Vallado, Algorithm 10.

 @param coes : The orbital elements.
 @param [out] stateVector : The computed position and velocity vectors.
*/
void ConvertOrbitalElements2StateVector(const OrbitalElements& coes, StateVector* stateVector);