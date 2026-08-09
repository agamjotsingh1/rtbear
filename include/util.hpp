#ifndef UTIL_H
#define UTIL_H

#include <random>
#define EPSILON (1e-6)

// get a random value between [0.0, 1.0)
inline double random_double() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

inline double random_double(double min, double max) {
        return min + (max - min)*random_double();
}

#endif
