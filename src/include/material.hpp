#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "surface.hpp"
#include "util.hpp"

class Material {
public:
        Color color;

        Material() {}
        Material(Color color): color(color) {}

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
        Lambertian(Vec3 albedo, Color color, double prob):
                Material(color), albedo(albedo), prob(prob) {}

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

                scattered_ray = Ray(
                        hitpoint.point,
                        scatter_direction,
                        ray.refractive_index
                );
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
        Metal(Vec3 albedo, Color color, double fuzz):
                Material(color), albedo(albedo), fuzz(Interval::unipolar().clamp(fuzz)) {}

        bool scatter(
                const Ray& ray,
                const Hitpoint& hitpoint,
                Vec3& attenuation,
                Ray& scattered_ray
        ) const override {
                Vec3 v = ray.direction.normalize_bipolar();
                Vec3 scatter_direction = reflect(v, hitpoint.normal);
                Vec3 fuzzed_scatter_direction =
                        scatter_direction.normalize_bipolar() +
                        (fuzz * Vec3::random(Interval::bipolar()));

                scattered_ray = Ray(
                        hitpoint.point,
                        fuzzed_scatter_direction,
                        ray.refractive_index
                );

                attenuation = albedo;
                return true;
        }

private:
        Vec3 albedo;
        double fuzz;
};

class Dielectric: public Material {
public:
        Dielectric() {}
        Dielectric(Color color, double refractive_index):
                Material(color), refractive_index(refractive_index) {}

        bool scatter(
                const Ray& ray,
                const Hitpoint& hitpoint,
                Vec3& attenuation,
                Ray& scattered_ray
        ) const override {
                Vec3 v = ray.direction.normalize_bipolar();
                Vec3 scatter_direction;

                if(with_prob(0.5)) {
                        // reflect
                        scatter_direction = reflect(v, hitpoint.normal);
                        scattered_ray = Ray(
                                hitpoint.point,
                                scatter_direction,
                                ray.refractive_index
                        );
                }
                else {
                        // refract - change refractive index of ray
                        double relative_refractive_index = hitpoint.front_face
                                ? AIR_REFRACTIVE_INDEX/refractive_index
                                : refractive_index/AIR_REFRACTIVE_INDEX;

                        scatter_direction = refract(
                                v, hitpoint.normal,
                                relative_refractive_index
                        );

                        scattered_ray = Ray(
                                hitpoint.point,
                                scatter_direction,
                                hitpoint.front_face ? refractive_index: AIR_REFRACTIVE_INDEX
                        );
                }

                attenuation = Vec3(1, 1, 1); // no attenuation
                return true;
        }

private:
        double refractive_index;
};

#endif
