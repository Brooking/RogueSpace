#include "euclid.h"
#include <cmath> // for sqrt

unsigned int euclid::distance(Location location1, Location location2)
{
    int delta_y = location1.row() - location2.row();
    int delta_x = location1.cell() - location2.cell();
    return static_cast<int>(sqrt(delta_y * delta_y + delta_x * delta_x));
}

std::vector<Location> euclid::closer_adjacent_locations(Location target, Location location)
{
    std::vector<Location> result;
    int distance = euclid::distance(target, location);
    for (int delta_row = -1; delta_row <= 1; delta_row++)
    {
        for (int delta_cell = -1; delta_cell <= 1; delta_cell++)
        {
            Location candidate_location(location.row()+delta_row, location.cell()+delta_cell);
            int candidate_distance = euclid::distance(target, candidate_location);
            if (candidate_distance < distance)
            {
                result.push_back(candidate_location);
            }
        }
    }

    return result;
}