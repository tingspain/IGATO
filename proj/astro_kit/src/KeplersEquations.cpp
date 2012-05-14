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

#include "KeplersEquations.h"
#include "Base.h"

double SolveKeplersEquationE(double ecc, double M)
{
    assert(ecc >= 0.0 && ecc < 1.0);

    double E; // eccentric anomaly (radians)
    if (M < MATH_PI)
    {
        E = M + 0.5*ecc;
    }
    else
    {
        E = M - 0.5*ecc;
    }
 
    int counter = 0;
    const int MAX_COUNTER = 10000; // The max number of iteration attempts allowed.

    double ratio = 1.0;
    while (fabs(ratio) > MATH_TOLERANCE && counter < MAX_COUNTER)
    {
        ratio = (M - E + ecc*sin(E)) / (1 - ecc*cos(E));
        E += ratio;
        counter++;
    }

    if (counter >= MAX_COUNTER)
    {
        // log error
        throw "Iteration limit exceeded.";
    }

    return E;
}

double SolveKeplersEquationH(double ecc, double M)
{
    assert (ecc >= 1.0);

    double H;

    if (ecc < 1.6)
    {
        if (M > MATH_PI || (M > -MATH_PI && M < 0.0))
        {
            H = M - ecc;
        }
        else
        {
            H = M + ecc;
        }
    }
    else
    {
        if (ecc < 3.6 && fabs(M) > MATH_PI)
        {
            H = M - Sign(M)*ecc;
        }
        else
        {
            H = M / (ecc - 1.0);
        }
    }

    int counter = 0;
    const int MAX_COUNTER = 10000; // The max number of iteration attempts allowed.

    double ratio = 1.0;
    while (fabs(ratio) > MATH_TOLERANCE && counter < MAX_COUNTER)
    {
        ratio = (M - ecc*sinh(H) + H) / (ecc*cosh(H) - 1.0);
        H += ratio;
        counter++;
    }

    if (counter >= MAX_COUNTER)
    {
        // log error
        throw "Iteration limit exceeded.";
    }

    return H;
}