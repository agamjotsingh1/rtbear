#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <cmath>
#include <memory>
#include "vec3.hpp"
#include "surface.hpp"
#include "interval.hpp"
#include "material.hpp"

class Sphere: public Surface {
public:
        Vec3 center;
        double radius;

        Sphere(): radius(0.0) {}
        Sphere(
                const Vec3& center,
                double radius,
                std::shared_ptr<Material> material
        ): center(center), radius(radius), material(material) {}

        bool hit(
                const Ray& ray,
                const Interval& interval,
                Hitpoint& hitpoint
        ) const override {
                // quadratic equation with coefficients a, -2b, c
                // at^2 + (-2b)t + c = 0
                double a = ray.direction.length_squared();
                double b = dot(center - ray.origin, ray.direction); 
                double c = (center - ray.origin).length_squared() - radius*radius;
                double discriminant = b*b - a*c;

                if(discriminant < 0) return false;

                double t = (b - std::sqrt(discriminant))/a;
                if(!interval.contains(t)) {
                        t = (b + std::sqrt(discriminant))/a;
                        if(!interval.contains(t)) return false;
                }

                Vec3 point = ray.at(t);
                Vec3 normal = (point - center)/radius;

                hitpoint.point = point;
                hitpoint.t = t;
                hitpoint.set_normal(ray, normal);
                hitpoint.material = material;

                return true;
        }

private:
        std::shared_ptr<Material> material;
};

#endif

