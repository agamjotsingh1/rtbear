#ifndef INTERVAL_HPP
#define INTERVAL_HPP

#include <cmath>

#define MAX(a, b) (((a)>(b))?(a):(b))
#define MIN(a, b) (((a)<(b))?(a):(b))

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

        bool empty() const {
                return min > max;
        }

        Interval orient() const {
                double actual_min = MIN(min, max);
                double actual_max = MAX(min, max);

                return Interval(actual_min, actual_max);
        }

        Interval pad(double padding) const {
                return Interval(min - padding, max + padding);
        }

        bool overlap(const Interval& i) {
                min = MAX(min, i.min);
                max = MIN(max, i.max);
                return (!empty());
        }

        static Interval merge(const Interval& i1, const Interval& i2) {
                return Interval(MIN(i1.min, i2.min), MAX(i1.max, i2.max));
        }

        static Interval unipolar() { return Interval(0.0, 1.0); }
        static Interval bipolar()  { return Interval(-1.0, 1.0); }
};

#endif
