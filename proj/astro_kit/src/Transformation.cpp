#include "Transformation.h"
#include "Vector3.h"
#include "Base.h"

void Perifocal2Inertial(const Vector3& vectorPerifocal, double incl, double raan, double omega, Vector3* vectorInertial)
{
    static Vector3 row1, row2, row3;

    float cosRAAN = cos(raan);
    float sinRAAN = sin(raan);

    float cosOmega = cos(omega);
    float sinOmega = sin(omega);

    float cosIncl = cos(incl);
    float sinIncl = sin(incl);

    row1.x =  (cosRAAN * cosOmega) - (sinRAAN * sinOmega * cosIncl);
    row1.y = -(cosRAAN * sinOmega) - (sinRAAN * cosIncl * cosOmega);
    row1.z =  (sinRAAN * sinIncl);

    row2.x =  (sinRAAN * cosOmega) + (cosRAAN * cosIncl * sinOmega);
    row2.y = -(sinRAAN * sinOmega) + (cosRAAN * cosIncl * cosOmega);
    row2.z = -(cosRAAN * sinIncl);

    row3.x =  (sinIncl * sinOmega);
    row3.y =  (sinIncl * cosOmega);
    row3.z =  (cosIncl);

    vectorInertial->x = row1.dot(vectorPerifocal);
    vectorInertial->y = row2.dot(vectorPerifocal);
    vectorInertial->z = row3.dot(vectorPerifocal);
}