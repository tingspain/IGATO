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

/// Transform a 3D vector from perifocal reference frame to inertial.
/**
 Reference: Orbital Mechanics for Engineering Students 1st Edition, Howard Curtis, Eqn 4.44.

 @param perifocalVector : 3D vector in perifocal coordinates.
 @param incl : The inclination (radians)
 @param raan : The right ascension of the ascending node (radians)
 @param omega : The true anomaly (radians)
 @param [out] inertialVector : The computed 3D vector in inertial coordinates
*/
void TransformPerifocal2Inertial(const Vector3& perifocalVector, double incl, double raan, double omega, Vector3* inertialVector);