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
#include "Base.h"

// Forward declaration
class Lambert;

class LambertManager
{
public:
    static void SetLambertType(LambertType lambertType);

    static void Evaluate(const Vector3& initialPosition,
                         const Vector3& finalPosition,
                         double timeOfFlight,
                         OrbitDirection orbitDirection,
                         int numberRevolutions,
                         Vector3* initialVelocity,
                         Vector3* finalVelocity);
    
    static void Cleanup();

private:
    /// Static class only, prevent instantiation.
    LambertManager();

private:
    static Lambert* _lambertSolver;
};

/// Abstract base class for all Lambert solver algorithms.
class Lambert
{
public:
    virtual void Evaluate(const Vector3& initialPosition,
                          const Vector3& finalPosition,
                          double timeOfFlight,
                          OrbitDirection orbitDirection,
                          int numberRevolutions,
                          Vector3* initialVelocity,
                          Vector3* finalVelocity) = 0;
};

class ExpSinusoidLambert : public Lambert
{
public:
    virtual void Evaluate(const Vector3& initialPosition,
                          const Vector3& finalPosition,
                          double timeOfFlight,
                          OrbitDirection orbitDirection,
                          int numberRevolutions,
                          Vector3* initialVelocity,
                          Vector3* finalVelocity);

protected:
    void CalculateTimeOfFlight(double x, double s, double c, int longway, double N, double* tof);
};

class BattinsLambert : public Lambert
{
public:
    virtual void Evaluate(const Vector3& initialPosition,
                          const Vector3& finalPosition,
                          double timeOfFlight,
                          OrbitDirection orbitDirection,
                          int numberRevolutions,
                          Vector3* initialVelocity,
                          Vector3* finalVelocity);
};

class UniversalVarLambert : public Lambert
{
public:
    virtual void Evaluate(const Vector3& initialPosition,
                          const Vector3& finalPosition,
                          double timeOfFlight,
                          OrbitDirection orbitDirection,
                          int numberRevolutions,
                          Vector3* initialVelocity,
                          Vector3* finalVelocity);
};

class UniversalVarGpuLambert : public Lambert
{
public:
    virtual void Evaluate(const Vector3& initialPosition,
                          const Vector3& finalPosition,
                          double timeOfFlight,
                          OrbitDirection orbitDirection,
                          int numberRevolutions,
                          Vector3* initialVelocity,
                          Vector3* finalVelocity);
};