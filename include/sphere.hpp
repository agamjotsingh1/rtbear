#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <cmath>
#include <vec3.hpp>

class Sphere {
public:
        Vec3 center;
        double radius;
        Sphere(): radius(0.0) {}
        Sphere(const Vec3& center, double radius): center(center), radius(radius) {}

        // returns -1.0 if no intersection exists
        // returns parameter of ray if it exists
        double intersection(const Ray& ray) const {
                // quadratic equation with coefficients a, -2b, c
                // at^2 + (-2b)t + c = 0
                double a = ray.direction.length_squared();
                double b = dot(center - ray.origin, ray.direction); 
                double c = (center - ray.origin).length_squared() - radius*radius;
                double discriminant = b*b - a*c;

                if(discriminant >= 0) {
                        return (b + std::sqrt(discriminant))/a;
                }

                return -1.0;
        }
};

#endif

