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
#include "Ephemeris.h"
#include "Base.h"

// Analytical Ephemeris Fixture
class AnalyticalEphemerisTest : public ::testing::Test 
{
protected:

    AnalyticalEphemerisTest() {}
    virtual ~AnalyticalEphemerisTest() {}

    virtual void SetUp()
    {
        EphemerisManager::SetEphemerisType(EPHEMERIS_ANALYTICAL);
        epoch = 2455195;
    }

    int objectId;
    double epoch;
    OrbitalElements orbitalElements;
    StateVector stateVector;
};

TEST_F(AnalyticalEphemerisTest, EarthOrbitTest)
{
    objectId = PLANET_EARTH;
    EphemerisManager::GetOrbitAtEpoch(objectId, epoch, &orbitalElements, &stateVector);

    EXPECT_NEAR(1.0, orbitalElements.semimajorAxis, TEST_DU_TOLERANCE);
    EXPECT_NEAR(0.016705, orbitalElements.eccentricity, TEST_ECC_TOLERANCE);
    EXPECT_NEAR(1.799650, orbitalElements.argPerigee, TEST_ANGLE_TOLERANCE);
    EXPECT_NEAR(0.0, orbitalElements.inclination, TEST_ANGLE_TOLERANCE);
    EXPECT_NEAR(0.0, orbitalElements.raan, TEST_ANGLE_TOLERANCE);
    EXPECT_NEAR(6.193841, orbitalElements.trueAnomaly, TEST_ANGLE_TOLERANCE);

    EXPECT_NEAR(-0.136743, stateVector.position.x, TEST_DU_TOLERANCE);
    EXPECT_NEAR(0.973806, stateVector.position.y, TEST_DU_TOLERANCE);
    EXPECT_NEAR(0.0, stateVector.position.z, TEST_DU_TOLERANCE);
    EXPECT_NEAR(-1.006694, stateVector.velocity.x, TEST_VU_TOLERANCE);
    EXPECT_NEAR(-0.142867, stateVector.velocity.y, TEST_VU_TOLERANCE);
    EXPECT_NEAR(0.0, stateVector.velocity.z, TEST_VU_TOLERANCE);
}