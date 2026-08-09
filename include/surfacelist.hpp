#ifndef SURFACELIST_HPP 
#define SURFACELIST_HPP 

#include <vector>
#include <memory>
#include "vec3.hpp"
#include "surface.hpp"

class SurfaceList: public Surface {
public:
        std::vector<std::shared_ptr<Surface>> world;
        SurfaceList() {}
        SurfaceList(std::shared_ptr<Surface> surface) {
                push(surface);
        }

        void push(std::shared_ptr<Surface> surface) {
                world.push_back(surface);
        }

        void clear() {
                world.clear();
        }
        
        bool hit(const Ray& ray, double tmin, double tmax, Hitpoint& hitpoint) const override {
                double closest_t = tmax;
                bool is_hit = false;
                Hitpoint temp_hitpoint;

                for(const std::shared_ptr<Surface>& surface : world) {
                        if(surface->hit(ray, tmin, closest_t, temp_hitpoint)){
                                is_hit = true;
                                closest_t = temp_hitpoint.t;
                                hitpoint = temp_hitpoint;
                        }
                }

                return is_hit;
        }
};

#endif


