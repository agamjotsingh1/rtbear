#ifndef UTIL_H
#define UTIL_H

enum Axis { X, Y, Z };

#include <cstdint>
#include <random>
#include "interval.hpp"

#define EPSILON (1e-5)
#define SQUARE(a) (a*a)

// get a random value between [0.0, 1.0)
inline double random_double() {
        static uint64_t s = 0x9E3779B97F4A7C15ull;
        s ^= s >> 12; s ^= s << 25; s ^= s >> 27;
        return (s * 0x2545F4914F6CDD1Dull >> 11) * 0x1.0p-53;
}

// inline double random_double() {
//         static std::uniform_real_distribution<double> distribution(0.0, 1.0);
//         static std::mt19937 generator;
//         return distribution(generator);
// }

inline double random_double(const Interval& interval) {
        return interval.min + (interval.max - interval.min)*random_double();
}

inline int random_int(const Interval& interval) {
        return static_cast<int>(random_double(interval.pad(-EPSILON)));

//         static std::uniform_int_distribution<int> distribution(
//                 static_cast<int>(interval.min),
//                 static_cast<int>(interval.max)
//         );
//         static std::mt19937 generator;
//         return distribution(generator);
}

// returns gamma2 corrected rgb value
inline double gamma(double linear) {
        return std::sqrt(linear >= 0 ? linear: 0);
}

#define AIR_REFRACTIVE_INDEX (1.0)

#endif
