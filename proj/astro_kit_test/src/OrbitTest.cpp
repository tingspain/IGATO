#include "gtest/gtest.h"
#include "Orbit.h"
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
TEST(StateVector2CoesTest,  SolvesValladoTestCase)
{
    double mu = ASTRO_MU_EARTH;
    StateVector stateVector;
    stateVector.position = Vector3(6524.834, 6862.875, 6448.296);
    stateVector.velocity = Vector3(4.901327, 5.533756, -1.976341);
    Coes coes;
    Orbit::ConvertStateVector2Coes(stateVector, &coes, mu);
    EXPECT_NEAR(36127.343, coes.a, 1e-1);
    EXPECT_NEAR(0.832853, coes.ecc, 1e-4);
    EXPECT_NEAR(87.870*MATH_DEG_TO_RAD, coes.incl, 1e-3);
    EXPECT_NEAR(53.380*MATH_DEG_TO_RAD, coes.omega, 1e-3);
    EXPECT_NEAR(227.89*MATH_DEG_TO_RAD, coes.raan, 1e-3);
    EXPECT_NEAR(92.335*MATH_DEG_TO_RAD, coes.theta, 1e-3);
}

/// Test Case: Orbital Mechanics for Engineering Students 1st Edition, Howard Curtis, Example 4.3.
TEST(StateVector2CoesTest, SolvesCurtisTestCase)
{
    double mu = ASTRO_MU_EARTH;
    StateVector stateVector;
    stateVector.position = Vector3(-6045.0, -3490.0, 2500.0);
    stateVector.velocity = Vector3(-3.457, 6.618, 2.533);
    Coes coes;
    Orbit::ConvertStateVector2Coes(stateVector, &coes, mu);
    EXPECT_NEAR(8788.0, coes.a, 1e-1);
    EXPECT_NEAR(0.1712, coes.ecc, 1e-4);
    EXPECT_NEAR(153.2*MATH_DEG_TO_RAD, coes.incl, 1e-3);
    EXPECT_NEAR(20.07*MATH_DEG_TO_RAD, coes.omega, 1e-3);
    EXPECT_NEAR(255.3*MATH_DEG_TO_RAD, coes.raan, 1e-3);
    EXPECT_NEAR(28.45*MATH_DEG_TO_RAD, coes.theta, 1e-3);
}

/// Test Case: Fundamentals of Astrodynamics and Applications 3rd Edition, David Vallado, Example 2-6.
TEST(Coes2StateVectorTest, SolvesValladoTestCase)
{
    double mu = ASTRO_MU_EARTH;
    double p = 11067.790;
    Coes coes;
    coes.ecc = 0.83285;
    coes.incl = 87.87 * MATH_DEG_TO_RAD;
    coes.raan = 227.89 * MATH_DEG_TO_RAD;
    coes.omega = 53.38 * MATH_DEG_TO_RAD;
    coes.theta = 92.335 * MATH_DEG_TO_RAD;
    coes.a = p / (1.0 - coes.ecc*coes.ecc);
    StateVector stateVector;  
    Orbit::ConvertCoes2StateVector(coes, &stateVector, mu);
    EXPECT_NEAR(6525.344, stateVector.position.x, 1e-1);
    EXPECT_NEAR(6861.535, stateVector.position.y, 1e-1);
    EXPECT_NEAR(6449.125, stateVector.position.z, 1e-1);
    EXPECT_NEAR(4.902276, stateVector.velocity.x, 1e-4);
    EXPECT_NEAR(5.533124, stateVector.velocity.y, 1e-4);
    EXPECT_NEAR(-1.975709, stateVector.velocity.z, 1e-4);
}

/// Test Case: Orbital Mechanics for Engineering Students 1st Edition, Howard Curtis, Example 4.5.
TEST(Coes2StateVectorTest, SolvesCurtisTestCase)
{
    double mu = ASTRO_MU_EARTH;
    double h = 80000;
    Coes coes;
    coes.ecc = 1.4;
    coes.incl = 30.0 * MATH_DEG_TO_RAD;
    coes.raan = 40.0 * MATH_DEG_TO_RAD;
    coes.omega = 60.0 * MATH_DEG_TO_RAD;
    coes.theta = 30.0 * MATH_DEG_TO_RAD;
    coes.a = h*h/mu / (1.0 - coes.ecc*coes.ecc);
    StateVector stateVector;
    Orbit::ConvertCoes2StateVector(coes, &stateVector, mu);
    EXPECT_NEAR(-4040.0, stateVector.position.x, 1.0);
    EXPECT_NEAR(4815.0, stateVector.position.y, 1.0);
    EXPECT_NEAR(3629.0, stateVector.position.z, 1.0);
    EXPECT_NEAR(-10.39, stateVector.velocity.x, 1e-2);
    EXPECT_NEAR(-4.772, stateVector.velocity.y, 1e-2);
    EXPECT_NEAR(1.744, stateVector.velocity.z, 1e-2);
}