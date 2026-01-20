#pragma once

#include <random>

#include "config.hpp"

std::mt19937 generator(cfg::seed);

inline float randf(float min, float max)
{  
    std::uniform_real_distribution<float> dist(min, max);
    return dist(generator);
}

inline float randf() 
{
    return randf(0.0f, 1.0f);
}