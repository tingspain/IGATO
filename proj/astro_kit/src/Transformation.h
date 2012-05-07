#pragma once
#include "Base.h"

/// Transform a 3D vector from perifocal to inertial coordinates.
/**
 Reference: Orbital Mechanics for Engineering Students 1st Edition, Howard Curtis, Eqn 4.44.

 @param perifocalVector : 3D vector in perifocal coordinates.
 @param incl : The inclination (radians)
 @param raan : The right ascension of the ascending node (radians)
 @param omega : The true anomaly (radians)
 @param [out] inertialVector : The computed 3D vector in inertial coordinates
*/
void Perifocal2Inertial(const Vector3& perifocalVector, double incl, double raan, double omega, Vector3* inertialVector);