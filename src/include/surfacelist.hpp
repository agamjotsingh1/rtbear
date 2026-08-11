#ifndef SURFACELIST_HPP 
#define SURFACELIST_HPP 

#include <vector>
#include <memory>
#include "vec3.hpp"
#include "surface.hpp"
#include "interval.hpp"

class SurfaceList: public Surface {
public:
        std::vector<std::shared_ptr<Surface>> surfaces;

        SurfaceList() {}
        SurfaceList(std::shared_ptr<Surface> surface) {
                push(surface);
        }

        void push(std::shared_ptr<Surface> surface) {
                surfaces.push_back(surface);
        }

        void clear() {
                surfaces.clear();
        }
        
        // check if any surface it hit
        // if hits, return the closest hitpoint
        bool hit(
                const Ray& ray,
                const Interval& interval,
                Hitpoint& hitpoint
        ) const override {
                double tmin = interval.min;
                double closest_t = interval.max;
                bool is_hit = false;
                Hitpoint temp_hitpoint;

                for(const std::shared_ptr<Surface>& surface : surfaces) {
                        if(surface->hit(ray, Interval(tmin, closest_t), temp_hitpoint)){
                                is_hit = true;
                                closest_t = temp_hitpoint.t;
                                hitpoint = temp_hitpoint;
                        }
                }

                return is_hit;
        }
};

#endif
