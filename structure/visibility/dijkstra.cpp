#include "dijkstra.h"

// if it has not been done yet, fill in the entry and add to the todo list
void mark_and_add_neighbor(std::vector<std::vector<unsigned int>>& distance,
                           std::shared_ptr<iMap> map, 
                           std::queue<Location>& todo, 
                           Location location, unsigned int new_distance);

void dijkstra_fill(std::vector<std::vector<unsigned int>>& distance, std::shared_ptr<iMap> map, Location from, Location to)
{
    assert(from.row() < distance.size());
    assert(from.cell() < distance[0].size());
    assert(to.row() < distance.size());
    assert(to.cell() < distance[0].size());
    if (map->is_opaque(to.cell(), to.row()))
    {
        // destination is a wall
        return;
    }
    std::queue<Location> todo;
    todo.push(to);
    distance[to.row()][to.cell()] = 0;

    while (!todo.empty())
    {
        Location location = todo.front();
        todo.pop();

        unsigned int row = location.row();
        unsigned int cell = location.cell();

        unsigned int neighbor_distance = distance[row][cell] + 1;

        mark_and_add_neighbor(distance, map, todo, Location(row-1,cell), neighbor_distance);
        mark_and_add_neighbor(distance, map, todo, Location(row-1,cell+1), neighbor_distance);
        mark_and_add_neighbor(distance, map, todo, Location(row,cell+1), neighbor_distance);
        mark_and_add_neighbor(distance, map, todo, Location(row+1,cell+1), neighbor_distance);
        mark_and_add_neighbor(distance, map, todo, Location(row+1,cell), neighbor_distance);
        mark_and_add_neighbor(distance, map, todo, Location(row+1,cell-1), neighbor_distance);
        mark_and_add_neighbor(distance, map, todo, Location(row,cell-1), neighbor_distance);
        mark_and_add_neighbor(distance, map, todo, Location(row-1,cell-1), neighbor_distance);

        // if we just found our source, we can early exit
        if (location == from)
        {
            break;
        }
    }

    distance[to.row()][to.cell()] = 0;
}

void mark_and_add_neighbor(std::vector<std::vector<unsigned int>>& distance,
                           std::shared_ptr<iMap> map, 
                           std::queue<Location>& todo, 
                           Location location, 
                           unsigned int neighbor_distance)
{
    unsigned int row = location.row();
    unsigned int cell = location.cell();

    if (row >= map->get_height() || 
        cell >= map->get_width())
    {
        // off the map
        return;
    }

    if (distance[row][cell] != 0)
    {
        // already filled in
        return;
    }

    if (map->is_opaque(cell,row))
    {
        // wall, mark and do not add to todo list
        distance[row][cell] = -1;
        return;
    }

    distance[row][cell] = neighbor_distance;
    todo.push(location);
}                            


