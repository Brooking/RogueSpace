#ifndef _pathfinder_h_
#define _pathfinder_h_

#include <vector>
#include <queue>
#include "../world/location.h"
#include "imap.h"

#ifndef PROTECTED_ACCESS
#define PROTECTED_ACCESS protected
#endif

class Pathfinder
{
public:
    Pathfinder(iMap* map) : map_(map) {}
    virtual ~Pathfinder() {}

    // find the shortest path from 'from' to 'to'
    std::vector<Location> find_path(Location from, Location to);

PROTECTED_ACCESS:
    // fill in the djykstra graph
    void fill(std::vector<std::vector<int>>& distance, Location from, Location to);

    // if it has not been done yet, fill in the entry and add to the todo list
    void mark_and_add_neighbor(std::vector<std::vector<int>>& distance, 
                               std::queue<Location>& todo, 
                               Location location, int new_distance);

    // walk from the destination back to source
    void walk_back(std::vector<Location>& result, std::vector<std::vector<int>>& distance, 
                   Location location);


private:
    iMap* map_;
};

#endif // _pathfinder_h_