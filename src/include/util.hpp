#ifndef UTIL_H
#define UTIL_H

#include <random>
#include "interval.hpp"

#define EPSILON (1e-6)

// get a random value between [0.0, 1.0)
inline double random_double() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

inline double random_double(const Interval& interval) {
        return interval.min + (interval.max - interval.min)*random_double();
}

#endif
