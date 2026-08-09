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

        void set_normal(const Ray& ray, const Vec3& outward_normal) {
                // front face if the ray direction and outward normal point in different directions
                bool front_face = dot(ray.direction, outward_normal) < 0;

                // make it so that normal points always points against the ray direction
                normal = front_face ? outward_normal: -outward_normal;
        }
};

class Surface {
public:
        virtual ~Surface() {};
        virtual bool hit(const Ray& ray, const Interval& interval, Hitpoint& hitpoint) const = 0;
};

#endif
