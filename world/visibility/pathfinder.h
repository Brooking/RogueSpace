#ifndef _pathfinder_h_
#define _pathfinder_h_

#include <queue>
#include <vector>
#include "../iwall_map.h"
#include "location.h"

#ifndef PROTECTED_ACCESS
#define PROTECTED_ACCESS protected
#endif

//
// find a path using dijksta graph
//

class Pathfinder
{
public:
    Pathfinder(std::shared_ptr<iWallMap> map) : map_(map) {}
    virtual ~Pathfinder() = default;

    // find the shortest path from 'from' to 'to'
    std::vector<Location> find_path(Location from, Location to);

PROTECTED_ACCESS:
    // walk from the destination back to source
    void walk_back(std::vector<Location>& result, std::vector<std::vector<unsigned int>>& distance, 
                   Location location);


private:
    std::shared_ptr<iWallMap> map_;
};

#endif // _pathfinder_h_