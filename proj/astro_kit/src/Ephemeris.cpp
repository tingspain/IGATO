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

#include "Ephemeris.h"
#include "KeplersEquations.h"
#include "Conversions.h"

#include "jpleph.h"
#include "jpl_int.h"

// Static field initialization
Ephemeris* EphemerisManager::_ephemeris = NULL;

void EphemerisManager::SetEphemerisType(EphemerisType ephemerisType)
{
    Cleanup();

    switch (ephemerisType)
    {
    case EPHEMERIS_ANALYTICAL:
        _ephemeris = new AnalyticalEphemeris();
        break;

    case EPHEMERIS_JPL:
        _ephemeris = new JplEphemeris();
        break;

    default:
        throw "Invalid ephemeris source type";
    }
}

void EphemerisManager::GetOrbitAtEpoch(int objectId, double epoch, OrbitalElements* orbitalElements, StateVector* stateVector)
{
    if (_ephemeris != NULL)
    {
        _ephemeris->GetOrbitAtEpoch(objectId, epoch, orbitalElements, stateVector);
    }
    else
    {
        throw "Ephemeris source type has not been initialized yet";
    }
}

void EphemerisManager::Cleanup()
{
    if (_ephemeris != NULL)
    {
        delete _ephemeris;
        _ephemeris = NULL;
    }
}

void AnalyticalEphemeris::GetOrbitAtEpoch(int objectId, double epoch, OrbitalElements* orbitalElements, StateVector* stateVector)
{
    assert(objectId >= 0 && objectId < 10);
    assert(epoch > 0);

    // Nothing to do, get out and report the error.
    if (orbitalElements == NULL && stateVector == NULL)
    {
        // log error
        return;
    }

    // We must compute the orbital elements. If we don't want them,
    // then we use a dummy variable.
    if (orbitalElements != NULL)
    {
        Calculate(objectId, epoch, orbitalElements);
        
    }
    else
    {
        Calculate(objectId, epoch, &_dummyCoes);
    }

    if (orbitalElements != NULL && stateVector != NULL) // orbitalElements and state vector are outputs
    {
        ConvertOrbitalElements2StateVector(*orbitalElements, stateVector); 
    }
    else if (stateVector != NULL) // only state vector is output
    {
        ConvertOrbitalElements2StateVector(_dummyCoes, stateVector);
    }
    else if (orbitalElements != NULL) // only orbitalElements is output
    {
        // do nothing
    }
}

