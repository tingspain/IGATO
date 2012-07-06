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
#include "Transformation.h"
#include "Vector3.h"
#include "Base.h"

// Transformation Fixture
class TransformationTest : public ::testing::Test
{
protected:
    TransformationTest() {}
    virtual ~TransformationTest() {}

    virtual void SetUp() {}
    virtual void TearDown() {}

    Vector3 _perifocalVector;
    Vector3 _inertialVector;

    double _inclination;
    double _raan;
    double _argPerigee;
};

TEST_F(TransformationTest, InputVectorIsZero)
{
    _perifocalVector = Vector3(0.0f, 0.0f, 0.0f);
    _inclination = 30.0 * MATH_DEG_TO_RAD;
    _raan = 40.0 * MATH_DEG_TO_RAD;
    _argPerigee = 60.0 * MATH_DEG_TO_RAD;
    TransformPerifocal2Inertial(_perifocalVector, _inclination, _raan, _argPerigee, &_inertialVector);
    EXPECT_EQ(0.0, _inertialVector.x);
    EXPECT_EQ(0.0, _inertialVector.y);
    EXPECT_EQ(0.0, _inertialVector.z);
}

TEST_F(TransformationTest, InputAnglesAreZero)
{
    _perifocalVector = Vector3(6285.0, 3628.6, 0.0);
    _inclination = 0.0;
    _raan = 0.0;
    _argPerigee = 0.0;
    TransformPerifocal2Inertial(_perifocalVector, _inclination, _raan, _argPerigee, &_inertialVector);
    EXPECT_EQ(_perifocalVector.x, _inertialVector.x);
    EXPECT_EQ(_perifocalVector.y, _inertialVector.y);
    EXPECT_EQ(_perifocalVector.z, _inertialVector.z);
}

/// Test Case: Fundamentals of Astrodynamics and Applications 3rd Edition, David Vallado, Example 2-6.
TEST_F(TransformationTest, SolvesValladoTestCase)
{
    _perifocalVector = Vector3(-0.0731819, 1.7947281, 0.0); // units are ER
    _inclination = 87.87 * MATH_DEG_TO_RAD;
    _raan = 227.89 * MATH_DEG_TO_RAD;
    _argPerigee = 53.38 * MATH_DEG_TO_RAD;
    TransformPerifocal2Inertial(_perifocalVector, _inclination, _raan, _argPerigee, &_inertialVector);
    EXPECT_NEAR(1.02308, _inertialVector.x, 1e-4);
    EXPECT_NEAR(1.07579, _inertialVector.y, 1e-4);
    EXPECT_NEAR(1.01113, _inertialVector.z, 1e-4);
}

/// Test Case: Orbital Mechanics for Engineering Students 1st Edition, Howard Curtis, Example 4.5.
TEST_F(TransformationTest, SolvesCurtisTestCase)
{
    _perifocalVector = Vector3(6285.0, 3628.6, 0.0);
    _inclination = 30.0 * MATH_DEG_TO_RAD;
    _raan = 40.0 * MATH_DEG_TO_RAD;
    _argPerigee = 60.0 * MATH_DEG_TO_RAD;
    TransformPerifocal2Inertial(_perifocalVector, _inclination, _raan, _argPerigee, &_inertialVector);
    EXPECT_NEAR(-4040.0, _inertialVector.x, 1.0);
    EXPECT_NEAR(4815.0, _inertialVector.y, 1.0);
    EXPECT_NEAR(3629.0, _inertialVector.z, 1.0);
}