#include "Orbit.h"
#include "Base.h"

Orbit::Orbit(double mu)
{
    _mu = mu;
}

Orbit::Orbit(const StateVector& stateVector, double mu)
{
    _mu = mu;
    SetStateVector(stateVector);
}

Orbit::Orbit(const Vector3& position, const Vector3& velocity, double mu)
{
    _mu = mu;
    SetStateVector(position, velocity);
}

Orbit::Orbit(const Coes& coes, double mu)
{
    _mu = mu;
    SetCoes(coes);
}

void Orbit::SetStateVector(const StateVector& stateVector)
{
    SetStateVector(stateVector.position, stateVector.velocity);
}

void Orbit::SetStateVector(const Vector3& position, const Vector3& velocity)
{
    _stateVector.position = position;
    _stateVector.velocity = velocity;

    _coesState = DIRTY;
}

void Orbit::SetCoes(const Coes& coes)
{
    _coes = coes;

    _stateVectorState = DIRTY;
}

const StateVector& Orbit::GetStateVector() const
{
    if (_stateVectorState == DIRTY)
    {
        UpdateStateVector();
    }

    return _stateVector;
}

const Coes& Orbit::GetCoes() const
{
    if (_coesState == DIRTY)
    {
        UpdateCoes();
    }

    return _coes;
}

void Orbit::UpdateStateVector() const
{
    ConvertCoes2StateVector(_coes, &_stateVector);   
    _stateVectorState = CLEAN;
}

void Orbit::UpdateCoes() const
{
    ConvertStateVector2Coes(_stateVector, &_coes);
    _coesState = CLEAN;
}

void Orbit::Propagate(double timeOfFlight)
{

}

void Orbit::ConvertStateVector2Coes(const StateVector& stateVector, Coes* coes)
{

}

void Orbit::ConvertCoes2StateVector(const Coes& coes, StateVector* stateVector)
{

}