void AnalyticalEphemeris::Calculate(int planetId, double epoch, OrbitalElements* orbitalElements)
{
    assert(orbitalElements != NULL);
    // Reference: ESA, PaGMO - Planet_Ephemerides_Analytical function

    double mjd2000 = epoch - 2451545;
    double T = (mjd2000 + 36525.00) / 36525.00;

    double semimajorAxis, eccentricity, inclination, RA, w, XM, M, E;
    switch (planetId)
    {
    case PLANET_MERCURY:
        semimajorAxis=(0.38709860);
        eccentricity=(0.205614210 + 0.000020460*T - 0.000000030*T*T);
        inclination=(7.002880555555555560 + 1.86083333333333333e-3*T - 1.83333333333333333e-5*T*T);
        RA=(4.71459444444444444e+1 + 1.185208333333333330*T + 1.73888888888888889e-4*T*T);
        w=(2.87537527777777778e+1 + 3.70280555555555556e-1*T +1.20833333333333333e-4*T*T);
        XM   = 1.49472515288888889e+5 + 6.38888888888888889e-6*T;
        M=(1.02279380555555556e2 + XM*T);
        break;

    case PLANET_VENUS:
        semimajorAxis=(0.72333160);
        eccentricity=(0.006820690 - 0.000047740*T + 0.0000000910*T*T);
        inclination=(3.393630555555555560 + 1.00583333333333333e-3*T - 9.72222222222222222e-7*T*T);
        RA=(7.57796472222222222e+1 + 8.9985e-1*T + 4.1e-4*T*T);
        w=(5.43841861111111111e+1 + 5.08186111111111111e-1*T -1.38638888888888889e-3*T*T);
        XM =5.8517803875e+4 + 1.28605555555555556e-3*T;
        M=(2.12603219444444444e2 + XM*T);
        break;

    case PLANET_EARTH:
        semimajorAxis=(1.000000230);
        eccentricity=(0.016751040 - 0.000041800*T - 0.0000001260*T*T);
        inclination=(0.00);
        RA=(0.00);
        w=(1.01220833333333333e+2 + 1.7191750*T + 4.52777777777777778e-4*T*T + 3.33333333333333333e-6*T*T*T);
        XM   = 3.599904975e+4 - 1.50277777777777778e-4*T - 3.33333333333333333e-6*T*T;
        M=(3.58475844444444444e2 + XM*T);
        break;

    case PLANET_MARS:
        semimajorAxis=(1.5236883990);
        eccentricity=(0.093312900 + 0.0000920640*T - 0.0000000770*T*T);
        inclination=(1.850333333333333330 - 6.75e-4*T + 1.26111111111111111e-5*T*T);
        RA=(4.87864416666666667e+1 + 7.70991666666666667e-1*T - 1.38888888888888889e-6*T*T - 5.33333333333333333e-6*T*T*T);
        w=(2.85431761111111111e+2 + 1.069766666666666670*T +  1.3125e-4*T*T + 4.13888888888888889e-6*T*T*T);
        XM   = 1.91398585e+4 + 1.80805555555555556e-4*T + 1.19444444444444444e-6*T*T;
        M=(3.19529425e2 + XM*T);
        break;

    case PLANET_JUPITER:
        semimajorAxis=(5.2025610);
        eccentricity=(0.048334750 + 0.000164180*T  - 0.00000046760*T*T -0.00000000170*T*T*T);
        inclination=(1.308736111111111110 - 5.69611111111111111e-3*T +  3.88888888888888889e-6*T*T);
        RA=(9.94433861111111111e+1 + 1.010530*T + 3.52222222222222222e-4*T*T - 8.51111111111111111e-6*T*T*T);
        w=(2.73277541666666667e+2 + 5.99431666666666667e-1*T + 7.0405e-4*T*T + 5.07777777777777778e-6*T*T*T);
        XM   = 3.03469202388888889e+3 - 7.21588888888888889e-4*T + 1.78444444444444444e-6*T*T;
        M=(2.25328327777777778e2 + XM*T);
        break;

    case PLANET_SATURN:
        semimajorAxis=(9.5547470);
        eccentricity=(0.055892320 - 0.00034550*T - 0.0000007280*T*T + 0.000000000740*T*T*T);
        inclination=(2.492519444444444440 - 3.91888888888888889e-3*T - 1.54888888888888889e-5*T*T + 4.44444444444444444e-8*T*T*T);
        RA=(1.12790388888888889e+2 + 8.73195138888888889e-1*T -1.52180555555555556e-4*T*T - 5.30555555555555556e-6*T*T*T);
        w=(3.38307772222222222e+2 + 1.085220694444444440*T + 9.78541666666666667e-4*T*T + 9.91666666666666667e-6*T*T*T);
        XM   = 1.22155146777777778e+3 - 5.01819444444444444e-4*T - 5.19444444444444444e-6*T*T;
        M=(1.75466216666666667e2 + XM*T);
        break;

    case PLANET_URANUS:
        semimajorAxis=(19.218140);
        eccentricity=(0.04634440 - 0.000026580*T + 0.0000000770*T*T);
        inclination=(7.72463888888888889e-1 + 6.25277777777777778e-4*T + 3.95e-5*T*T);
        RA=(7.34770972222222222e+1 + 4.98667777777777778e-1*T + 1.31166666666666667e-3*T*T);
        w=(9.80715527777777778e+1 + 9.85765e-1*T - 1.07447222222222222e-3*T*T - 6.05555555555555556e-7*T*T*T);
        XM   = 4.28379113055555556e+2 + 7.88444444444444444e-5*T + 1.11111111111111111e-9*T*T;
        M=(7.26488194444444444e1 + XM*T);
        break;

    case PLANET_NEPTUNE:
        semimajorAxis=(30.109570);
        eccentricity=(0.008997040 + 0.0000063300*T - 0.0000000020*T*T);
        inclination=(1.779241666666666670 - 9.54361111111111111e-3*T - 9.11111111111111111e-6*T*T);
        RA=(1.30681358333333333e+2 + 1.0989350*T + 2.49866666666666667e-4*T*T - 4.71777777777777778e-6*T*T*T);
        w=(2.76045966666666667e+2 + 3.25639444444444444e-1*T + 1.4095e-4*T*T + 4.11333333333333333e-6*T*T*T);
        XM   = 2.18461339722222222e+2 - 7.03333333333333333e-5*T;
        M=(3.77306694444444444e1 + XM*T);
        break;

    case PLANET_PLUTO:
        //Fifth order polynomial least square fit generated by Dario Izzo
        //(ESA ACT). JPL405 ephemerides (Charon-Pluto barycenter) have been used to produce the coefficients.
        //This approximation should not be used outside the range 2000-2100;
        T =mjd2000/36525.00;
        semimajorAxis=(39.34041961252520 + 4.33305138120726*T - 22.93749932403733*T*T + 48.76336720791873*T*T*T - 45.52494862462379*T*T*T*T + 15.55134951783384*T*T*T*T*T);
        eccentricity=(0.24617365396517 + 0.09198001742190*T - 0.57262288991447*T*T + 1.39163022881098*T*T*T - 1.46948451587683*T*T*T*T + 0.56164158721620*T*T*T*T*T);
        inclination=(17.16690003784702 - 0.49770248790479*T + 2.73751901890829*T*T - 6.26973695197547*T*T*T + 6.36276927397430*T*T*T*T - 2.37006911673031*T*T*T*T*T);
        RA=(110.222019291707 + 1.551579150048*T - 9.701771291171*T*T + 25.730756810615*T*T*T - 30.140401383522*T*T*T*T + 12.796598193159 * T*T*T*T*T);
        w=(113.368933916592 + 9.436835192183*T - 35.762300003726*T*T + 48.966118351549*T*T*T - 19.384576636609*T*T*T*T - 3.362714022614 * T*T*T*T*T);
        M=(15.17008631634665 + 137.023166578486*T + 28.362805871736*T*T - 29.677368415909*T*T*T - 3.585159909117*T*T*T*T + 13.406844652829 * T*T*T*T*T);
        break;
    }

    orbitalElements->semimajorAxis = semimajorAxis; // units are AU (already in DU)
    orbitalElements->eccentricity = eccentricity;
       
    // conversion of DEG into RAD
    orbitalElements->inclination = inclination * MATH_DEG_TO_RAD;
    orbitalElements->raan = RA   * MATH_DEG_TO_RAD;
    orbitalElements->argPerigee = w    * MATH_DEG_TO_RAD;
    M *= MATH_DEG_TO_RAD;
    M = fmod(M, 2.0 * MATH_PI);

    // Conversion from Mean Anomaly to Eccentric Anomaly via Kepler's equation
    E = SolveKeplersEquationE(orbitalElements->eccentricity, M);

    // Convert Eccentric Anomaly to True Anomaly
    //orbitalElements.TA  = 2 * atan(sqrt((double) (1 + orbitalElements.e) / (1 - orbitalElements.e)) * tan((double) E / 2));
    orbitalElements->trueAnomaly = E;
}

