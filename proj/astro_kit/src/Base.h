#pragma once
// Base file for common includes, constants, and macros.
// Reference: GamePlay 3D game framework (gameplay3d.org) 

// C/C++
#include <new>
#include <memory>
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cwchar>
#include <cwctype>
#include <cctype>
#include <cmath>
#include <cstdarg>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <stack>
#include <map>
#include <algorithm>
#include <limits>
#include <functional>

// Bring common functions from C into global namespace
using std::fabs;
using std::sqrt;
using std::cos;
using std::sin;
using std::tan;
using std::isspace;
using std::isdigit;
using std::toupper;
using std::tolower;
using std::size_t;
using std::min;
using std::max;
using std::modf;

// Common
#ifndef NULL
#define NULL        0
#endif

// Math
#define MATH_DEG_TO_RAD(x)          ((x) * 0.0174532925f)
#define MATH_RAD_TO_DEG(x)          ((x)* 57.29577951f)
#define MATH_FLOAT_SMALL            1.0e-37f
#define MATH_TOLERANCE              2e-37f
#define MATH_E                      2.71828182845904523536f
#define MATH_LOG10E                 0.4342944819032518f
#define MATH_LOG2E                  1.442695040888963387f
#define MATH_PI                     3.14159265358979323846f
#define MATH_PIOVER2                1.57079632679489661923f
#define MATH_PIOVER4                0.785398163397448309616f
#define MATH_PIX2                   6.28318530717958647693f
#define MATH_EPSILON                0.000001f
#ifndef M_1_PI
#define M_1_PI                      0.31830988618379067154
#endif

//const double MATH_DEG_TO_RAD    = 0.0174532925;
//const double MATH_RAD_TO_DEG    = 57.29577951f;
//const double MATH_FLOAT_SMALL   = 1.0e-37f;
//const double MATH_TOLERANCE     = 2e-37f;
//const double MATH_E             = 2.71828182845904523536;
//const double MATH_LOG10E        = 0.4342944819032518;
//const double MATH_LOG2E         = 1.442695040888963387;
//const double MATH_PI            = 3.14159265358979323846;
//const double MATH_1_PI          = 0.31830988618379067154;
//const double MATH_PIOVER2       = 1.57079632679489661923;
//const double MATH_PIOVER4       = 0.785398163397448309616;
//const double MATH_PIX2          = 6.28318530717958647693;
//const double MATH_EPSILON       = 0.000001;

#define MATH_RANDOM_MINUS1_1()      ((2.0f*((float)rand()/RAND_MAX))-1.0f)      // Returns a random float between -1 and 1.
#define MATH_RANDOM_0_1()           ((float)rand()/RAND_MAX)                    // Returns a random float between 0 and 1.
#define MATH_CLAMP(x, lo, hi)       ((x < lo) ? lo : ((x > hi) ? hi : x))       // Clamps x between lo and hi.

template<typename T>
T MathClamp(T x, T low, T hi)
{
    return ((x < lo) ? lo : ((x > hi) ? hi : x));
}

#ifdef WIN32
    inline float round(float r)
    {
        return (r > 0.0f) ? floor(r + 0.5f) : ceil(r - 0.5f);
    }
#endif

// NOMINMAX makes sure that windef.h doesn't add macros min and max
#ifdef WIN32
    #define NOMINMAX
#endif

// Astrodynamics
#define ASTRO_AU_TO_KM              149597870.66;     // Convert Astronomical Units (AU) to km
#define ASTRO_MU_SUN                132712428000;     // Gravitional Parameter of the Sun [km3/s2]

#if defined(WIN32)
    //#pragma warning( disable : 4172 )               // returning address of local variable or temporary
    #pragma warning( disable : 4244 )               // 'conversion' conversion from 'type1' to 'type2', possible loss of data
    //#pragma warning( disable : 4311 )               // 'type cast': pointer truncation from 'type' to 'type'
    //#pragma warning( disable : 4390 )               // empty controlled statement found; is this the intent?
    #pragma warning( disable : 4800 )               // 'type': forcing value to bool 'true' or 'false' (performance warning)
    //#pragma warning( disable : 4996 )               // 'function': was declared deprecated
#endif

//// Assert has special behavior on Windows (for Visual Studio).
//#ifdef WIN32
//#ifdef assert
//#undef assert
//#endif
//#ifdef _DEBUG
//#define assert(expression) do { \
//    if (!(expression)) \
//    { \
//        printError("Assertion \'" #expression "\' failed."); \
//        __debugbreak(); \
//    } } while (0)
//
//#else
//#define assert(expression) do { (void)sizeof(expression); } while (0)
//#endif
//#endif
