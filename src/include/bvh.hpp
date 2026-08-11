#ifndef BVH_H
#define BVH_H

#include <algorithm>
#include "surface.hpp"
#include "surfacelist.hpp"
#include "bbox.hpp"

// makes a graph of bboxes 
// leaf nodes are actual surfaces
// each node itself is a virtual surface (bbox)
class BvhNode: public Surface {
public:
        BvhNode() {}
        BvhNode(SurfaceList& surfacelist): 
                BvhNode(surfacelist, 0, surfacelist.surfaces.size()) {}
        BvhNode(
                SurfaceList& surfacelist,
                size_t start, size_t end
        ) {
                Axis random_axis = static_cast<Axis>(random_int(Interval(X, Z)));

                auto comparator = [&random_axis](
                        const std::shared_ptr<Surface> a,
                        const std::shared_ptr<Surface> b
                ) {
                        return axis_comparator(a, b, random_axis);
                };

                size_t size = (end - start);
                switch(size) {
                        case 1:
                                left = surfacelist.surfaces[start];
                                right = nullptr;
                                break;
                        case 2:
                                left = surfacelist.surfaces[start];
                                right = surfacelist.surfaces[start+1];
                                break;
                        default:
                                std::sort(
                                        std::begin(surfacelist.surfaces) + start,
                                        std::begin(surfacelist.surfaces) + end,
                                        comparator
                                );

                                size_t mid = start + size/2;
                                left = std::make_shared<BvhNode>(surfacelist, start, mid);
                                right = std::make_shared<BvhNode>(surfacelist, mid, end);
                                break;
                }
                bbox = right ? BBox(left->bbox, right->bbox): left->bbox;
        }

        bool hit(
                const Ray& ray,
                const Interval& interval,
                Hitpoint& hitpoint
        ) const override {
                if(!bbox.hit(ray, interval)) return false;
                bool left_hit = left->hit(ray, interval, hitpoint);

                Interval right_interval =
                        Interval(interval.min, left_hit ? hitpoint.t: interval.max);

                bool right_hit = (right == nullptr)
                        ? false
                        : right->hit(ray, right_interval, hitpoint);

                return left_hit || right_hit;
        };


private:
        std::shared_ptr<Surface> left;
        std::shared_ptr<Surface> right;

        static bool axis_comparator(
                const std::shared_ptr<Surface> a,
                const std::shared_ptr<Surface> b,
                Axis axis
        ) {
                switch(axis) {
                        case X: return a->bbox.x.min < b->bbox.x.min;
                        case Y: return a->bbox.y.min < b->bbox.y.min;
                        case Z: return a->bbox.z.min < b->bbox.z.min;
                }

                return false;
        }
};

#endif
