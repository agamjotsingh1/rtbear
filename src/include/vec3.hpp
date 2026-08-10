#ifndef VEC3_HPP
#define VEC3_HPP

#include <cmath>
#include "util.hpp"
#include "interval.hpp"

class Vec3 {
public:
        double x, y, z;

        Vec3() : x(0.0), y(0.0), z(0.0) {}
        Vec3(double x, double y, double z) : x(x), y(y), z(z) {}

        Vec3 operator-() const {
                return Vec3(-x, -y, -z);
        }

        Vec3& operator+=(const Vec3& v) {
                x += v.x; y += v.y; z += v.z;
                return *this;
        }

        Vec3& operator*=(double t) {
                x *= t; y *= t; z *= t;
                return *this;
        }

        Vec3& operator/=(double t) {
                return *this *= 1.0 / t;
        }

        bool is_zero() const {
                Interval interval = Interval(-EPSILON, EPSILON);
                return interval.contains(x) && interval.contains(y) && interval.contains(z); 
        }

        double length_squared() const {
                return x*x + y*y + z*z;
        }

        double length() const {
                return std::sqrt(length_squared());
        }

        Vec3 normalize_bipolar() const {
                double len = length();
                if (len == 0) return Vec3(0, 0, 0);
                return Vec3(x / len, y / len, z / len);
        }

        inline Vec3 normalize_unipolar() const {
                Vec3 bipolar = this->normalize_bipolar(); 
                return Vec3(0.5*(bipolar.x + 1), 0.5*(bipolar.y + 1), 0.5*(bipolar.z + 1));
        }

        static Vec3 random() {
                return Vec3(random_double(), random_double(), random_double());
        }

        static Vec3 random(const Interval& interval) {
                return Vec3(random_double(interval), random_double(interval), random_double(interval));
        }
};

inline Vec3 operator+(const Vec3& u, const Vec3& v) {
        return Vec3(u.x + v.x, u.y + v.y, u.z + v.z);
}

inline Vec3 operator-(const Vec3& u, const Vec3& v) {
        return Vec3(u.x - v.x, u.y - v.y, u.z - v.z);
}

inline Vec3 operator*(const Vec3& u, const Vec3& v) {
        return Vec3(u.x * v.x, u.y * v.y, u.z * v.z);
}

inline Vec3 operator*(double t, const Vec3& v) {
        return Vec3(t * v.x, t * v.y, t * v.z);
}

inline Vec3 operator*(const Vec3& v, double t) {
        return t * v;
}

inline Vec3 operator/(const Vec3& v, double t) {
        return (1.0 / t) * v;
}

inline double dot(const Vec3& u, const Vec3& v) {
        return (u.x * v.x) + (u.y * v.y) + (u.z * v.z);
}

inline Vec3 cross(const Vec3& u, const Vec3& v) {
        double x = u.y*v.z - u.z*v.y;
        double y = u.z*v.x - u.x*v.z;
        double z = u.x*v.y - v.x*u.y;
        return Vec3(x, y, z);
}

inline Vec3 reflect(const Vec3& v, const Vec3& normal) {
        return (v - 2*dot(v, normal)*normal);
}

// ref: https://physics.stackexchange.com/questions/435512/snells-law-in-vector-form
inline Vec3 refract(
        const Vec3& v,
        const Vec3& normal,
        double relative_refractive_index
) {
        Vec3 outward_normal = -(normal.normalize_bipolar());
        Vec3 unit_v = v.normalize_bipolar();

        double beta = 1 - SQUARE(dot(outward_normal, unit_v));
        double alpha = std::sqrt(1 - (SQUARE(relative_refractive_index) * beta));

        Vec3 normal_component = alpha * outward_normal;
        Vec3 off_normal_component = relative_refractive_index *
                (unit_v - (dot(unit_v, outward_normal)*outward_normal));

        return normal_component + off_normal_component;
}

#endif
