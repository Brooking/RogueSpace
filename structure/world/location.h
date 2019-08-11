#ifndef _location_h_
#define _location_h_

#include <vector>
#include "direction.h"
#include "ithing.h"

class Floor;

class Location
{    
public:
    Location() : 
        row_(-1), cell_(-1)
    {}

    Location(int row, int cell) :
        row_(row), cell_(cell)
    {}

    int row() const { return this->row_; }
    int cell() const { return this->cell_; }

    bool operator== (const Location& that) const
    {
        return (this->row() == that.row() &&
                this->cell() == that.cell());
    }

    bool operator!= (const Location& that) const
    {
        return !(*this == that);
    }

    Location apply_direction(Direction direction) const;

    virtual std::vector<Location> all_adjacent_locations();

    int distance(Location that);

    std::vector<Location> closer_adjacent_locations(Location target);

    Location chose_random(std::vector<Location> locations, Floor& floor, iThing* thing);

private:
    int row_;
    int cell_;
};

#endif // _location_h_