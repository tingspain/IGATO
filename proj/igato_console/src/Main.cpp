#include <iostream>
#include "Orbit.h"
#include "Base.h"

/**
 * Main entry point.
 */
int main(int argc, char *argv[])
{
    Orbit orbit(ASTRO_MU_SUN);

    std::cin.get();
    return 0;
}