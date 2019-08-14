#ifndef _los_h_
#define _los_h_

#include <vector>
#include "location.h"

// calculate the line between two locations
std::vector<Location> bresenham_los(int start_row, int start_cell, int end_row, int end_cell);

#endif // _los_h_
