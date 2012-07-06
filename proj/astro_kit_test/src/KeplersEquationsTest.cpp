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

#include "gtest/gtest.h"
#include "KeplersEquations.h"
#include "Base.h"

/// Test Case: Fundamentals of Astrodynamics and Applications 3rd Edition, David Vallado, Example 2-1.
TEST(KeplersEquationE, SolvesValladoTestCase)
{
    double eccentricity = 0.4;
    double M = 235.4 * MATH_DEG_TO_RAD;
    double E = SolveKeplersEquationE(eccentricity, M);
    EXPECT_NEAR(3.8486971, E, 1e-4);
}

TEST(KeplersEquationEDeathTest, EccentricityIsNotValid)
{
    double eccentricity = 1.1;
    double M = 0.0;
    EXPECT_DEBUG_DEATH(SolveKeplersEquationE(eccentricity, M), "Assertion failed: eccentricity >= 0.0 && eccentricity < 1.0");
}

/// Test Case: Fundamentals of Astrodynamics and Applications 3rd Edition, David Vallado, Example 2-3.
TEST(KeplersEquationH, SolvesValladoTestCase)
{
    double eccentricity = 2.4;
    double M = 235.4 * MATH_DEG_TO_RAD;
    double H = SolveKeplersEquationH(eccentricity, M);
    EXPECT_NEAR(1.6013761449, H, 1e-4);
}

TEST(KeplersEquationHDeathTest, EccentricityIsNotValid)
{
    double eccentricity = 0.9;
    double M = 0.0;
    EXPECT_DEBUG_DEATH(SolveKeplersEquationH(eccentricity, M), "Assertion failed: eccentricity >= 1.0");
}