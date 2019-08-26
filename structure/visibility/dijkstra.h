#ifndef _dijkstra_h_
#define _dijkstra_h_

#include <vector>
#include <queue>
#include "../world/location.h"
#include "imap.h"

// fill in the djykstra graph
void dijkstra_fill(std::vector<std::vector<int>>& distance, iMap* map, Location from, Location to);

#endif // _dijkstra_h_