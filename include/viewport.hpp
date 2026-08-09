#ifndef VIEWPORT_HPP
#define VIEWPORT_HPP

#include <vec3.hpp>
#include <ray.hpp>

class Viewport {
public:
        Viewport(
                        const Vec3& cam_pos, double focal_len,
                        double viewport_height, double viewport_width,
                        int img_height, int img_width
                ):
                cam_pos(cam_pos) {
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
                return Ray(cam_pos, pixel_zero + (x*pixel_delta_x) + (y*pixel_delta_y) - cam_pos);
        }
private:
        Vec3 cam_pos;
        Vec3 pixel_zero; // first pixel at (0, 0) of the viewport
        Vec3 pixel_delta_x, pixel_delta_y;
};

#endif

