#include <cmath> // for sqrt
#include <vector>
#include "location.h"
#include "safe_math.h"


Location Location::apply_direction(Direction direction) const
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
        case Direction::none:
        default:
            return *this;
    }
}

std::vector<Location> Location::all_adjacent_locations() const
{
    std::vector<Location> result;
    for (int delta_row = -1; delta_row <= 1; delta_row++)
    {
        for (int delta_cell = -1; delta_cell <= 1; delta_cell++)
        {
            result.push_back(
                Location(SafeMath::Add(this->row(), delta_row), SafeMath::Add(this->cell(), delta_cell)));
        }
    }

    return result;
}

unsigned int Location::distance(Location that) const
{
    int delta_y = static_cast<int>(this->row()) - static_cast<int>(that.row());
    int delta_x = static_cast<int>(this->cell()) - static_cast<int>(that.cell());
    return static_cast<unsigned int>(sqrt(delta_y * delta_y + delta_x * delta_x));
}

std::vector<Location> Location::closer_adjacent_locations(Location target) const
{
    std::vector<Location> result = this->all_adjacent_locations();
    unsigned int distance = this->distance(target);
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

bool Location::is_adjacent(Location& that, bool& diagonal) const
{
    diagonal = false;
    if (*this == that)
    {
        return false;
    }

    int row_diff = std::abs(
        static_cast<int>(this->row()) - static_cast<int>(that.row()));
    int cell_diff = std::abs(
        static_cast<int>(this->cell()) - static_cast<int>(that.cell()));

    if (row_diff <= 1 && cell_diff <= 1)
    {
        // it is adjacent
        diagonal = (row_diff > 0 && cell_diff > 0);
        return true;
    }

    return false;
}