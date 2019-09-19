#include <queue>
#include "dijkstra.h"
#include "pathfinder.h"

std::vector<Location> Pathfinder::find_path(Location from, Location to)
{
    std::vector<Location> result;
    if (from == to)
    {
        // already there
        return result;
    }

    // flood fill distances for floor (todo: save this for reuse by all actors)
    std::vector<std::vector<unsigned int>> distance(
        this->map_->height(), 
        std::vector<unsigned int>(
            this->map_->width(),
            0
        ));
    Dijkstra::fill(distance, this->map_, from, to);
    if ( distance[from.row()][from.cell()] == 0)
    {
        // no path
        return result;
    }

    // walk along the shortest path to the source
    walk_back(result, distance, from);
    return result;
}

void Pathfinder::walk_back(
    std::vector<Location>& result,
    std::vector<std::vector<unsigned int>>& distance,
    Location location)
{
    unsigned int current_distance = distance[location.row()][location.cell()];
    while (current_distance > 0)
    {
        Location next_location;
        // check each of the neighbors for the next step
        for (unsigned int i = 0; i < 8; i++)
        {
            unsigned int row = location.row() + Dijkstra::Neighbors[i].first;
            unsigned int cell = location.cell() + Dijkstra::Neighbors[i].second;
            if (row >= static_cast<unsigned int>(distance.size()) || 
                cell >= static_cast<unsigned int>(distance[0].size()))
            {
                // off the map
                continue;
            }
            unsigned int new_distance = distance[row][cell];
            if (new_distance == INT_MAX)
            {
                // wall
                continue;
            }

            if (new_distance < current_distance)
            {
                // found a next step
                assert(new_distance == current_distance - 1);
                next_location = Location(row, cell);
                break;
            }
        }

        if (next_location == Location())
        {
            // could not find a next step
            return;
        }

        location = next_location;
        result.push_back(location);
        current_distance = distance[location.row()][location.cell()];
    }
}                           
