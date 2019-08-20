#ifndef _io_constants_h_
#define _io_constants_h_

namespace io
{

//
// output character values (from ncurses)
//
enum Character : unsigned int
{
    WALL_NS = 4194424,
    WALL_EW = 4194417,
    WALL_NE = 4194413,
    WALL_SE = 4194412,
    WALL_SW = 4194411,
    WALL_NW = 4194410,
    WALL_NSE = 4194420,
    WALL_NSW = 4194421,
    WALL_NEW = 4194422,
    WALL_SEW = 4194423,
    WALL_NSEW = 4194414,
    BULLET = 4194430,
};

//
// input key values (from ncurses)
//
enum Key : unsigned int
{
    UP = 259,
    UP_RIGHT = 339,
    RIGHT = 261,
    DOWN_RIGHT = 338,
    DOWN = 258,
    DOWN_LEFT = 360,
    LEFT = 260,
    UP_LEFT = 262,
};

//
// colors (from ncurses)
//
const unsigned int bright = 8;
enum Color : unsigned int
{
    BLACK = 0,
    RED = 1,
    GREEN = 2,
    YELLOW = 3,
    BLUE = 4,
    MAGENTA = 5,
    CYAN = 6,
    WHITE = 7,
    BRIGHT_BLACK = bright + Color::BLACK,
    BRIGHT_RED = bright + Color::RED,
    BRIGHT_GREEN = bright + Color::GREEN,
    BRIGHT_YELLOW = bright + Color::YELLOW,
    BRIGHT_BLUE = bright + Color::BLUE,
    BRIGHT_MAGENTA = bright + Color::MAGENTA,
    BRIGHT_CYAN = bright + Color::CYAN,
    BRIGHT_WHITE = bright + Color::WHITE,
};

} // namespace io

#endif // _io_constants_h_