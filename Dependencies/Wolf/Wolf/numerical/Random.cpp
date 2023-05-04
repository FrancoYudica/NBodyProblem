#include "Random.h"

using namespace Wolf::Numerical::Random;


RandomFloat::RandomFloat(uint32_t seed)
{
    _seed = seed;
    _distribution = std::uniform_real_distribution<float>(0.0f, 1.0f);
    _generator = std::mt19937(seed);
}

float RandomFloat::unit()
{
    return _distribution(_generator);
}

float RandomFloat::signed_unit()
{
    return _distribution(_generator) * 2.0f - 1.0f;
}

float RandomFloat::range(float min, float max)
{
    return min + _distribution(_generator) * (max - min);
}

RandomDouble::RandomDouble(uint32_t seed)
{
    _seed = seed;
    _distribution = std::uniform_real_distribution<double>(0.0f, 1.0f);
    _generator = std::mt19937(seed);
}

double RandomDouble::unit()
{
    return _distribution(_generator);
}

double RandomDouble::signed_unit()
{
    return _distribution(_generator) * 2.0f - 1.0f;
}

double RandomDouble::range(double min, double max)
{
    return min + _distribution(_generator) * (max - min);
}

/*
float Random::unit_f()
{
    static thread_local std::uniform_real_distribution<float> distrubution(0.0, 1.0);
    static thread_local std::mt19937 generator;
    return distrubution(generator);
}
float Random::range(float min, float max)
{
    return min + unit_f() * (max - min);
}

float Random::signed_unit_f()
{
    return unit_f() * 2.0f - 1.0f;
}


// FLOAT IMPLEMENTATIONS
float Random::unit_f()
{
    static thread_local std::uniform_real_distribution<float> distrubution(0.0, 1.0);
    static thread_local std::mt19937 generator;
    return distrubution(generator);
}
float Random::range(float min, float max)
{
    return min + unit_f() * (max - min);
}

float Random::signed_unit_f()
{
    return unit_f() * 2.0f - 1.0f;
}

// DOUBLE IMPLEMENTATIONS
double Random::unit_d()
{
    static thread_local std::uniform_real_distribution<double> distrubution(0.0, 1.0);
    static thread_local std::mt19937 generator;
    return distrubution(generator);
}
double Random::range(double min, double max)
{
    return min + unit_d() * (max - min);
}

double Random::signed_unit_d()
{
    return unit_d() * 2.0f - 1.0f;
}

int32_t Random::range(int32_t min, int32_t max)
{
    float random_float = Random::unit_f();
    return static_cast<int32_t>(min + random_float * (max - min));
}
*/


