#ifndef _location_h_
#define _location_h_

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

private:
    int row_;
    int cell_;
};

#endif // _location_h_