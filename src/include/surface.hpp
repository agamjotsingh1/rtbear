#ifndef SURFACE_HPP
#define SURFACE_HPP

#include <memory>
#include "vec3.hpp"
#include "ray.hpp"
#include "interval.hpp"
#include "bbox.hpp"

// defined later in material.hpp
class Material;

class Hitpoint {
public:
        Vec3 point;
        Vec3 normal;
        bool front_face;
        double t; // ray parameter

        double texture_u, texture_v;

        // shared ptr because of forward declaration
        // and multiple hitpoints may refer to material
        std::shared_ptr<Material> material;

        void set_normal(const Ray& ray, const Vec3& outward_normal) {
                // front face if the ray direction and outward normal point in different directions
                front_face = dot(ray.direction, outward_normal) < 0;

                // make it so that normal points always points against the ray direction
                normal = front_face ? outward_normal: -outward_normal;
        }
};

class Surface {
public:
        BBox bbox;

        virtual ~Surface() {};
        virtual bool hit(
                const Ray& ray,
                const Interval& interval,
                Hitpoint& hitpoint
        ) const {
                return false;
        };
};

#endif
