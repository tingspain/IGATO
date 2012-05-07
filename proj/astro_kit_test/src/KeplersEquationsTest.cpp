#include "gtest/gtest.h"
#include "KeplersEquations.h"
#include "Base.h"

/// Test Case: Fundamentals of Astrodynamics and Applications 3rd Edition, David Vallado, Example 2-1.
TEST(KeplersEquationE, SolvesValladoTestCase)
{
    double ecc = 0.4;
    double M = 235.4 * MATH_DEG_TO_RAD;
    double E = SolveKeplersEquationE(ecc, M);
    EXPECT_NEAR(3.8486971, E, 1e-4);
}

TEST(KeplersEquationEDeathTest, EccentricityIsNotValid)
{
    double ecc = 1.1;
    double M = 0.0;
    EXPECT_DEBUG_DEATH(SolveKeplersEquationE(ecc, M), "Assertion failed: ecc >= 0.0 && ecc < 1.0");
}

/// Test Case: Fundamentals of Astrodynamics and Applications 3rd Edition, David Vallado, Example 2-3.
TEST(KeplersEquationH, SolvesValladoTestCase)
{
    double ecc = 2.4;
    double M = 235.4 * MATH_DEG_TO_RAD;
    double H = SolveKeplersEquationH(ecc, M);
    EXPECT_NEAR(1.6013761449, H, 1e-4);
}

TEST(KeplersEquationHDeathTest, EccentricityIsNotValid)
{
    double ecc = 0.9;
    double M = 0.0;
    EXPECT_DEBUG_DEATH(SolveKeplersEquationH(ecc, M), "Assertion failed: ecc >= 1.0");
}