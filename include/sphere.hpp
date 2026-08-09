#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <vec3.hpp>

class Sphere {
public:
        Vec3 center;
        double radius;
        Sphere(): radius(0.0) {}
        Sphere(const Vec3& center, double radius): center(center), radius(radius) {}

        bool hit(const Ray& ray) const {
                // quadratic equation with coefficients a, b, c
                // at^2 + bt + c = 0
                double a = ray.direction.length_squared();
                double b = (-2.0) * dot(center - ray.origin, ray.direction); 
                double c = (center - ray.origin).length_squared() - radius*radius;
                double discriminant = b*b - 4*a*c;
                return (discriminant >= 0);
        }
};

#endif

