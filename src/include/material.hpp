#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "vec3.hpp"
#include "color.hpp"
#include "surface.hpp"
#include "texture.hpp"
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

        virtual Color emit(
                const Ray& ray,
                const Hitpoint& hitpoint
        ) const {
                return BLACK;
        }
};

class Lambertian: public Material {
public:
        Lambertian() {}
        Lambertian(Vec3 albedo):
                texture(std::make_shared<Solid>(albedo)) {}

        Lambertian(std::shared_ptr<Texture> texture):
                texture(texture) {}

        bool scatter(
                const Ray& ray,
                const Hitpoint& hitpoint,
                Vec3& attenuation,
                Ray& scattered_ray
        ) const override {
                Vec3 scatter_direction = hitpoint.normal + Vec3::random();

                while(scatter_direction.is_zero()) {
                        scatter_direction = hitpoint.normal + Vec3::random();
                }

                scattered_ray = Ray(hitpoint.point, scatter_direction);
                attenuation = texture->color(
                        hitpoint.texture_u,
                        hitpoint.texture_v,
                        hitpoint.point
                );
                return true;
        }

private:
        std::shared_ptr<Texture> texture;
};

class Metal: public Material {
public:
        Metal() {}
        Metal(Vec3 albedo, double fuzz):
                albedo(albedo), fuzz(Interval::unipolar().clamp(fuzz)) {}

        bool scatter(
                const Ray& ray,
                const Hitpoint& hitpoint,
                Vec3& attenuation,
                Ray& scattered_ray
        ) const override {
                Vec3 v = ray.direction.unit();
                Vec3 scatter_direction = reflect(v, hitpoint.normal);
                Vec3 fuzzed_scatter_direction =
                        scatter_direction.unit() +
                        (fuzz * Vec3::random(Interval::bipolar()));

                scattered_ray = Ray(hitpoint.point, fuzzed_scatter_direction);
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
        Dielectric(double refractive_index):
                refractive_index(refractive_index) {}

        bool scatter(
                const Ray& ray,
                const Hitpoint& hitpoint,
                Vec3& attenuation,
                Ray& scattered_ray
        ) const override {
                Vec3 v = ray.direction.unit();
                Vec3 scatter_direction;

                double cos_theta = Interval::bipolar().clamp(
                                dot(-hitpoint.normal.unit(),
                                ray.direction.unit())
                        );

                double sin_theta = std::sqrt(1 - SQUARE(cos_theta));

                double relative_refractive_index = hitpoint.front_face
                        ? AIR_REFRACTIVE_INDEX/refractive_index
                        : refractive_index/AIR_REFRACTIVE_INDEX;

                bool total_internal_reflection =
                        (relative_refractive_index * sin_theta > 1);

                if(
                        total_internal_reflection ||
                        reflectance(cos_theta, relative_refractive_index) > random_double()
                ) {
                        // reflect
                        scatter_direction = reflect(v, hitpoint.normal);
                        scattered_ray = Ray(hitpoint.point, scatter_direction);
                }
                else {
                        // refract - change refractive index of ray
                        scatter_direction = refract(
                                v, hitpoint.normal,
                                relative_refractive_index
                        );

                        scattered_ray = Ray(hitpoint.point, scatter_direction);
                }

                attenuation = Vec3(1, 1, 1); // no attenuation
                return true;
        }

private:
        double refractive_index;

        // schlick's approximation for reflectance
        static double reflectance(double cosine, double refractive_index) {
                double r0 = (1 - refractive_index) / (1 + refractive_index);
                r0 = SQUARE(r0);
                return r0 + ((1 - r0)*std::pow(1-cosine, 5));
        }
};

class LightSource: public Material {
public:
        LightSource() {}
        LightSource(Color color, Color diffuse, Vec3 direction):
                color(color), diffuse(diffuse), direction(direction.unit()) {}

        Color emit(
                const Ray& ray,
                const Hitpoint& hitpoint
        ) const override {
                double lambert = dot(hitpoint.normal.unit(), direction);
                if(lambert < 0) lambert = 0;
                // by diffuse lighting equation
                return color*diffuse*lambert;
        }
private:
        Color color, diffuse;
        Vec3 direction;
};

#endif
