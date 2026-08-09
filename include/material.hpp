#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "surface.hpp"
#include "util.hpp"

class Material {
public:
        virtual ~Material() {}

        virtual bool scatter(
                const Ray& ray,
                Hitpoint& hitpoint,
                Vec3& attenuation,
                Ray& scattered_ray
        ) const {
                return false;
        }
};

class Lambertian: public Material {
public:
        Lambertian() {}
        Lambertian(Vec3 albedo, double p): albedo(albedo), p(p) {}

        virtual bool scatter(
                const Ray& ray,
                Hitpoint& hitpoint,
                Vec3& attenuation,
                Ray& scattered_ray
        ) const override {
                if(random_double(0.0, 1.0) < p) return false;

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
        double p;
};

class Metal: public Material {
public:
        Metal() {}
        Metal(Vec3 albedo): albedo(albedo) {}

        virtual bool scatter(
                const Ray& ray,
                Hitpoint& hitpoint,
                Vec3& attenuation,
                Ray& scattered_ray
        ) const override {
                Vec3 v = unitize(ray.direction);
                Vec3 scatter_direction = v - 2*dot(v, hitpoint.normal)*hitpoint.normal;
                scattered_ray = Ray(hitpoint.point, scatter_direction);
                attenuation = albedo;
                return true;
        }

private:
        Vec3 albedo;
};

#endif
