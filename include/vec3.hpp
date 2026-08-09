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

        Vec3 operator-() const { return Vec3(-x, -y, -z); }

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

        Vec3 normalize() const {
                double len = length();
                if (len == 0) return Vec3(0, 0, 0);
                return Vec3(x / len, y / len, z / len);
        }

        double dot(const Vec3& v) const {
                return (x * v.x) + (y * v.y) + (z * v.z);
        }

        static Vec3 random() {
                return Vec3(random_double(), random_double(), random_double());
        }

        static Vec3 random(double min, double max) {
                return Vec3(random_double(min, max), random_double(min, max), random_double(min, max));
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

inline Vec3 unitize(const Vec3& v) {
        if(v.length() == 0) return Vec3(0, 0, 0);
        return v / (v.length());
}

// return the normalized vector in 0.0 to 1.0 instead of -1.0 to 1.0
inline Vec3 colorize(const Vec3& v) {
        return 0.5*(unitize(v) + Vec3(1, 1, 1));
}

inline double dot(const Vec3& u, const Vec3& v) {
        return (u.x * v.x) + (u.y * v.y) + (u.z * v.z);
}

#endif
