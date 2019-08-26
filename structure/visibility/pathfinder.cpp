#include "pathfinder.h"
#include <queue>

std::vector<Location> Pathfinder::find_path(Location from, Location to)
{
    std::vector<Location> result;
    if (from == to)
    {
        // already there
        return result;
    }

    // flood fill distances for floor (todo: save this for reuse by all monsters)
    std::vector<std::vector<int>> distance(this->map_->get_height(), std::vector(this->map_->get_width(), 0));
    fill(distance, from, to);
    if ( distance[from.row()][from.cell()] == 0)
    {
        // no path
        return result;
    }

    // walk along the shortest path to the source
    walk_back(result, distance, from);
    return result;
}

void Pathfinder::fill(std::vector<std::vector<int>>& distance, Location from, Location to)
{
    assert(from.row() >= 0 && from.row() < static_cast<int>(distance.size()));
    assert(from.cell() >= 0 && from.cell() < static_cast<int>(distance[0].size()));
    assert(to.row() >= 0 && to.row() < static_cast<int>(distance.size()));
    assert(to.cell() >= 0 && to.cell() < static_cast<int>(distance[0].size()));
    if (this->map_->is_opaque(to.cell(), to.row()))
    {
        // destination is a wall
        return;
    }
    std::queue<Location> todo;
    todo.push(to);
    distance[to.row()][to.cell()] = -1;

    while (!todo.empty())
    {
        Location location = todo.front();
        todo.pop();

        int row = location.row();
        int cell = location.cell();

        int neighbor_distance = std::max(distance[row][cell], 0) + 1;

        this->mark_and_add_neighbor(distance, todo, Location(row-1,cell), neighbor_distance);
        this->mark_and_add_neighbor(distance, todo, Location(row-1,cell+1), neighbor_distance);
        this->mark_and_add_neighbor(distance, todo, Location(row,cell+1), neighbor_distance);
        this->mark_and_add_neighbor(distance, todo, Location(row+1,cell+1), neighbor_distance);
        this->mark_and_add_neighbor(distance, todo, Location(row+1,cell), neighbor_distance);
        this->mark_and_add_neighbor(distance, todo, Location(row+1,cell-1), neighbor_distance);
        this->mark_and_add_neighbor(distance, todo, Location(row,cell-1), neighbor_distance);
        this->mark_and_add_neighbor(distance, todo, Location(row-1,cell-1), neighbor_distance);

        // if we just found our source, we can early exit
        if (location == from)
        {
            break;
        }
    }

    distance[to.row()][to.cell()] = 0;
}

void Pathfinder::mark_and_add_neighbor(std::vector<std::vector<int>>& distance, 
                                       std::queue<Location>& todo, 
                                       Location location, int neighbor_distance)
{
    int row = location.row();
    int cell = location.cell();

    if (row < 0 || cell < 0 || 
        row >= static_cast<int>(this->map_->get_height()) || 
        cell >= static_cast<int>(this->map_->get_width()))
    {
        // off the map
        return;
    }

    if (distance[row][cell] != 0)
    {
        // already filled in
        return;
    }

    if (this->map_->is_opaque(cell,row))
    {
        // wall, mark and do not add to todo list
        distance[row][cell] = -1;
        return;
    }

    distance[row][cell] = neighbor_distance;
    todo.push(location);
}                            

std::vector<std::pair<int,int>> neighbors
{
    {-1,0},
    {-1,1},
    {0,1},
    {1,1},
    {1,0},
    {1,-1},
    {0,-1},
    {-1,-1}
};

void Pathfinder::walk_back(std::vector<Location>& result, std::vector<std::vector<int>>& distance, 
                           Location location)
{
    int current_distance = distance[location.row()][location.cell()];
    while (current_distance > 0)
    {
        Location next_location;
        // check each of the neighbors for the next step
        for (int i = 0; i < 8; i++)
        {
            int row = location.row() + neighbors[i].first;
            int cell = location.cell() + neighbors[i].second;
            if (row < 0 || cell < 0 || 
                row >= static_cast<int>(distance.size()) || 
                cell >= static_cast<int>(distance[0].size()))
            {
                // off the map
                continue;
            }
            int new_distance = distance[row][cell];
            if (new_distance == -1)
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
