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
#include "Conversions.h"
#include "Base.h"

/// Test Case: Fundamentals of Astrodynamics and Applications 3rd Edition, David Vallado, Example 2-5.
TEST(ConversionsTest, EarthUnitsTest)
{
    Vector3 radiusReal(6524.834, 6862.875, 6448.296);
    Vector3 velocityReal(4.901327, 5.533756, -1.976341);

    double DU, TU, VU;
    CalculateCanonicalUnits(ASTRO_ER_TO_KM, ASTRO_MU_EARTH, &DU, &TU, &VU);

    Vector3 radiusCanonical(radiusReal.x * DU, radiusReal.y * DU, radiusReal.z * DU);
    Vector3 velocityCanonical(velocityReal.x * VU, velocityReal.y * VU, velocityReal.z * VU);

    EXPECT_NEAR(1.023, radiusCanonical.x, TEST_DU_TOLERANCE);
    EXPECT_NEAR(1.076, radiusCanonical.y, TEST_DU_TOLERANCE);
    EXPECT_NEAR(1.011, radiusCanonical.z, TEST_DU_TOLERANCE);
    EXPECT_NEAR(0.62, velocityCanonical.x, TEST_VU_TOLERANCE);
    EXPECT_NEAR(0.7, velocityCanonical.y, TEST_VU_TOLERANCE);
    EXPECT_NEAR(-0.25, velocityCanonical.z, TEST_VU_TOLERANCE);
}