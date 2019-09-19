#ifndef _los_h_
#define _los_h_

#include <vector>
#include "location.h"

class Los
{
public:
    //
    // calculate the line between two locations.
    //
    //  This uses the Bresenham algorithm which results in a thin trail 
    // (usually 1 tile wide, sparse at diagonals)
    // includes both endpoints
    //
    static std::vector<Location> bresenham_los(
        unsigned int start_row, 
        unsigned int start_cell, 
        unsigned int end_row, 
        unsigned int end_cell);
};

#endif // _los_h_
