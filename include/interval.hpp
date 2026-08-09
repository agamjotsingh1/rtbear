#ifndef INTERVAL_HPP
#define INTERVAL_HPP

#include <cmath>

class Interval {
public:
        double min, max;
        Interval(): min(+INFINITY), max(-INFINITY) {} // empty interval
        Interval(double min, double max): min(min), max(max) {}

        double size() const {
                return (max - min);
        }

        bool contains(double a) const {
                return (a <= max) && (a >= min);
        }

        bool strict_contains(double a) const {
                return (a < max) && (a > min);
        }

        double clamp(double a) const {
                if(a < min) return min;
                if(a > max) return max;
                return a;
        }
};

#endif
