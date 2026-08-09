#include <iostream>
#include "vec3.hpp"
#include "ray.hpp"
#include "viewport.hpp"

// display parameters
#define ASPECT_RATIO (16.0/9.0)
#define HEIGHT       (800)
#define WIDTH        ((HEIGHT) * (ASPECT_RATIO))

#define MAX_COLOR_VAL 255

// render image in PPM format
void render(int width, int height, Viewport& viewport){
        std::cout << "P3\n" << width << " " << height << "\n";
        std::cout << MAX_COLOR_VAL << "\n";

        for(int i = 0; i < height; i++) {
                for(int j = 0; j < width; j++) {
                        Vec3 direction = unitize((viewport.pixel_ray(j, i)).direction);
                        double a = 0.5*(direction.y + 1.0);
                        double r = a;
                        double g = 0.0;
                        double b = 1-a;

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
        double viewport_height = 2, viewport_width = 2;

        Viewport viewport(cam_pos, focal_len, viewport_height, viewport_width, HEIGHT, WIDTH);
        render(WIDTH, HEIGHT, viewport);
        return 0;
}
