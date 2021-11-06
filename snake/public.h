#ifndef __SNAKE_PUBLIC_H__
#define __SNAKE_PUBLIC_H__

#include <list>

namespace cwy_snake {
const int WINDOW_WIDTH = 1024;              // 窗口宽度
const int WINDOW_HEIGHT = 768;              // 窗口高度
const int BOUNDARY_DISTANCE = 10;           // 游戏界面左（上、下）边界离窗口左（上、下）侧距离
const int BOUNDARY_RIGHT_DISTANCE = 260;    // 游戏界面右边界离窗口右侧距离
const int SIDE_LENGTH = 20;                 // 蛇一节的边长、豆子的直径
const int GAME_WINDOW_WIDTH = 700;          // 游戏窗口宽度
const int GAME_WINDOW_HEIGTH = 700;         // 游戏窗口高度
const int INIT_SNAKE_LENGTH = 3;            // 初始化蛇长度

enum class dir { // 蛇行进方向
    UP, DOWN, LEFT, RIGHT
};

UINT32 boundaryHeight{0};       // 标题栏高度
UINT32 boundaryWidth{0};        // 标题栏宽度
UINT32 score{0};                // 当前得分
bool isStandardHeight{false};
bool isStandardWidth{false};
bool isGameBegin{false};

struct Coordinate {
    Coordinate()
        : x_(0), y_(0)
    {
    }
    Coordinate(UINT32 x, UINT32 y)
        : x_(x), y_(y)
    {
    }
    UINT32 x_;
    UINT32 y_;
} coordinate;

struct Font {
    Font()
        : location_(0, 0), sizeHeight_(0), sizeWidth_(0), red_(0), green_(0), blue_(0)
    {
    }
    Font(UINT32 x, UINT32 y, UINT32 height, UINT32 width, UINT32 red, UINT32 green, UINT32 blue)
        : location_(x, y), sizeHeight_(height), sizeWidth_(width), red_(red), green_(green), blue_(blue)
    {
    }
    Coordinate location_;
    UINT32 sizeHeight_;
    UINT32 sizeWidth_;
    UINT32 red_;
    UINT32 green_;
    UINT32 blue_;
} font;

struct Bean {
    Bean()
        : location_(0, 0)
    {
    }
    Bean(UINT32 x, UINT32 y)
        : location_(x, y)
    {
    }
    Coordinate location_;
} bean;

struct Snake {
    Snake()
        : location_(0, 0)
    {
    }
    Snake(UINT32 x, UINT32 y)
        : location_(x, y)
    {
    }
    Coordinate location_;
} snake;

std::list<Snake> snake_list;

volatile dir direction = dir::RIGHT;

}

#endif // !__SNAKE_PUBLIC_H__
