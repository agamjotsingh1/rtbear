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
        ): center(center), radius(radius), material(material) {
                Vec3 r = Vec3(radius, radius, radius);
                bbox = BBox(center - r, center + r);

        }

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

                double sqrt_discriminant = std::sqrt(discriminant);
                double t = (b - sqrt_discriminant)/a;
                if(!interval.contains(t)) {
                        t = (b + sqrt_discriminant)/a;
                        if(!interval.contains(t)) return false;
                }

                Vec3 point = ray.at(t);
                Vec3 normal = (point - center)/radius;

                hitpoint.point = point;
                hitpoint.t = t;
                hitpoint.set_normal(ray, normal);
                hitpoint.material = material;
                get_uv(normal, hitpoint.texture_u, hitpoint.texture_v);
                return true;
        }

private:
        std::shared_ptr<Material> material;

        void get_uv(const Vec3& p, double& u, double& v) const {
                // theta = angle with positive y-axis
                double dist = std::sqrt(SQUARE(p.x) + SQUARE(p.z));
                double theta = std::abs(std::atan2(dist, p.y));
                if(std::isnan(theta)) theta = PI/2;
                else if(theta < 0) theta = -theta;

                v = theta/PI;

                // phi = angle with positive x-axis
                double phi = std::atan2(p.z, p.x);
                if(std::isnan(phi)) phi = 0.0;
                else if(phi < 0) phi = 2*PI + phi;

                u = phi/(2*PI);
        }
};

#endif

