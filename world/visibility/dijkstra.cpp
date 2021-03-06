#include "dijkstra.h"

const std::vector<std::pair<int,int>> Dijkstra::Neighbors
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


void Dijkstra::fill(
    std::vector<std::vector<unsigned int>>& distance,
    std::shared_ptr<iWallMap> map,
    Location to,
    Location from)
{
    // There general algorithm here is that we start at the destination, and on each 
    // iteration, we mark all of our neighbors as being 1 further away, we also push
    // each neighbor into the todo queue. Then we iterate on the next spot in the queue
    // until we are done.

    assert(from == Location() || from.row() < map->height());
    assert(from == Location() || from.cell() < map->width());
    assert(to.row() < map->height());
    assert(to.cell() <map->width());
    if (map->is_opaque(to.row(), to.cell()))
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

        unsigned int orthogonal_distance = distance[row][cell] + Dijkstra::OrthogonalDistance;
        unsigned int diagonal_distance = distance[row][cell] + Dijkstra::DiagonalDistance;

        mark_and_add_neighbor(distance, map, todo, Location(row-1,cell), orthogonal_distance);
        mark_and_add_neighbor(distance, map, todo, Location(row-1,cell+1), diagonal_distance);
        mark_and_add_neighbor(distance, map, todo, Location(row,cell+1), orthogonal_distance);
        mark_and_add_neighbor(distance, map, todo, Location(row+1,cell+1), diagonal_distance);
        mark_and_add_neighbor(distance, map, todo, Location(row+1,cell), orthogonal_distance);
        mark_and_add_neighbor(distance, map, todo, Location(row+1,cell-1), diagonal_distance);
        mark_and_add_neighbor(distance, map, todo, Location(row,cell-1), orthogonal_distance);
        mark_and_add_neighbor(distance, map, todo, Location(row-1,cell-1), diagonal_distance);

        // if we just found our source, we can early exit
        if (location == from)
        {
            break;
        }
    }

    // why do this both before and after?????
    distance[to.row()][to.cell()] = 0;
}

void Dijkstra::mark_and_add_neighbor(
    std::vector<std::vector<unsigned int>>& distance,
    std::shared_ptr<iWallMap> map, 
    std::queue<Location>& todo, 
    Location location, 
    unsigned int neighbor_distance)
{
    unsigned int row = location.row();
    unsigned int cell = location.cell();

    if (row >= map->height() || 
        cell >= map->width())
    {
        // off the map
        return;
    }

    if (distance[row][cell] != 0)
    {
        // already filled in
        return;
    }

    if (map->is_opaque(row,cell))
    {
        // wall, mark and do not add to todo list
        distance[row][cell] = UINT_MAX;
        return;
    }

    distance[row][cell] = neighbor_distance;
    todo.push(location);
}                            
