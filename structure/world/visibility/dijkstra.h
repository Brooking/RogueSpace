#ifndef _dijkstra_h_
#define _dijkstra_h_

#include <queue>
#include <vector>
#include "../iwall_map.h"
#include "location.h"

// a list of row/column deltas to (orthogonal+diagonal) neighbors
static std::vector<std::pair<int,int>> neighbors
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

// 
// Dijkstra graph - an array showing the stepping distance from any tile to an origin
// (in our case the hero). Used in path finding.
//
void dijkstra_fill(
    std::vector<std::vector<unsigned int>>& distance,
    std::shared_ptr<iWallMap> map, 
    Location from, 
    Location to);

#endif // _dijkstra_h_