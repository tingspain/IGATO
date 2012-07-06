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

#include "Transformation.h"

void TransformPerifocal2Inertial(const Vector3& perifocalVector, double inclination, double raan, double argPerigee, Vector3* inertialVector)
{
    // Precalculate common trig functions.
    float cosRAAN = cos(raan);
    float sinRAAN = sin(raan);
    float cosOmega = cos(argPerigee);
    float sinOmega = sin(argPerigee);
    float cosIncl = cos(inclination);
    float sinIncl = sin(inclination);

    // Build the rotation matrix
    static Vector3 row1, row2, row3;
    row1.x =  (cosRAAN * cosOmega) - (sinRAAN * sinOmega * cosIncl);
    row1.y = -(cosRAAN * sinOmega) - (sinRAAN * cosIncl * cosOmega);
    row1.z =  (sinRAAN * sinIncl);
    row2.x =  (sinRAAN * cosOmega) + (cosRAAN * cosIncl * sinOmega);
    row2.y = -(sinRAAN * sinOmega) + (cosRAAN * cosIncl * cosOmega);
    row2.z = -(cosRAAN * sinIncl);
    row3.x =  (sinIncl * sinOmega);
    row3.y =  (sinIncl * cosOmega);
    row3.z =  (cosIncl);

    // Transform perifocal vector to inertial according to rotation matrix.
    inertialVector->x = row1.dot(perifocalVector);
    inertialVector->y = row2.dot(perifocalVector);
    inertialVector->z = row3.dot(perifocalVector);
}