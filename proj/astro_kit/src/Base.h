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

#pragma once
// Base file for common includes, constants, and functions.
// Reference: Inspired by GamePlay 3D game framework (gameplay3d.org) 

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

// Common dependencies
#include "Vector3.h"

// Bring common dependency data structures into global namespace
using gameplay::Vector3;

// Common
#ifndef NULL
#define NULL        0
#endif

// Fundamental datatypes
enum State
{
    STATE_INVALID_TYPE = -1,
    STATE_DIRTY,
    STATE_CLEAN,
    STATE_COUNT
};

enum OrbitDirection
{
    ORBIT_DIR_INVALID_DIR = -1,
    ORBIT_DIR_PROGRADE,
    ORBIT_DIR_RETROGRADE,
    ORBIT_DIR_COUNT
};

enum OrbitType
{
    ORBIT_INVALID_TYPE = -1,
    ORBIT_CIRCULAR,
    ORBIT_ELLIPTICAL,
    ORBIT_PARABOLIC,
    ORBIT_HYPERBOLIC,
    ORBIT_COUNT
};

enum OrbitalBodyType
{
    ORBIT_BODY_INVALID_TYPE = -1,
    ORBIT_BODY_PLANET,
    ORBIT_BODY_MOON,
    ORBIT_BODY_ASTEROID,
    ORBIT_BODY_COMET,
    ORBIT_BODY_SATELLITE,
    ORBIT_BODY_COUNT
};

enum Planets
{
    PLANET_INVALID_TYPE = -1,
    PLANET_MERCURY,
    PLANET_VENUS,
    PLANET_EARTH,
    PLANET_MARS,
    PLANET_JUPITER,
    PLANET_SATURN,
    PLANET_URANUS,
    PLANET_NEPTUNE,
    PLANET_PLUTO,
    PLANET_COUNT
};

enum EphemerisType
{
    EPHEMERIS_INVALID_TYPE = -1,
    EPHEMERIS_ANALYTICAL,
    EPHEMERIS_JPL,
    EPHEMERIS_COUNT
};

enum LambertType
{
    LAMBERT_INVALID_TYPE = -1,
    LAMBERT_EXP_SINUSOID,
    LAMBERT_BATTIN,
    LAMBERT_UNIVERSAL_VAR,
    LAMBERT_UNIVERSAL_VAR_GPU,
    LAMBERT_COUNT
};

enum PropagateType
{
    PROPAGATE_INVALID_TYPE = -1,
    PROPAGATE_COES,
    PROPAGATE_RV,
    PROPAGATE_JPL_EPHEMERIS,
    PROPAGATE_COUNT,
};

/// State Vector
struct StateVector
{
    Vector3 position;
    Vector3 velocity;

    inline bool operator==(const StateVector& rhs) const
    {
        return (position == rhs.position && velocity == rhs.velocity);
    }
};

/// Classical Orbital Elements
struct OrbitalElements
{
    double semimajorAxis; /// Semimajor axis
    double eccentricity;  /// Eccentricity
    double argPerigee;    /// Arguement of perigee
    double inclination;   /// Inclination
    double raan;          /// Right ascension of the ascending node
    double trueAnomaly;   /// True anomaly
    double timePerigee;   /// Time of perigee

    inline bool operator==(const OrbitalElements& rhs) const
    {
        return (semimajorAxis == rhs.semimajorAxis &&
                eccentricity  == rhs.eccentricity  &&
                argPerigee    == rhs.argPerigee    &&
                inclination   == rhs.inclination   &&
                raan          == rhs.raan          &&
                trueAnomaly   == rhs.trueAnomaly   &&
                timePerigee   == rhs.timePerigee);
    }
    
};

// Math
const double MATH_DEG_TO_RAD        = 0.0174532925;
const double MATH_RAD_TO_DEG        = 57.29577951f;
const double MATH_FLOAT_SMALL       = 1.0e-37f;
const double MATH_NEAR_ZERO         = 2.0e-37f;
const double MATH_TOLERANCE         = 1.0e-8f;
const double MATH_INFINITY          = 1.0e37f;
const double MATH_E                 = 2.71828182845904523536;
const double MATH_LOG10E            = 0.4342944819032518;
const double MATH_LOG2E             = 1.442695040888963387;
const double MATH_PI                = 3.14159265358979323846;
const double MATH_2_PI              = 6.28318530717958647693;
const double MATH_1_OVER_PI         = 0.31830988618379067154;
const double MATH_PI_OVER_2         = 1.57079632679489661923;
const double MATH_PI_OVER_4         = 0.785398163397448309616;
const double MATH_DAY_TO_SEC        = 86400.0;
const double MATH_SEC_TO_DAY        = 1.0 / MATH_DAY_TO_SEC;
const Vector3 MATH_UNIT_VEC_I       = Vector3(1.0f, 0.0, 0.0);
const Vector3 MATH_UNIT_VEC_J       = Vector3(0.0f, 1.0, 0.0);
const Vector3 MATH_UNIT_VEC_K       = Vector3(0.0f, 0.0, 1.0);

