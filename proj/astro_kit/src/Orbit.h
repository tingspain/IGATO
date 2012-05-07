#pragma once
#include "Base.h"

struct StateVector
{
    Vector3 position;
    Vector3 velocity;
};

struct Coes
{
    double a;       /// semimajor axis;
    double ecc;     /// eccentricity;
    double omega;   /// arguementOfPerigee;
    double incl;    /// inclination
    double raan;    /// right ascension of the ascending node
    double theta;   /// true anomaly
    double tp;      /// time of perigee  
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

    /// Convert state vectors to orbital elements.
    /**
     This routine calculates the classical orbital elements (coes) of an object given its position
     and velocity (state) vectors and the gravitional parameter of the central body.

     Reference: Fundamentals of Astrodynamics and Applications 3rd Edition, David Vallado, Algorithm 9.

     @param stateVector : The position and velocity vectors.
     @param [out] coes : The computed orbital elements.
     @param mu : The gravitional parameter.
    */
    static void ConvertStateVector2Coes(const StateVector& stateVector, Coes* coes, double mu);

    /// Convert orbital elements to state vectors.
    /**
     This routine calculates the position and velocity (state) vectors of an object given its
     classical orbital elements (coes) and the gravitational parameter of the central body.

     Reference: Fundamentals of Astrodynamics and Applications 3rd Edition, David Vallado, Algorithm 10.

     @param coes : The orbital elements.
     @param [out] stateVector : The computed position and velocity vectors.
     @param mu : The gravitational parameter.
    */
    static void ConvertCoes2StateVector(const Coes& coes, StateVector* stateVector, double mu);

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