#pragma once

// Forward declarations
class Vector3;

void Perifocal2Inertial(const Vector3& vectorPerifocal, double incl, double raan, double omega, Vector3* vectorInertial);