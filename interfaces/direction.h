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
static std::map<int,Direction> KeyToDirection
{
    {static_cast<int>(io::Key::UP), Direction::North},
    {static_cast<int>(io::Key::UP_RIGHT), Direction::NorthEast},
    {static_cast<int>(io::Key::RIGHT), Direction::East},
    {static_cast<int>(io::Key::DOWN_RIGHT), Direction::SouthEast},
    {static_cast<int>(io::Key::DOWN), Direction::South},
    {static_cast<int>(io::Key::DOWN_LEFT), Direction::SouthWest},
    {static_cast<int>(io::Key::LEFT), Direction::West},
    {static_cast<int>(io::Key::UP_LEFT), Direction::NorthWest},
};

#endif // _direction_h_
