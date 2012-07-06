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

/// Solves Keplers Equation for elliptical orbits.
/**
 This routine computes the eccentric anomaly of an elliptical orbit using the eccentricity and mean anomaly.
 Kepler's Equation is a transendental equation which is solved using Newton-Raphson iteration. An exception
 is thrown if more than 10,000 iterations are performed.

 Reference: Fundamentals of Astrodynamics and Applications 3rd Edition, David Vallado, Algorithm 2.

 @param eccentricity : The eccentricity.
 @param M : The mean anomaly (radians).
 @returns : The eccentric anomaly (radians).
*/
double SolveKeplersEquationE(double eccentricity, double M);

/// Solves Keplers Equation for hyperbolic orbits.
/**
 This routine computes the hyperbolic anomaly of an hyperbolic orbit using the eccentricity and mean anomaly.
 Kepler's Equation is a transendental equation which is solved using Newton-Raphson iteration. An exception
 is thrown if more than 10,000 iterations are performed.

 Reference: Fundamentals of Astrodynamics and Applications 3rd Edition, David Vallado, Algorithm 4.

 @param eccentricity : The eccentricity.
 @param M : The mean anomaly (radians).
 @returns : The hyperbolic anomaly (radians).
*/
double SolveKeplersEquationH(double eccentricity, double M);