void JplEphemeris::SetEphemerisFile(const std::string& filepath)
{
    _ephemerisFile = filepath;
    _ephemerisState = STATE_DIRTY;
}

void JplEphemeris::GetOrbitAtEpoch(int objectId, double epoch, OrbitalElements* orbitalElements, StateVector* stateVector)
{
}

void JplEphemeris::QueryDatabase(int planetId, double epoch, StateVector* stateVector)
{
    // Make sure the current jpl ephemeris file has already been initialized
    if (_ephemerisState == STATE_DIRTY)
    {
        if (_ephemerisData != NULL)
        {
            delete _ephemerisData;
            _ephemerisData = NULL;
        }

        // Initialize the jpl ephemeris file
        void* result = jpl_init_ephemeris(_ephemerisFile.c_str(), NULL, NULL);

        if (result != NULL)
        {
            _ephemerisData = reinterpret_cast<jpl_eph_data*>(result);
            assert(_ephemerisData != NULL);
            _ephemerisState = STATE_CLEAN;
        }
        else
        {
            throw "Failed to initialize JPL ephemeris file";
        }
    }

    // Query the ephemeris database
    double rv[6];
    jpl_pleph(_ephemerisData, epoch, planetId + 1, 12, rv, 1);
    stateVector->position.x = rv[0];
    stateVector->position.y = rv[1];
    stateVector->position.z = rv[2];

    stateVector->velocity.x = rv[3];
    stateVector->velocity.y = rv[4];
    stateVector->velocity.z = rv[5];
}

