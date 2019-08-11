#ifndef _location_h_
#define _location_h_

#include <cmath> // for sqrt
#include <vector>
#include "direction.h"

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

    Location apply_direction(Direction direction) const
    {
        switch(direction)
        {
            case Direction::North:
                return Location(this->row()-1, this->cell());
            case Direction::NorthEast:
                return Location(this->row()-1, this->cell()+1);
            case Direction::East:
                return Location(this->row(), this->cell()+1);
            case Direction::SouthEast:
                return Location(this->row()+1, this->cell()+1);
            case Direction::South:
                return Location(this->row()+1, this->cell());
            case Direction::SouthWest:
                return Location(this->row()+1, this->cell()-1);
            case Direction::West:
                return Location(this->row(), this->cell()-1);
            case Direction::NorthWest:
                return Location(this->row()-1, this->cell()-1);
            default:
                return *this;
        }
    }

    virtual std::vector<Location> all_adjacent_locations()
    {
        std::vector<Location> result;
        for (int delta_row = -1; delta_row <= 1; delta_row++)
        {
            for (int delta_cell = -1; delta_cell <= 1; delta_cell++)
            {
                result.push_back(Location(this->row()+delta_row, this->cell()+delta_cell));
            }
        }

        return result;
    }

    int distance(Location that)
    {
        int delta_y = this->row() - that.row();
        int delta_x = this->cell() - that.cell();
        return static_cast<int>(sqrt(delta_y * delta_y + delta_x * delta_x));
    }

    std::vector<Location> closer_adjacent_locations(Location target)
    {
        std::vector<Location> result = this->all_adjacent_locations();
        int distance = this->distance(target);
        for (unsigned int i = 0; i < result.size(); i++)
        {
            if (result[i].distance(target) >= distance)
            {
                result.erase(result.begin()+i);
                i--;
            }
        }

        return result;
    }

private:
    int row_;
    int cell_;
};

#endif // _location_h_