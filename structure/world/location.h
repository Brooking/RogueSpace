#ifndef _location_h_
#define _location_h_

#include <vector>
#include <bits/stdc++.h>
#include "direction.h"
#include "ithing.h"

class Floor;


class Location
{    
public:
    // default location
    Location() : 
        row_(INT_MAX), cell_(INT_MAX)
    {}

    // create a location
    Location(unsigned int row, unsigned int cell) :
        row_(row), cell_(cell)
    {}

    // return the location's row
    unsigned int row() const { return this->row_; }

    // return the location's cell
    unsigned int cell() const { return this->cell_; }

    // equality operator ==
    bool operator== (const Location& that) const
    {
        return (this->row() == that.row() &&
                this->cell() == that.cell());
    }

    // inequality opertor !=
    bool operator!= (const Location& that) const
    {
        return !(*this == that);
    }

    // Note: all less/greater than operators on this class are artificial:
    // we are actually returning the row first, cell second ordering.

    // less than operator <
    bool operator< (const Location& that) const
    {
        if (this->row_ < that.row_)
        {
            return true;
        }
        else if (this->row_ == that.row_)
        {
            if (this->cell_ < that.cell_)
            {
                return true;
            }
        }

        return false;
    }

    // less than or equals operator <=
    bool operator<= (const Location& that) const
    {
        return (*this < that || *this == that);
    }

    // greater than >
    bool operator> (const Location& that) const
    {
        return !(*this <= that);
    }

    // greater than >=
    bool operator>= (const Location& that) const
    {
        return !(*this < that);
    }

    // return this location moved in the given direction
    Location apply_direction(Direction direction) const;

    // return all adjacent locations
    std::vector<Location> all_adjacent_locations();

    // return the distance between this location and another
    unsigned int distance(Location that);

    // return all adjacent locations that are closer to the target than the current
    std::vector<Location> closer_adjacent_locations(Location target);

    // given a list of locations, return a random one
    Location choose_random(std::vector<Location> locations, std::shared_ptr<Floor> floor, std::shared_ptr<iThing> thing);

private:
    // the row of the location
    unsigned int row_;

    // the cell of this location
    unsigned int cell_;
};

#endif // _location_h_