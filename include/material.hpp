#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "surface.hpp"

class Material {
public:
        virtual ~Material() {};

        virtual bool scatter(
                const Ray& ray,
                Hitpoint& hitpoint,
                Cattenuation,
                Ray& scattered_ray
        ) const {
                return false
        };
};

#endif