// Astrodynamics
const double ASTRO_AU_TO_KM         = 149597870.66;     // Convert Astronomical Units (AU) to km
const double ASTRO_ER_TO_KM         = 6378.137;         // Mean equitorial radius of Earth (ER) to km
const double ASTRO_MU_SUN           = 132712428000;     // Gravitional Parameter of the Sun (km3/s2)
const double ASTRO_MU_EARTH         = 398600.4418;      // Gravitional Parameter of the Earth
const double ASTRO_ECC_CIRCULAR     = 0.0;              // Eccentricity of a ciruclar orbit
const double ASTRO_ECC_PARABOLIC    = 1.0;              // Eccentricity of a parabolic orbit
const double ASTRO_INCL_EQUATORIAL  = 0.0;              // Inclination of an equatorial orbit

// Unit testing
const double TEST_DU_TOLERANCE      = 1.0e-3;
const double TEST_VU_TOLERANCE      = 1.0e-3;
const double TEST_TU_TOLERANCE      = 1.0e-3;
const double TEST_ANGLE_TOLERANCE   = 1.0e-3;
const double TEST_ECC_TOLERANCE     = 1.0e-4;

// NOMINMAX makes sure that windef.h doesn't add macros min and max
#ifdef WIN32
    #define NOMINMAX
#endif

/// Clamps x between lo and hi.
template<typename T>
inline const T& Clamp(const T& x, const T& lo, const T& hi)
{ return ((x < lo) ? lo : ((x > hi) ? hi : x)); }

/// Returns true if x is between lo and hi (inclusive).
template<typename T>
inline bool IsBetween(const T& x, const T& lo, const T& hi)
{ return x >= lo && x <= hi; }

/// Returns the mininum of a and b.
template<typename T>
inline const T& Min(const T &a, const T &b)
{ return a < b ? a : b; }

/// Returns the maximum of a and b.
template<typename T>
inline const T& Max(const T &a, const T &b)
{ return a > b ? a : b; }

/// Returns a random double between 0 and 1 (inclusive).
inline double Random0_1()
{ return (double)rand()/RAND_MAX; }

/// Returns a random double between -1 and 1 (inclusive).
inline double RandomMinus1_1()
{ return 2.0f*Random0_1() - 1.0f; }

/// Returns r rounded to the nearest int (0.5 is rounded up)
inline double Round(double r)
{ return (r > 0.0f) ? floor(r + 0.5f) : ceil(r - 0.5f); }

/// Returns r rounded towards zero.
inline double Round0(double r)
{ return (r > 0.0f) ? floor(r) : ceil(r); }

/// Returns positive one if x is greater than or equal to zero, return negative one otherwise.
inline double Sign(double x)
{ return (x >= 0) ? 1.0 : -1.0; }

/// Returns the inverse hyperbolic sine of x.
inline double asinh(double x)
{ return log(x + sqrt(x*x + 1.0f)); }

/// Returns the inverse hyperbolic cosine of x.
inline double acosh(double x)
{ return log(x + sqrt(x*x - 1.0)); }

/// Returns the inverse hyperbolic tangent of x.
inline double atanh(double x)
{ return 0.5f*log((1.0f+x)/(1.0f-x)); }

/// Returns the square of x.
inline double SQR(double x)
{return x*x;}

#if defined(WIN32)
    //#pragma warning( disable : 4172 )               // returning address of local variable or temporary
    #pragma warning( disable : 4244 )               // 'conversion' conversion from 'type1' to 'type2', possible loss of data
    //#pragma warning( disable : 4311 )               // 'type cast': pointer truncation from 'type' to 'type'
    //#pragma warning( disable : 4390 )               // empty controlled statement found; is this the intent?
    #pragma warning( disable : 4800 )               // 'type': forcing value to bool 'true' or 'false' (performance warning)
    //#pragma warning( disable : 4996 )               // 'function': was declared deprecated
#endif


///// Print logging
//void printError(const char* format, ...)
//{
//#ifdef WIN32
//    va_list argptr;
//    va_start(argptr, format);
//    fprintf(stderr, "\n");
//    int sz = vfprintf_s(stderr, format, argptr);
//    if (sz > 0)
//    {
//        char* buf = new char[sz +2];
//        vsprintf_s(buf, format, argptr);
//        buf[sz] = '\n';
//        buf[sz+1] = 0;
//    }
//#elif __APPLE__
//    va_list argptr;
//    va_start(argptr, format);
//    vfprintf(stderr, format, argptr);
//    fprintf(stderr, "\n");
//    va_end(argptr);
//#endif
//}
//
//// System Errors
//#define LOG_ERROR(x) \
//{ \
//    LOGI(x); \
//    assert(#x == 0); \
//}
//
//// Warning macro
//#ifdef WARN
//#undef WARN
//#endif
//#define WARN(x) printError(x)
//#define WARN_VARG(x, ...) printError(_XA, __VA_ARGS__) 

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
