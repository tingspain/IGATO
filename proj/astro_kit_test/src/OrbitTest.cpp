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
