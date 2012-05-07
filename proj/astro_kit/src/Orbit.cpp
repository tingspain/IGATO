#include "Orbit.h"
#include "KeplersEquations.h"
#include "Transformation.h"

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
    ConvertCoes2StateVector(_coes, &_stateVector, _mu);   
    _stateVectorState = CLEAN;
}

void Orbit::UpdateCoes() const
{
    ConvertStateVector2Coes(_stateVector, &_coes, _mu);
    _coesState = CLEAN;
}

void Orbit::Propagate(double timeOfFlight)
{

}

void Orbit::ConvertStateVector2Coes(const StateVector& stateVector, Coes* coes, double mu)
{
    static Vector3 H, N;

    // useful references
    const Vector3& R = stateVector.position;
    const Vector3& V = stateVector.velocity;

    double r = R.length();
    double v = V.length();
    double rv = R.dot(V);

    Vector3::cross(R, V, &H);
    double h = H.length(); // specific angular momentum

    Vector3::cross(MATH_UNIT_VEC_K, H, &N); 
    double n = N.length();

    Vector3 Ecc = 1/mu * ((v*v - mu/r)*R - rv*V);
    double ecc = Ecc.length(); // eccentricity

    double a; // semimajor axis
    double p; // semiparameter
    if (ecc != 1.0) // non parabolic orbit
    {
        double xi = 0.5*v*v - mu/r; // specific mechanical energy
        a = -0.5*mu/xi;
        p = a*(1 - ecc*ecc);
    }
    else // parabolic orbit
    {
        a = MATH_INFINITY;
        p = h*h/mu;    
    }

    double incl = acos(H.z / h); // inclination

    double raan = acos(N.x / n); // right ascension of the ascending node
    if (N.y < 0)
    {
        raan = MATH_2_PI - raan;
    }

    double necc = N.dot(Ecc);
    double omega = acos(necc / n / ecc); // arguement of perigee
    if (Ecc.z < 0.0)
    {
        omega = MATH_2_PI - omega;
    }

    double eccr = Ecc.dot(R);
    double theta = acos(eccr / ecc / r); // true anomaly
    if (rv < 0.0)
    {
        theta = MATH_2_PI - theta;
    }

    coes->a = a;
    coes->ecc = ecc;
    coes->omega = omega;
    coes->incl = incl;
    coes->raan = raan;
    coes->theta = theta;
}

void Orbit::ConvertCoes2StateVector(const Coes& coes, StateVector* stateVector, double mu)
{
    static Vector3 R, V;

    double a = coes.a;
    double ecc = coes.ecc;
    double omega = coes.omega;
    double incl = coes.incl;
    double raan = coes.raan;
    double theta = coes.theta;

    double p = a*(1.0 - ecc*ecc);
    double h = sqrt(mu*p);

    double cosTheta = cos(theta);
    double sinTheta = sin(theta);

    // State vector in perifocal coordinate frame
    R.x = p*cosTheta / (1.0 + ecc*cosTheta);
    R.y = p*sinTheta / (1.0 + ecc*cosTheta);
    R.z = 0.0;

    V.x = -sqrt(mu/p)*sinTheta;
    V.y = sqrt(mu/p)*(ecc + cosTheta);
    V.z = 0.0;

    Perifocal2Inertial(R, incl, raan, omega, &stateVector->position);
    Perifocal2Inertial(V, incl, raan, omega, &stateVector->velocity);
}