#include <iostream>
#include "vec3.hpp"
#include "ray.hpp"
#include "viewport.hpp"
#include "sphere.hpp"

// display parameters
#define ASPECT_RATIO (16.0/9.0)
#define HEIGHT       (800)
#define WIDTH        ((HEIGHT) * (ASPECT_RATIO))

#define MAX_COLOR_VAL 255

// render image in PPM format
void render(int width, int height, Viewport& viewport, Sphere& sphere){
        std::cout << "P3\n" << width << " " << height << "\n";
        std::cout << MAX_COLOR_VAL << "\n";

        for(int i = 0; i < height; i++) {
                for(int j = 0; j < width; j++) {
                        Ray pixel_ray = viewport.pixel_ray(j, i);

                        double t = sphere.intersection(pixel_ray);
                        Vec3 normal = t >= 0
                                ? unitize(pixel_ray.at(t) - sphere.center)
                                : Vec3(1.0, 1.0, 1.0);

                        double r = 0.5*(normal.x + 1);
                        double g = 0.5*(normal.y + 1);
                        double b = 0.5*(normal.z + 1);

                        int ir = int(255.999 * r);
                        int ig = int(255.999 * g);
                        int ib = int(255.999 * b);

                        std::cout << ir << " " << ig << " " << ib << "\n";
                }
        }
}

int main() {
        Vec3 cam_pos = Vec3(0, 0, 0);
        double focal_len = 2;
        double viewport_height = 2;
        double viewport_width = viewport_height * ASPECT_RATIO;

        Vec3 sphere_center = Vec3(0, 0, -5);
        double sphere_radius = 1;
        Sphere sphere = Sphere(sphere_center, sphere_radius);

        Viewport viewport(cam_pos, focal_len, viewport_height, viewport_width, HEIGHT, WIDTH);
        render(WIDTH, HEIGHT, viewport, sphere);
        return 0;
}
