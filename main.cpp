#include <iostream>
#include <cmath>
#include "vec3.hpp"
#include "ray.hpp"
#include "viewport.hpp"
#include "sphere.hpp"
#include "surface.hpp"
#include "surfacelist.hpp"

// display parameters
#define ASPECT_RATIO (16.0/9.0)
#define HEIGHT       (800)
#define WIDTH        ((HEIGHT) * (ASPECT_RATIO))

int main() {
        Vec3 cam_pos = Vec3(0, 0, 0);
        double focal_len = 2;
        double viewport_height = 2;
        double viewport_width = viewport_height * ASPECT_RATIO;

        SurfaceList surfacelist;
        // surfacelist.push(std::make_shared<Sphere>(Sphere(Vec3(-2, 0, -5), 0.5)));
        // surfacelist.push(std::make_shared<Sphere>(Sphere(Vec3(1, -1, -3.5), 1)));
        surfacelist.push(std::make_shared<Sphere>(Sphere(Vec3(0, 0, -5), 1)));
        surfacelist.push(std::make_shared<Sphere>(Sphere(Vec3(1, 0, -4), 1)));

        int samples_per_pixel = 50;
        int max_depth = 20;

        Viewport viewport(cam_pos, focal_len, viewport_height, viewport_width, HEIGHT, WIDTH, samples_per_pixel, max_depth);
        viewport.render(surfacelist);
        return 0;
}
