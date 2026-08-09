#ifndef COLOR_HPP
#define COLOR_HPP
#include "vec3.hpp"

#define MIN_COLOR 0
#define MAX_COLOR 255

// rgb values (normalized)
using Color = Vec3;
#define BLACK      (Color(0.0, 0.0, 0.0))
#define WHITE      (Color(1.0, 1.0, 1.0))
#define LIGHT_BLUE (Color(0.6, 0.8, 0.9))
#define LIGHT_RED  (Color(0.9, 0.5, 0.4))

#endif
