#ifndef _direction_h_
#define _direction_h_

#include <map>
#include "io_constants.h"

enum class Direction
{
    none = 0,
    North,
    NorthEast,
    East,
    SouthEast,
    South,
    SouthWest,
    West,
    NorthWest
};

// maps key inputs into useful directions
static std::map<unsigned int,Direction> KeyToDirection
{
    {io::Key::UP, Direction::North},
    {io::Key::UP_RIGHT, Direction::NorthEast},
    {io::Key::RIGHT, Direction::East},
    {io::Key::DOWN_RIGHT, Direction::SouthEast},
    {io::Key::DOWN, Direction::South},
    {io::Key::DOWN_LEFT, Direction::SouthWest},
    {io::Key::LEFT, Direction::West},
    {io::Key::UP_LEFT, Direction::NorthWest},
};

#endif // _direction_h_
