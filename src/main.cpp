#include <iostream>
#include <cmath>
#include "vec3.hpp"
#include "ray.hpp"
#include "color.hpp"
#include "viewport.hpp"
#include "sphere.hpp"
#include "surface.hpp"
#include "surfacelist.hpp"
#include "material.hpp"
#include "scene.hpp"
#include "bbox.hpp"
#include "bvh.hpp"

// display parameters
#define ASPECT_RATIO (16.0/9.0)
#define HEIGHT       (800)
#define WIDTH        (static_cast<int>((HEIGHT) * (ASPECT_RATIO)))

int main() {
        Camera camera = {.pos = Vec3(0, 0, 0), .view = Vec3(0, 0, -2)};
        // Camera camera = {.pos = Vec3(-2, 2, -4), .view = Vec3(1, -1, 0)};
        Image image = {.height = HEIGHT, .width = WIDTH};
        RenderConfig config = {
                .viewport_height = 2.0,
                .viewport_width = 2.0 * ASPECT_RATIO,
                .samples_per_pixel = 100
        };

        std::shared_ptr<Material> green_lambertian =
                std::make_shared<Lambertian>(Vec3(0.1, 0.9, 0.4), DARK_GREEN, 0.1);

        std::shared_ptr<Material> sky =
                std::make_shared<Lambertian>(Vec3(0.5, 0.5, 0.5), LIGHT_BLUE, 0.9);

        std::shared_ptr<Material> metal =
                std::make_shared<Metal>(Vec3(0.25, 0.25, 0.2), VOID, 0.0);

        std::shared_ptr<Material> fuzz_metal =
                std::make_shared<Metal>(Vec3(0.25, 0.25, 0.2), VOID, 0.1);

        std::shared_ptr<Material> ground =
                std::make_shared<Lambertian>(Vec3(1.0, 1.0, 1.0), DARK_BROWN, 1.0);

        std::shared_ptr<Material> water =
                std::make_shared<Dielectric>(VOID, 1.333);

        std::shared_ptr<Material> bubble =
                std::make_shared<Dielectric>(VOID, 1.0/1.333);

        SurfaceList world;
        world.push(std::make_shared<Sphere>(Sphere(Vec3(0, 0, -5), 1, metal)));
        world.push(std::make_shared<Sphere>(Sphere(Vec3(1, 1, -4), 0.5, green_lambertian)));
        world.push(std::make_shared<Sphere>(Sphere(Vec3(0, -6, -4), 5, ground)));
        world.push(std::make_shared<Sphere>(Sphere(Vec3(0.3, 0.5, -2), 0.2, water)));
        world.push(std::make_shared<Sphere>(Sphere(Vec3(0.3, 0.5, -2), 0.18, bubble)));

        world = SurfaceList(std::make_shared<BvhNode>(world));
        // keep sky seperate
        world.push(std::make_shared<Sphere>(Sphere(Vec3(0, 0, 0), 30, sky)));
        Viewport viewport(camera, image, config);
        viewport.render(world);
        return 0;
}
