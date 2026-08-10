#include <iostream>
#include <cmath>
#include "vec3.hpp"
#include "ray.hpp"
#include "viewport.hpp"
#include "sphere.hpp"
#include "surface.hpp"
#include "surfacelist.hpp"
#include "material.hpp"
#include "scene.hpp"

// display parameters
#define ASPECT_RATIO (16.0/9.0)
#define HEIGHT       (800)
#define WIDTH        (static_cast<int>((HEIGHT) * (ASPECT_RATIO)))

int main() {
        // Camera camera = {.pos = Vec3(0, 0, 0), .view = Vec3(0, 0, -2)};
        Camera camera = {.pos = Vec3(-2, 2, -4), .view = Vec3(1, -1, 0)};
        Image image = {.height = HEIGHT, .width = WIDTH};
        RenderConfig config = {
                .viewport_height = 2.0,
                .viewport_width = 2.0 * ASPECT_RATIO
        };

        std::shared_ptr<Material> lambertian = std::make_shared<Lambertian>(Vec3(0.1, 0.9, 0.4), 0.1);
        std::shared_ptr<Material> metal = std::make_shared<Metal>(Vec3(0.25, 0.25, 0.2));
        std::shared_ptr<Material> ground = std::make_shared<Lambertian>(Vec3(0.1, 0.4, 0.4), 0.2);

        SurfaceList surfacelist;
        surfacelist.push(std::make_shared<Sphere>(Sphere(Vec3(0, 0, -5), 1, metal)));
        surfacelist.push(std::make_shared<Sphere>(Sphere(Vec3(1, 2, -4), 0.3, lambertian)));
        surfacelist.push(std::make_shared<Sphere>(Sphere(Vec3(0, -6, -4), 5, ground)));
        surfacelist.push(std::make_shared<Sphere>(Sphere(Vec3(1, 0, -3), 0.6, metal)));

        Viewport viewport(camera, image, config);
        viewport.render(surfacelist);
        return 0;
}
