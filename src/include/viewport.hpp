#ifndef VIEWPORT_HPP
#define VIEWPORT_HPP

#include "vec3.hpp"
#include "ray.hpp"
#include "color.hpp"
#include "util.hpp"
#include "material.hpp"
#include "surfacelist.hpp"
#include "scene.hpp"

#define WORLD_UP    (Vec3(0, 1, 0))
#define WORLD_RIGHT (Vec3(1, 0, 0))

class Viewport {
public:
        Viewport(
                const Camera camera,
                const Image image,
                const RenderConfig config
        ):
                camera(camera),
                config(config),
                image(image)
        {
                Vec3 view_normal = camera.view.normalize_bipolar();
                Vec3 right = cross(view_normal, WORLD_UP).normalize_bipolar();

                if(right.is_zero()) {
                        right = cross(view_normal, WORLD_RIGHT).normalize_bipolar();
                }

                Vec3 down = cross(view_normal, right).normalize_bipolar();

                // vectors u and v for positions of viewport in 3D
                // -height because increase in y in viewport sense
                // is decrease in actual coordinates (right handed system)
                Vec3 delta_x = (config.viewport_width) * right;
                Vec3 delta_y = (config.viewport_height) * down;
                pixel_delta_x = delta_x / (image.width + 1);
                pixel_delta_y = delta_y / (image.height + 1);

                Vec3 top_left = (camera.pos + camera.view) - (0.5*delta_x) - (0.5*delta_y);
                pixel_zero = top_left + (pixel_delta_x + pixel_delta_y);
        }

        Ray pixel_ray(int x, int y) {
                double rand_offset_x = random_double(Interval(-0.5, 0.5));
                double rand_offset_y = random_double(Interval(-0.5, 0.5));

                Vec3 direction = pixel_zero + ((x + rand_offset_x)*pixel_delta_x)
                        + ((y + rand_offset_y)*pixel_delta_y) - camera.pos;

                return Ray(camera.pos, direction);
        }

        Color ray_color(const Ray& ray, SurfaceList& surfacelist, int depth) {
                if(depth <= 0) return BLACK;

                Hitpoint hitpoint;

                bool hit = surfacelist.hit(ray, Interval(EPSILON, INFINITY), hitpoint);

                if(hit) {
                        Ray scattered_ray;
                        Vec3 attenuation;

                        if((hitpoint.material)->scatter(
                                ray, hitpoint,
                                attenuation, scattered_ray
                        ))
                                return attenuation * ray_color(
                                        scattered_ray, surfacelist, depth-1);
                        else
                                return (hitpoint.material)->color;
                }

                return VOID;
        }

        void render(SurfaceList& surfacelist){
                init_img();
                Ray ray;

                for(int y = 0; y < image.height; y++) {
                        for(int x = 0; x < image.width; x++) {
                                ray = pixel_ray(x, y);
                                Color color = ray_color(ray, surfacelist, config.max_depth);

                                for(int i = 1; i < config.samples_per_pixel; i++) {
                                        ray = pixel_ray(x, y);
                                        color += ray_color(ray, surfacelist, config.max_depth);
                                }

                                commit_color(color/config.samples_per_pixel);
                        }
                }
        }

private:
        Camera camera;
        Image image;
        RenderConfig config;
        Vec3 pixel_zero; // first pixel at (0, 0) of the viewport
        Vec3 pixel_delta_x, pixel_delta_y;

        void init_img(){
                // P3 PPM format
                std::cout << "P3\n" << image.width << " " << image.height << "\n";
                std::cout << MAX_COLOR << "\n";
        }

        void commit_color(const Color& color) {
                Interval interval = Interval(0.0, 1.0 - EPSILON);
                double r = gamma(interval.clamp(color.x));
                double g = gamma(interval.clamp(color.y));
                double b = gamma(interval.clamp(color.z));

                int ir = int(MAX_COLOR * r);
                int ig = int(MAX_COLOR * g);
                int ib = int(MAX_COLOR * b);

                std::cout << ir << " " << ig << " " << ib << "\n";
        }
};

#endif

