#ifndef __SNAKE_PUBLIC_H__
#define __SNAKE_PUBLIC_H__

#include <list>

namespace cwy_snake {
#define BOUNDARY_DISTANCE                    10
#define BOUNDARY_RIGHT_DISTANCE              300
#define SIDE_LENGTH                          20
#define GAME_WINDOW_WIDTH                    700
#define GAME_WINDOW_HEIGTH                   700
#define INIT_SNAKE_LENGTH                    3

enum dir { UP, DOWN, LEFT, RIGHT };

UINT32 boundary_height = 0, boundary_width = 0, score = 0;
bool is_standard_height = false, is_standard_width = false, is_game_begin = false;

struct Coordinate {
    Coordinate() {
        x = 0;
        y = 0;
    }
    Coordinate(UINT32 _x, UINT32 _y) {
        x = _x;
        y = _y;
    }
    UINT32 x;
    UINT32 y;
} coordinate;

struct Font {
    Font() {
        location.x = 0;
        location.y = 0;
        size_h = 0;
        size_w = 0;
        red = 0;
        green = 0;
        blue = 0;
    }
    Font(UINT32 _x, UINT32 _y, UINT32 _height, UINT32 _width, UINT32 _red, UINT32 _green, UINT32 _blue) {
        location.x = _x;
        location.y = _y;
        size_h = _height;
        size_w = _width;
        red = _red;
        green = _green;
        blue = _blue;
    }
    Coordinate location;
    UINT32 size_h;
    UINT32 size_w;
    UINT32 red;
    UINT32 green;
    UINT32 blue;
} font;

struct Bean {
    Bean() {
        location.x = 0;
        location.y = 0;
    }
    Bean(UINT32 _x, UINT32 _y) {
        location.x = _x;
        location.y = _y;
    }
    Coordinate location;
} bean;

struct Snake {
    Snake() {
        location.x = 0;
        location.y = 0;
    }
    Snake(UINT32 _x, UINT32 _y) {
        location.x = _x;
        location.y = _y;
    }
    Coordinate location;
} snake;

std::list<Snake> snake_list;

volatile dir direction = RIGHT;

}

#endif // !__SNAKE_PUBLIC_H__
