#ifndef _euclid_h_
#define _euclid_h_

#include <vector>
#include "location.h"

namespace euclid
{

// returns the distance between two spots
unsigned int distance(Location location1, Location location2);

// get a list of adjacent locations that are closer to the target than the current
std::vector<Location> closer_adjacent_locations(Location target, Location location);

} // namespace euclid

#endif // _euclid_h_