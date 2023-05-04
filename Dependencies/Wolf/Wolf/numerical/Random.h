#pragma once
#ifndef WOLF_RANDOM_H
#define WOLF_RANDOM_H
#include <stdint.h>
#include <random>

namespace Wolf
{
    namespace Numerical
    {
        
        namespace Random
        {
            class RandomFloat
            {
            
                public:
                    RandomFloat(uint32_t seed=0);
                    float unit();
                    float range(float min, float max);
                    float signed_unit();
    
                private:
                    std::uniform_real_distribution<float> _distribution;
                    std::mt19937 _generator;
                    uint32_t _seed;
            };
    
            class RandomDouble
            {
            
                public:
                    RandomDouble(uint32_t seed=0);
                    double unit();
                    double range(double min, double max);
                    double signed_unit();
    
                private:
                    std::uniform_real_distribution<double> _distribution;
                    std::mt19937 _generator;
                    uint32_t _seed;
            };
    
            // Generic use static instances
            static thread_local RandomFloat RandomFloatGenerator;
            static thread_local RandomDouble RandomDoubleGenerator;
    
            // Acess to float methods
            static float unit_f() { return RandomFloatGenerator.unit(); }
            static float signed_unit_f() { return RandomFloatGenerator.signed_unit(); }
            static float range_f(float min, float max) { return RandomFloatGenerator.range(min, max); }
    
            // Acess to double methods
            static double unit_d() { return RandomDoubleGenerator.unit(); }
            static double signed_unit_d() { return RandomDoubleGenerator.signed_unit(); }
            static double range_d(double min, double max) { return RandomDoubleGenerator.range(min, max); }
        }
    }
}


#endif