#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "surface.hpp"
#include "util.hpp"

class Material {
public:
        virtual ~Material() {}

        virtual bool scatter(
                const Ray& ray,
                const Hitpoint& hitpoint,
                Vec3& attenuation,
                Ray& scattered_ray
        ) const {
                return false;
        }
};

class Lambertian: public Material {
public:
        Lambertian() {}
        Lambertian(Vec3 albedo, double prob): albedo(albedo), prob(prob) {}

        bool scatter(
                const Ray& ray,
                const Hitpoint& hitpoint,
                Vec3& attenuation,
                Ray& scattered_ray
        ) const override {
                double p = Interval::unipolar().clamp(prob);
                if(random_double(Interval::unipolar()) < p) return false;

                Vec3 scatter_direction = hitpoint.normal + Vec3::random();

                while(scatter_direction.is_zero()) {
                        scatter_direction = hitpoint.normal + Vec3::random();
                }

                scattered_ray = Ray(hitpoint.point, scatter_direction);
                attenuation = albedo;
                return true;
        }

private:
        Vec3 albedo;
        double prob;
};

class Metal: public Material {
public:
        Metal() {}
        Metal(Vec3 albedo): albedo(albedo) {}

        bool scatter(
                const Ray& ray,
                const Hitpoint& hitpoint,
                Vec3& attenuation,
                Ray& scattered_ray
        ) const override {
                Vec3 v = ray.direction.normalize_bipolar();
                Vec3 scatter_direction = v - 2*dot(v, hitpoint.normal)*hitpoint.normal;
                scattered_ray = Ray(hitpoint.point, scatter_direction);
                attenuation = albedo;
                return true;
        }

private:
        Vec3 albedo;
};

#endif
