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
#include "Orbit.h"
#include "Conversions.h"
#include "Base.h"

// Orbit Fixture
class OrbitTest : public ::testing::Test 
{
protected:

    OrbitTest()
    {
        orbit = NULL;
    }

    virtual ~OrbitTest()
    {
    }

    virtual void SetUp()
    {
        double mu = ASTRO_MU_SUN;
        orbit = new Orbit(mu);
    }

    virtual void TearDown()
    {
        delete orbit;
        orbit = NULL;
    }

    Orbit* orbit;
};

TEST_F(OrbitTest, IsCorrectMU)
{
    double mu = ASTRO_MU_SUN;
    EXPECT_EQ(mu, orbit->GetMu());
}

/// Test Case: Fundamentals of Astrodynamics and Applications 3rd Edition, David Vallado, Example 2-5.
TEST(StateVector2OrbitalElementsTest,  SolvesValladoTestCase)
{
    StateVector stateVector;
    stateVector.position = Vector3(1.023, 1.076, 1.011); // units are ER
    stateVector.velocity = Vector3(0.62, 0.7, -0.25); // units are VU
    OrbitalElements orbitalElements;
    ConvertStateVector2OrbitalElements(stateVector, &orbitalElements);
    EXPECT_NEAR(5.664247, orbitalElements.semimajorAxis, TEST_DU_TOLERANCE);
    EXPECT_NEAR(0.832853, orbitalElements.eccentricity, TEST_ECC_TOLERANCE);
    EXPECT_NEAR(87.870*MATH_DEG_TO_RAD, orbitalElements.inclination, TEST_ANGLE_TOLERANCE);
    EXPECT_NEAR(53.380*MATH_DEG_TO_RAD, orbitalElements.argPerigee, TEST_ANGLE_TOLERANCE);
    EXPECT_NEAR(227.89*MATH_DEG_TO_RAD, orbitalElements.raan, TEST_ANGLE_TOLERANCE);
    EXPECT_NEAR(92.335*MATH_DEG_TO_RAD, orbitalElements.trueAnomaly, TEST_ANGLE_TOLERANCE);
}

/// Test Case: Orbital Mechanics for Engineering Students 1st Edition, Howard Curtis, Example 4.3.
TEST(StateVector2OrbitalElementsTest, SolvesCurtisTestCase)
{
    StateVector stateVector;
    stateVector.position = Vector3(-0.947769, -0.547182, 0.391964); // units are ER
    stateVector.velocity = Vector3(-0.437298, 0.837153, 0.320415); // units are VU
    OrbitalElements orbitalElements;
    ConvertStateVector2OrbitalElements(stateVector, &orbitalElements);
    EXPECT_NEAR(1.377832, orbitalElements.semimajorAxis, TEST_DU_TOLERANCE);
    EXPECT_NEAR(0.1712, orbitalElements.eccentricity, TEST_ECC_TOLERANCE);
    EXPECT_NEAR(153.2*MATH_DEG_TO_RAD, orbitalElements.inclination, TEST_ANGLE_TOLERANCE);
    EXPECT_NEAR(20.07*MATH_DEG_TO_RAD, orbitalElements.argPerigee, TEST_ANGLE_TOLERANCE);
    EXPECT_NEAR(255.3*MATH_DEG_TO_RAD, orbitalElements.raan, TEST_ANGLE_TOLERANCE);
    EXPECT_NEAR(28.45*MATH_DEG_TO_RAD, orbitalElements.trueAnomaly, TEST_ANGLE_TOLERANCE);
}

/// Test Case: Fundamentals of Astrodynamics and Applications 3rd Edition, David Vallado, Example 2-6.
TEST(OrbitalElements2StateVectorTest, SolvesValladoTestCase)
{
    OrbitalElements orbitalElements;
    orbitalElements.semimajorAxis = 5.664137; // units are ER
    orbitalElements.eccentricity = 0.83285;
    orbitalElements.inclination = 87.87 * MATH_DEG_TO_RAD;
    orbitalElements.raan = 227.89 * MATH_DEG_TO_RAD;
    orbitalElements.argPerigee = 53.38 * MATH_DEG_TO_RAD;
    orbitalElements.trueAnomaly = 92.335 * MATH_DEG_TO_RAD;
    StateVector stateVector;  
    ConvertOrbitalElements2StateVector(orbitalElements, &stateVector);
    EXPECT_NEAR(1.02308, stateVector.position.x, TEST_DU_TOLERANCE);
    EXPECT_NEAR(1.07579, stateVector.position.y, TEST_DU_TOLERANCE);
    EXPECT_NEAR(1.01113, stateVector.position.z, TEST_DU_TOLERANCE);
    EXPECT_NEAR(0.62012, stateVector.velocity.x, TEST_VU_TOLERANCE);
    EXPECT_NEAR(0.69992, stateVector.velocity.y, TEST_VU_TOLERANCE);
    EXPECT_NEAR(-0.24992, stateVector.velocity.z, TEST_VU_TOLERANCE);
}

/// Test Case: Orbital Mechanics for Engineering Students 1st Edition, Howard Curtis, Example 4.5.
TEST(OrbitalElements2StateVectorTest, SolvesCurtisTestCase)
{
    OrbitalElements orbitalElements;
    orbitalElements.semimajorAxis = -2.62226828; // units are ER
    orbitalElements.eccentricity = 1.4;
    orbitalElements.inclination = 30.0 * MATH_DEG_TO_RAD;
    orbitalElements.raan = 40.0 * MATH_DEG_TO_RAD;
    orbitalElements.argPerigee = 60.0 * MATH_DEG_TO_RAD;
    orbitalElements.trueAnomaly = 30.0 * MATH_DEG_TO_RAD;
    StateVector stateVector;
    ConvertOrbitalElements2StateVector(orbitalElements, &stateVector);
    EXPECT_NEAR(-0.633414, stateVector.position.x,TEST_DU_TOLERANCE);
    EXPECT_NEAR(0.754923, stateVector.position.y, TEST_DU_TOLERANCE);
    EXPECT_NEAR(0.568975, stateVector.position.z, TEST_DU_TOLERANCE);
    EXPECT_NEAR(-1.314297, stateVector.velocity.x, TEST_VU_TOLERANCE);
    EXPECT_NEAR(-0.603641, stateVector.velocity.y, TEST_VU_TOLERANCE);
    EXPECT_NEAR(0.220610, stateVector.velocity.z, TEST_VU_TOLERANCE);
}