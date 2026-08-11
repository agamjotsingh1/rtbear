#include <iostream>
#include <cmath>
#include "vec3.hpp"
#include "ray.hpp"
#include "color.hpp"
#include "util.hpp"
#include "interval.hpp"
#include "viewport.hpp"
#include "sphere.hpp"
#include "surface.hpp"
#include "surfacelist.hpp"
#include "material.hpp"
#include "scene.hpp"

// display parameters
#define WIDTH        (1200)
#define HEIGHT       (675)
#define ASPECT_RATIO (static_cast<double>(WIDTH)/(HEIGHT))

#define PI           (3.1415926535897932385)
#define RADIANS(deg) ((deg) * PI / 180.0)

#define LOOKFROM     (Vec3(13, 2, 3))
#define LOOKAT       (Vec3(0, 0, 0))
#define VFOV         (20.0)
#define FOCUS_DIST   (10.0)

int main() {
        Vec3 view = FOCUS_DIST * (LOOKAT - LOOKFROM).normalize_bipolar();
        double viewport_height = 2.0 * std::tan(RADIANS(VFOV)/2.0) * FOCUS_DIST;

        Camera camera = {.pos = LOOKFROM, .view = view};
        Image image = {.height = HEIGHT, .width = WIDTH};
        RenderConfig config = {
                .viewport_height = viewport_height,
                .viewport_width = viewport_height * ASPECT_RATIO,
                .samples_per_pixel = 50,
                .max_depth = 10
        };

        SurfaceList surfacelist;

        // a ray that hits nothing returns VOID, so the sky is an enclosing
        // sphere that always absorbs and hands back its own colour
        std::shared_ptr<Material> sky =
                std::make_shared<Lambertian>(Vec3(1.0, 1.0, 1.0), LIGHT_BLUE, 1.0);
        surfacelist.push(std::make_shared<Sphere>(Sphere(Vec3(0, 0, 0), 4000, sky)));

        std::shared_ptr<Material> ground_material =
                std::make_shared<Lambertian>(Vec3(0.5, 0.5, 0.5), VOID, 0.0);
        surfacelist.push(std::make_shared<Sphere>(
                Sphere(Vec3(0, -1000, 0), 1000, ground_material)));

        for(int a = -11; a < 11; a++) {
                for(int b = -11; b < 11; b++) {
                        double choose_mat = random_double();
                        Vec3 center(
                                a + 0.9*random_double(),
                                0.2,
                                b + 0.9*random_double()
                        );

                        if((center - Vec3(4, 0.2, 0)).length() <= 0.9) continue;

                        std::shared_ptr<Material> sphere_material;

                        if(choose_mat < 0.8) {
                                // diffuse
                                Vec3 albedo = Vec3::random() * Vec3::random();
                                sphere_material =
                                        std::make_shared<Lambertian>(albedo, VOID, 0.0);
                        }
                        else if(choose_mat < 0.95) {
                                // metal
                                Vec3 albedo = Vec3::random(Interval(0.5, 1));
                                double fuzz = random_double(Interval(0, 0.5));
                                sphere_material =
                                        std::make_shared<Metal>(albedo, VOID, fuzz);
                        }
                        else {
                                // glass
                                sphere_material =
                                        std::make_shared<Dielectric>(VOID, 1.5);
                        }

                        surfacelist.push(std::make_shared<Sphere>(
                                Sphere(center, 0.2, sphere_material)));
                }
        }

        std::shared_ptr<Material> material1 =
                std::make_shared<Dielectric>(VOID, 1.5);
        surfacelist.push(std::make_shared<Sphere>(
                Sphere(Vec3(0, 1, 0), 1.0, material1)));

        std::shared_ptr<Material> material1_inner =
                std::make_shared<Dielectric>(VOID, 1/1.5);
        surfacelist.push(std::make_shared<Sphere>(
                Sphere(Vec3(0, 1, 0), 0.95, material1_inner)));

        std::shared_ptr<Material> material2 =
                std::make_shared<Lambertian>(Vec3(0.4, 0.2, 0.1), VOID, 0.0);
        surfacelist.push(std::make_shared<Sphere>(
                Sphere(Vec3(-4, 1, 0), 1.0, material2)));

        std::shared_ptr<Material> material3 =
                std::make_shared<Metal>(Vec3(0.7, 0.6, 0.5), VOID, 0.0);
        surfacelist.push(std::make_shared<Sphere>(
                Sphere(Vec3(4, 1, 0), 1.0, material3)));

        Viewport viewport(camera, image, config);
        viewport.render(surfacelist);
        return 0;
}
