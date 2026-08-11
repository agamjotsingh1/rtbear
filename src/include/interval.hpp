#ifndef INTERVAL_HPP
#define INTERVAL_HPP

#include <cmath>

class Interval {
public:
        double min, max;
        Interval(): min(+INFINITY), max(-INFINITY) {} // empty interval
        Interval(double min, double max): min(min), max(max) {}

        bool contains(double a) const {
                return (a <= max) && (a >= min);
        }

        double clamp(double a) const {
                if(a < min) return min;
                if(a > max) return max;
                return a;
        }

        static Interval empty()    { return Interval(+INFINITY, -INFINITY); }
        static Interval universe() { return Interval(-INFINITY, +INFINITY); }
        static Interval unipolar() { return Interval(0.0, 1.0); }
        static Interval bipolar()  { return Interval(-1.0, 1.0); }
};

#endif
