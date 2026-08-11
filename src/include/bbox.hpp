#ifndef BBOX_HPP
#define BBOX_HPP
#include "vec3.hpp"
#include "ray.hpp"
#include "interval.hpp"

// axis aligned bbox are used
class BBox {
public:
        Interval x, y, z;

        BBox() {}
        BBox(Interval x, Interval y, Interval z): x(x), y(y), z(z) {}
        BBox(Vec3 p1, Vec3 p2) {
                x = Interval(p1.x, p2.x).orient();
                y = Interval(p1.y, p2.y).orient();
                z = Interval(p1.z, p2.z).orient();
        }
        BBox(const BBox& b1, const BBox& b2) {
                x = Interval::merge(b1.x, b2.x);
                y = Interval::merge(b1.y, b2.y);
                z = Interval::merge(b1.z, b2.z);
        }

        bool hit(const Ray& ray, const Interval& interval) const {
                Interval t = interval;
                for(int axis = X; axis <= Z; axis++) {
                        Interval axis_t = axis_interval(ray, static_cast<Axis>(axis));
                        if(!t.overlap(axis_t)) return false;
                }
                return true;
        }

private:
        Interval axis_interval(const Ray& ray, Axis axis) const {
                // ray is given by p(t) = q + td with parameter as t
                double q = ray.origin.axis(axis);
                double d = ray.direction.axis(axis);
                double min_coord = Vec3(x.min, y.min, z.min).axis(axis);
                double max_coord = Vec3(x.max, y.max, z.max).axis(axis);
                double t0 = (min_coord - q)/d;
                double t1 = (max_coord - q)/d;
                return Interval(t0, t1).orient();
        }
};

#endif
