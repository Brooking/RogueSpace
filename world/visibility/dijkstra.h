#ifndef _dijkstra_h_
#define _dijkstra_h_

#include <queue>
#include <vector>
#include "../iwall_map.h"
#include "location.h"

class Dijkstra
{
public:
    // a list of row/column deltas to (orthogonal+diagonal) neighbors
    // todo - isnt this more general? and cant this include diagonal indication?
    static const std::vector<std::pair<int,int>> Neighbors;
    // {
    //     {-1,0},
    //     {-1,1},
    //     {0,1},
    //     {1,1},
    //     {1,0},
    //     {1,-1},
    //     {0,-1},
    //     {-1,-1}
    // };

    // 
    // Dijkstra graph - an array showing the stepping distance from any tile to an origin
    // (in our case the hero). Used in path finding.
    //
    static void fill(
        std::vector<std::vector<unsigned int>>& distance,
        std::shared_ptr<iWallMap> map,
        Location to,
        Location from = Location());

private:
    // if it has not been done yet, fill in the entry and add to the todo list
    static void mark_and_add_neighbor(
        std::vector<std::vector<unsigned int>>& distance,
        std::shared_ptr<iWallMap> map, 
        std::queue<Location>& todo, 
        Location location, unsigned int new_distance);

    static const unsigned int OrthogonalDistance = 10;
    static const unsigned int DiagonalDistance = 14;

};
#endif // _dijkstra_h_