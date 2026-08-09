#ifndef VIEWPORT_HPP
#define VIEWPORT_HPP

#include "util.hpp"
#include "vec3.hpp"
#include "ray.hpp"
#include "surfacelist.hpp"

#define MAX_COLOR 255
using Color = Vec3;
#define BLACK (Color(0.0, 0.0, 0.0))
#define WHITE (Color(1.0, 1.0, 1.0))

class Viewport {
public:
        Viewport(
                        const Vec3& cam_pos, double focal_len,
                        double viewport_height, double viewport_width,
                        int img_height, int img_width, int samples_per_pixel, int max_depth
                ):
                cam_pos(cam_pos), samples_per_pixel(samples_per_pixel), max_depth(max_depth),
                img_height(img_height), img_width(img_width),
                viewport_height(viewport_height), viewport_width(viewport_width)
        {
                        // vectors u and v for positions of viewport in 3D
                        // -height because increase in y in viewport sense
                        // is decrease in actual coordinates (right handed system)
                        Vec3 delta_u = Vec3(viewport_width, 0, 0);
                        Vec3 delta_v = Vec3(0, -viewport_height, 0);
                        pixel_delta_x = delta_u / (img_width + 1);
                        pixel_delta_y = delta_v / (img_height + 1);

                        Vec3 top_left = cam_pos - Vec3(0, 0, focal_len) - delta_u/2 - delta_v/2;
                        pixel_zero = top_left + (pixel_delta_x + pixel_delta_y);
        }

        Ray pixel_ray(int x, int y) {
                double rand_offset_x = random_double(-0.5, 0.5);
                double rand_offset_y = random_double(-0.5, 0.5);

                Vec3 direction = pixel_zero + ((x + rand_offset_x)*pixel_delta_x)
                        + ((y + rand_offset_y)*pixel_delta_y) - cam_pos;

                return Ray(cam_pos, direction);
        }

        Color ray_color(const Ray& ray, SurfaceList& surfacelist, int depth) {
                if(depth <= 0) return BLACK;

                Hitpoint hitpoint;

                bool hit = surfacelist.hit(ray, Interval(EPSILON, INFINITY), hitpoint);

                if(hit) {
                        Vec3 reflected_direction =
                                Vec3::random_direction_on_sphere(hitpoint.normal);

                        Ray reflected_ray = Ray(hitpoint.point, reflected_direction);

                        return 0.5*(ray_color(reflected_ray, surfacelist, depth-1));
                }

                Color color = hit
                        ? colorize(hitpoint.normal)
                        : WHITE;

                return color;
        }

        void render(SurfaceList& surfacelist){
                init_img();
                Ray ray;

                for(int y = 0; y < img_height; y++) {
                        for(int x = 0; x < img_width; x++) {
                                ray = pixel_ray(x, y);
                                Color color = ray_color(ray, surfacelist, max_depth);

                                for(int i = 1; i < samples_per_pixel; i++) {
                                        ray = pixel_ray(x, y);
                                        color += ray_color(ray, surfacelist, max_depth);
                                }

                                commit_color(color/samples_per_pixel);
                        }
                }
        }

private:
        Vec3 cam_pos;
        int img_height, img_width;
        double viewport_height, viewport_width;
        Vec3 pixel_zero; // first pixel at (0, 0) of the viewport
        Vec3 pixel_delta_x, pixel_delta_y;
        int samples_per_pixel, max_depth;

        void init_img(){
                std::cout << "P3\n" << img_width << " " << img_height << "\n";
                std::cout << MAX_COLOR << "\n";
        }

        void commit_color(const Color& color) {
                Interval interval = Interval(0.0, 0.9999);
                double r = interval.clamp(color.x);
                double g = interval.clamp(color.y);
                double b = interval.clamp(color.z);

                int ir = int(MAX_COLOR * r);
                int ig = int(MAX_COLOR * g);
                int ib = int(MAX_COLOR * b);

                std::cout << ir << " " << ig << " " << ib << "\n";
        }
};

#endif

