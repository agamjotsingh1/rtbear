#ifndef COLOR_HPP
#define COLOR_HPP
#include "vec3.hpp"

#define MIN_COLOR 0
#define MAX_COLOR 255

// rgb values (normalized)
using Color = Vec3;
#define RGB(r, g, b) (Color(\
        (static_cast<double>(r))/(MAX_COLOR-MIN_COLOR),\
        (static_cast<double>(g))/(MAX_COLOR-MIN_COLOR),\
        (static_cast<double>(b))/(MAX_COLOR-MIN_COLOR)))

#define BLACK           (RGB(0, 0, 0))
#define VOID            BLACK

#define WHITE           (RGB(255, 255, 255))
#define RED             (RGB(255, 0, 0))
#define GREEN           (RGB(0, 255, 0))
#define BLUE            (RGB(0, 0, 255))
#define YELLOW          (RGB(255, 255, 0))
#define CYAN            (RGB(0, 255, 255))
#define MAGENTA         (RGB(255, 0, 255))
#define LIGHT_RED       (RGB(255, 102, 102))
#define LIGHT_GREEN     (RGB(144, 238, 144))
#define LIGHT_BLUE      (RGB(173, 216, 230))
#define LIGHT_YELLOW    (RGB(255, 255, 153))
#define LIGHT_CYAN      (RGB(224, 255, 255))
#define LIGHT_MAGENTA   (RGB(255, 153, 255))
#define LIGHT_GRAY      (RGB(211, 211, 211))
#define LIGHT_PINK      (RGB(255, 182, 193))
#define LIGHT_PURPLE    (RGB(200, 162, 255))
#define LIGHT_ORANGE    (RGB(255, 200, 124))
#define LIGHT_BROWN     (RGB(205, 170, 125))
#define DARK_RED        (RGB(139, 0, 0))
#define DARK_GREEN      (RGB(0, 100, 0))
#define DARK_BLUE       (RGB(0, 0, 139))
#define BLUE_BLACK      (RGB(4, 7, 32))
#define DARK_YELLOW     (RGB(153, 153, 0))
#define DARK_CYAN       (RGB(0, 139, 139))
#define DARK_MAGENTA    (RGB(139, 0, 139))
#define DARK_GRAY       (RGB(64, 64, 64))
#define DARK_PURPLE     (RGB(75, 0, 130))
#define DARK_ORANGE     (RGB(255, 140, 0))
#define DARK_BROWN      (RGB(101, 67, 33))
#define GRAY            (RGB(128, 128, 128))
#define SILVER          (RGB(192, 192, 192))
#define GAINSBORO       (RGB(220, 220, 220))
#define DIM_GRAY        (RGB(105, 105, 105))
#define ORANGE          (RGB(255, 165, 0))
#define PURPLE          (RGB(128, 0, 128))
#define PINK            (RGB(255, 192, 203))
#define HOT_PINK        (RGB(255, 105, 180))
#define BROWN           (RGB(165, 42, 42))
#define GOLD             (RGB(255, 215, 0))
#define NAVY            (RGB(0, 0, 128))
#define TEAL            (RGB(0, 128, 128))
#define OLIVE           (RGB(128, 128, 0))
#define MAROON          (RGB(128, 0, 0))
#define INDIGO          (RGB(75, 0, 130))
#define VIOLET          (RGB(238, 130, 238))
#define TURQUOISE       (RGB(64, 224, 208))
#define CORAL           (RGB(255, 127, 80))
#define SALMON          (RGB(250, 128, 114))
#define KHAKI           (RGB(240, 230, 140))
#define BEIGE           (RGB(245, 245, 220))
#define IVORY           (RGB(255, 255, 240))
#define LAVENDER        (RGB(230, 230, 250))
#define MINT            (RGB(189, 252, 201))
#define CRIMSON         (RGB(220, 20, 60))
#define CHOCOLATE       (RGB(210, 105, 30))
#define SLATE_BLUE      (RGB(106, 90, 205))
#define STEEL_BLUE      (RGB(70, 130, 180))
#define SKY_BLUE        (RGB(135, 206, 235))
#define FOREST_GREEN    (RGB(34, 139, 34))
#define LIME            (RGB(0, 255, 0))
#define AQUAMARINE      (RGB(127, 255, 212))

#endif
