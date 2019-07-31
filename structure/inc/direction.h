#ifndef _direction_h_
#define _direction_h_

#include "location.h"

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

Location apply_direction(Location location, Direction direction)
{
    switch(direction)
    {
        case Direction::North:
            return Location(location.row-1, location.cell);
        case Direction::NorthEast:
            return Location(location.row-1, location.cell+1);
        case Direction::East:
            return Location(location.row, location.cell+1);
        case Direction::SouthEast:
            return Location(location.row+1, location.cell+1);
        case Direction::South:
            return Location(location.row+1, location.cell);
        case Direction::SouthWest:
            return Location(location.row+1, location.cell-1);
        case Direction::West:
            return Location(location.row, location.cell-1);
        case Direction::NorthWest:
            return Location(location.row-1, location.cell-1);
        default:
            return location;
    }
}

#endif // _direction_h_
