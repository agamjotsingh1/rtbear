#ifndef SURFACE_HPP
#define SURFACE_HPP

#include "vec3.hpp"
#include "ray.hpp"
#include "interval.hpp"

class Hitpoint {
public:
        Vec3 point;
        Vec3 normal;
        double t; // ray parameter
};

class Surface {
public:
        virtual ~Surface() {};
        virtual bool hit(const Ray& ray, const Interval& interval, Hitpoint& hitpoint) const = 0;
};

#endif
