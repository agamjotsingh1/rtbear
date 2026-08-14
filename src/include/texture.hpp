#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "vec3.hpp"
#include "color.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

class Texture {
public:
        virtual ~Texture() {}

        virtual Color color(double u, double v, const Vec3& point) const {
                return BLACK;
        }
};

class Solid: public Texture {
public:
        Solid() {}
        Solid(Color color): solid_color(color) {}

        Color color(double u, double v, const Vec3& point) const override {
                return solid_color;
        }
private:
        Color solid_color;
};

class Checkered: public Texture {
public:
        Checkered() {}
        Checkered(double grain, Color c1, Color c2):
                grain(grain), c1(c1), c2(c2) {}

        Color color(double u, double v, const Vec3& point) const override {
                int grain_u = std::floor(grain * u);
                int grain_v = std::floor(grain * v);
                if((grain_u + grain_v)%2 == 0) return c1;
                else return c2;
        }
private:
        double grain;
        Color c1, c2;
};

class Image: public Texture {
public:
        ~Image() override {
                if(data) {
                        stbi_image_free(data);
                }
        }

        Image(const Image&) = delete;
        Image& operator=(const Image&) = delete;

        Image(const char* path) {
                int channels;

                // force 3 channels (R, G, B)
                data = stbi_load(path, &width, &height, &channels, 3);

                if(!data) {
                        throw std::runtime_error(std::string("Failed to load image: ") + path);
                }
        }

        Color color(double u, double v, const Vec3& point) const override {
                int grain_u = std::floor(width * Interval(0, 1).clamp(u));
                int grain_v = std::floor(height * Interval(0, 1).clamp(v));
                int pixel_idx = (grain_u + width*grain_v)*3;
                int r = data[pixel_idx];
                int g = data[pixel_idx + 1];
                int b = data[pixel_idx + 2];
                return RGB(r, g, b);
        }
private:
        unsigned char* data = nullptr;
        int width = 0, height = 0;
};

#endif
