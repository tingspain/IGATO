#pragma once
#include "Vector3.h"

struct StateVector
{
    Vector3 position;
    Vector3 velocity;
};

struct Coes
{
    double a;       // semimajor axis;
    double e;       // eccentricity;
    double w;       // arguementOfPerigee;
    double i;       // inclination
    double raan;    // right ascension of the ascending node
    double tp;      // time of perigee
    double theta;   // true anomaly
};

class Orbit
{
public:

    enum State
    {
        DIRTY = 0,
        CLEAN,
    };

    Orbit(double mu);
    Orbit(const StateVector& stateVector, double mu);
    Orbit(const Vector3& position, const Vector3& velocity, double mu);
    Orbit(const Coes& coes, double mu);

    void SetStateVector(const StateVector& stateVector);
    void SetStateVector(const Vector3& position, const Vector3& velocity);
    void SetCoes(const Coes& coes);

    const StateVector& GetStateVector() const;
    const Coes& GetCoes() const;
    double GetMu() const {return _mu;}
    
    void Propagate(double timeOfFlight);

    static void ConvertStateVector2Coes(const StateVector& stateVector, Coes* coes);
    static void ConvertCoes2StateVector(const Coes& coes, StateVector* stateVector);

private:
    void UpdateStateVector() const;
    void UpdateCoes() const;

private:
    double _mu;
    double _radius;
    mutable StateVector _stateVector;
    mutable Coes _coes;

    mutable State _stateVectorState;
    mutable State _coesState;
};