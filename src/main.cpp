#include <iostream>
#include <cmath>
#include "vec3.hpp"
#include "ray.hpp"
#include "color.hpp"
#include "viewport.hpp"
#include "sphere.hpp"
#include "surface.hpp"
#include "texture.hpp"
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
        CameraConfig camera = {.pos = Vec3(0, 0, 0), .view = Vec3(0, 0, -2)};
        // CameraConfig camera = {.pos = Vec3(-2, 2, -4), .view = Vec3(1, -1, 0)};
        ImageConfig image = {.height = HEIGHT, .width = WIDTH};
        RenderConfig config = {
                .viewport_height = 2.0,
                .viewport_width = 2.0 * ASPECT_RATIO,
                .samples_per_pixel = 300
        };

        // std::shared_ptr<Checkered> green_white_checkered = 
        //         std::make_shared<Checkered>(10.0, GREEN, WHITE);

        std::shared_ptr<Image> globe_tex = 
                std::make_shared<Image>("globe.jpg");

        std::shared_ptr<Image> moon_tex = 
                std::make_shared<Image>("moon.jpg");

        std::shared_ptr<Material> globe =
                std::make_shared<Lambertian>(globe_tex);

        std::shared_ptr<Material> moon =
                std::make_shared<Lambertian>(moon_tex);

        // std::shared_ptr<Material> sky =
        //         std::make_shared<LightSource>(SKY_BLUE, Color(1, 1, 1), );

        std::shared_ptr<Material> sky =
                std::make_shared<Lambertian>(VOID);

        std::shared_ptr<Material> sun =
                std::make_shared<LightSource>(YELLOW, WHITE, Vec3(-1.5, -1.5, -2));

        std::shared_ptr<Material> metal =
                std::make_shared<Metal>(Vec3(0.25, 0.25, 0.2), 0.0);

        std::shared_ptr<Material> fuzz_metal =
                std::make_shared<Metal>(Vec3(0.25, 0.25, 0.2), 0.1);

        std::shared_ptr<Material> ground =
                std::make_shared<Lambertian>(DARK_BROWN);

        std::shared_ptr<Material> water =
                std::make_shared<Dielectric>(1.333);

        std::shared_ptr<Material> bubble =
                std::make_shared<Dielectric>(1.0/1.333);

        SurfaceList world;
        world.push(std::make_shared<Sphere>(Sphere(Vec3(0, 0, -5), 1, metal)));
        world.push(std::make_shared<Sphere>(Sphere(Vec3(1, 1, -4), 0.5, globe)));
        world.push(std::make_shared<Sphere>(Sphere(Vec3(-1.2, 1, -3), 0.5, moon)));
        world.push(std::make_shared<Sphere>(Sphere(Vec3(0, -6, -4), 5, ground)));
        world.push(std::make_shared<Sphere>(Sphere(Vec3(0.3, 0.5, -2), 0.2, water)));
        world.push(std::make_shared<Sphere>(Sphere(Vec3(0.3, 0.5, -2), 0.18, bubble)));
        world.push(std::make_shared<Sphere>(Sphere(Vec3(2.5, 2.5, 0), 2, sun)));

        if(world.surfaces.size() > 32)
                world = SurfaceList(std::make_shared<BvhNode>(world));

        // keep sky seperate
        world.push(std::make_shared<Sphere>(Sphere(Vec3(0, 0, 0), 30, sky)));
        Viewport viewport(camera, image, config);
        viewport.render(world);
        return 0;
}
