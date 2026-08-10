#ifndef RAY_HPP
#define RAY_HPP

#include <vec3.hpp>

class Ray {
public:
        Vec3 origin;
        Vec3 direction;
        double refractive_index;

        Ray() {}
        Ray(
                const Vec3& origin,
                const Vec3& direction,
                double refractive_index
        ): origin(origin), direction(direction),
        refractive_index(refractive_index) {}

        Vec3 at(double t) const {
                return origin + (t * direction);
        }
};

#endif
