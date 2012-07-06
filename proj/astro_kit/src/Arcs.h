#pragma once
#include "Base.h"

class Arc
{
public:
    Arc() {}
    virtual ~Arc() {}

    void GetInitialStateVector(StateVector* stateVector) const {*stateVector = _initialStateVector;}
    void GetFinalStateVector(StateVector* stateVector) const {*stateVector = _finalStateVector;}

    virtual void SetInitialConditions(const Vector3& initialCondition1, const Vector3& initialCondition2) = 0;
    virtual void Evaluate(double timeOfFlight) = 0;
    virtual void CompareToPreviousArc(const Arc& nextArc, Vector3* deltaVelocity);

protected:
    StateVector _initialStateVector;
    StateVector _finalStateVector;
    StateVector _dummyStateVector;
};

class LambertArc : public Arc
{
public:
    LambertArc(OrbitDirection orbitDirection, int maxRevolutions);
    virtual ~LambertArc() {}

    void SetOrbitDirection(OrbitDirection direction) {_orbitDirection = direction;}
    void SetMaxNumberRevolutions(int maxRevolutions) {_maxRevolutions = maxRevolutions;}

    OrbitDirection GetOrbitDirection() const {return _orbitDirection;}
    int GetMaxNumberRevolutions() const {return _maxRevolutions;}

    virtual void SetInitialConditions(const Vector3& initialCondition1, const Vector3& initialCondition2);
    virtual void Evaluate(double timeOfFlight);

protected:
    OrbitDirection _orbitDirection;
    int _maxRevolutions;
};

class CoastArc : public Arc
{
public:
    CoastArc(PropagateType propagateType);
    virtual ~CoastArc() {}

    void SetPropagateType(PropagateType propagateType) {_propagateType = propagateType;}
    
    PropagateType GetPropagateType() const {return _propagateType;}

    virtual void SetInitialConditions(const Vector3& initialCondition1, const Vector3& initialCondition2);
    virtual void Evaluate(double timeOfFlight);

protected:
    PropagateType _propagateType;
};
