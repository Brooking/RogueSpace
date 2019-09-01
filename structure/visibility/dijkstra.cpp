#include "dijkstra.h"

// if it has not been done yet, fill in the entry and add to the todo list
void mark_and_add_neighbor(std::vector<std::vector<int>>& distance,
                           std::shared_ptr<iMap> map, 
                           std::queue<Location>& todo, 
                           Location location, int new_distance);

void dijkstra_fill(std::vector<std::vector<int>>& distance, std::shared_ptr<iMap> map, Location from, Location to)
{
    assert(from.row() >= 0 && from.row() < static_cast<int>(distance.size()));
    assert(from.cell() >= 0 && from.cell() < static_cast<int>(distance[0].size()));
    assert(to.row() >= 0 && to.row() < static_cast<int>(distance.size()));
    assert(to.cell() >= 0 && to.cell() < static_cast<int>(distance[0].size()));
    if (map->is_opaque(to.cell(), to.row()))
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

void mark_and_add_neighbor(std::vector<std::vector<int>>& distance,
                           std::shared_ptr<iMap> map, 
                           std::queue<Location>& todo, 
                           Location location, int neighbor_distance)
{
    int row = location.row();
    int cell = location.cell();

    if (row < 0 || cell < 0 || 
        row >= static_cast<int>(map->get_height()) || 
        cell >= static_cast<int>(map->get_width()))
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


