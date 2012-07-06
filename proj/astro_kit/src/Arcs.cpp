#include "Arcs.h"
#include "Lambert.h"

void Arc::CompareToPreviousArc(const Arc& previousArc, Vector3* deltaVelocity)
{
    previousArc.GetFinalStateVector(&_dummyStateVector);
    *deltaVelocity = _initialStateVector.velocity - _dummyStateVector.velocity;
}

LambertArc::LambertArc(OrbitDirection orbitDirection, int maxRevolutions)
    : Arc()
{
    _orbitDirection = orbitDirection;
    _maxRevolutions = maxRevolutions;
}

void LambertArc::SetInitialConditions(const Vector3& initialCondition1, const Vector3& initialCondition2)
{
    _initialStateVector.position = initialCondition1;
    _finalStateVector.position = initialCondition2;
}

void LambertArc::Evaluate(double timeOfFlight)
{
    assert(timeOfFlight > 0.0);
    LambertManager::Evaluate(_initialStateVector.position, _initialStateVector.velocity,
                             timeOfFlight,
                             _orbitDirection,
                             _maxRevolutions,
                             &_finalStateVector.position, &_finalStateVector.velocity);
}

CoastArc::CoastArc(PropagateType propagateType)
    : Arc()
{
    _propagateType = propagateType;
}

void CoastArc::SetInitialConditions(const Vector3& initialCondition1, const Vector3& initialCondition2)
{
    _initialStateVector.position = initialCondition1;
    _initialStateVector.velocity = initialCondition2;
}

void CoastArc::Evaluate(double timeOfFlight)
{
    assert(timeOfFlight > 0.0);
    switch (_propagateType)
    {
    case PROPAGATE_COES:
        break;

    case PROPAGATE_RV:
        break;

    case PROPAGATE_JPL_EPHEMERIS:
        break;

    default:
        throw "Invalid propagation algorithm type";
    }
}