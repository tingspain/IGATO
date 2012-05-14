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
#include "Lambert.h"
#include "Base.h"

TEST(LambertTest, ExponentialSinusoidValladoTestCase)
{
    Vector3 initialPosition(2.5, 0.0, 0.0); // units are ER
    Vector3 finalPosition(1.915111, 1.606969, 0.0); // units are ER
    double timeOfFlightDays = 5.6519; // units are TU
    int numberRevolutions = 0;

    Vector3 initialVelocity, finalVelocity;

    Lambert::ExponentialSinusoids(initialPosition, finalPosition, timeOfFlightDays, Prograde, numberRevolutions, &initialVelocity, &finalVelocity);

    EXPECT_NEAR(0.2604450, initialVelocity.x, TEST_VU_TOLERANCE);
    EXPECT_NEAR(0.3688589, initialVelocity.y, TEST_VU_TOLERANCE);
    EXPECT_NEAR(0.0, initialVelocity.z, TEST_VU_TOLERANCE);
    EXPECT_NEAR(-0.4366104, finalVelocity.x, TEST_VU_TOLERANCE);
    EXPECT_NEAR(0.1151515, finalVelocity.y, TEST_VU_TOLERANCE);
    EXPECT_NEAR(0.0, finalVelocity.z, TEST_VU_TOLERANCE);
}