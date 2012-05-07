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

    double _incl;
    double _raan;
    double _omega;
};

TEST_F(TransformationTest, InputVectorIsZero)
{
    _perifocalVector = Vector3(0.0f, 0.0f, 0.0f);
    _incl = 30.0 * MATH_DEG_TO_RAD;
    _raan = 40.0 * MATH_DEG_TO_RAD;
    _omega = 60.0 * MATH_DEG_TO_RAD;
    Perifocal2Inertial(_perifocalVector, _incl, _raan, _omega, &_inertialVector);
    EXPECT_EQ(0.0, _inertialVector.x);
    EXPECT_EQ(0.0, _inertialVector.y);
    EXPECT_EQ(0.0, _inertialVector.z);
}

TEST_F(TransformationTest, InputAnglesAreZero)
{
    _perifocalVector = Vector3(6285.0, 3628.6, 0.0);
    _incl = 0.0;
    _raan = 0.0;
    _omega = 0.0;
    Perifocal2Inertial(_perifocalVector, _incl, _raan, _omega, &_inertialVector);
    EXPECT_EQ(_perifocalVector.x, _inertialVector.x);
    EXPECT_EQ(_perifocalVector.y, _inertialVector.y);
    EXPECT_EQ(_perifocalVector.z, _inertialVector.z);
}

/// Test problem: Orbital Mechanics for Engineering Students 1st Edition, Howard Curtis, Example 4.5.
TEST_F(TransformationTest, SolvesCurtisTestProblem)
{
    _perifocalVector = Vector3(6285.0, 3628.6, 0.0);
    _incl = 30.0 * MATH_DEG_TO_RAD;
    _raan = 40.0 * MATH_DEG_TO_RAD;
    _omega = 60.0 * MATH_DEG_TO_RAD;;
    Perifocal2Inertial(_perifocalVector, _incl, _raan, _omega, &_inertialVector);
    EXPECT_NEAR(-4040.0, _inertialVector.x, 1.0);
    EXPECT_NEAR(4815.0, _inertialVector.y, 1.0);
    EXPECT_NEAR(3629.0, _inertialVector.z, 1.0);
}