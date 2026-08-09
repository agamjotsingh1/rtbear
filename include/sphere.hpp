#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <cmath>
#include "vec3.hpp"
#include "surface.hpp"

class Sphere: public Surface {
public:
        Vec3 center;
        double radius;
        Sphere(): radius(0.0) {}
        Sphere(const Vec3& center, double radius): center(center), radius(radius) {}

        bool hit(const Ray& ray, double tmin, double tmax, Hitpoint& hitpoint) const override {
                // quadratic equation with coefficients a, -2b, c
                // at^2 + (-2b)t + c = 0
                double a = ray.direction.length_squared();
                double b = dot(center - ray.origin, ray.direction); 
                double c = (center - ray.origin).length_squared() - radius*radius;
                double discriminant = b*b - a*c;

                if(discriminant < 0) return false;

                double t = (b + std::sqrt(discriminant))/a;
                Vec3 point = ray.at(t);
                Vec3 normal = unitize(point - center);

                hitpoint.point = point;
                hitpoint.normal = normal;
                hitpoint.t = t;

                return true;
        }
};

#endif

