#ifndef UTIL_H
#define UTIL_H

#include <random>
#include "interval.hpp"

#define EPSILON (1e-5)
#define SQUARE(a) (a*a)

// get a random value between [0.0, 1.0)
inline double random_double() {
        static std::uniform_real_distribution<double> distribution(0.0, 1.0);
        static std::mt19937 generator;
        return distribution(generator);
}

inline double random_double(const Interval& interval) {
        return interval.min + (interval.max - interval.min)*random_double();
}

inline double with_prob(double p) {
        return (random_double(Interval::unipolar()) < p);
}

// returns gamma2 corrected rgb value
inline double gamma(double linear) {
        return std::sqrt(linear >= 0 ? linear: 0);
}

#define AIR_REFRACTIVE_INDEX (1.0)

#endif
