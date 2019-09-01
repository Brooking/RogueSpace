#ifndef _pathfinder_h_
#define _pathfinder_h_

#include <queue>
#include <vector>
#include "imap.h"
#include "../world/location.h"

#ifndef PROTECTED_ACCESS
#define PROTECTED_ACCESS protected
#endif

//
// find a path using dijksta graph
//

class Pathfinder
{
public:
    Pathfinder(std::shared_ptr<iMap> map) : map_(map) {}
    virtual ~Pathfinder() {}

    // find the shortest path from 'from' to 'to'
    std::vector<Location> find_path(Location from, Location to);

PROTECTED_ACCESS:
    // walk from the destination back to source
    void walk_back(std::vector<Location>& result, std::vector<std::vector<int>>& distance, 
                   Location location);


private:
    std::shared_ptr<iMap> map_;
};

#endif // _pathfinder_h_