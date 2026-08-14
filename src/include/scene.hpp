#ifndef SCENE_HPP 
#define SCENE_HPP
#include <utility>
#include "vec3.hpp"

struct CameraConfig {
        Vec3 pos;
        Vec3 view; // vector from camera to center of viewport
};

struct ImageConfig {
        int height;
        int width;
};

struct RenderConfig {
        double viewport_height = 2.0;
        double viewport_width  = 2.0;
        int samples_per_pixel = 50;
        int max_depth = 10;
};

#endif
