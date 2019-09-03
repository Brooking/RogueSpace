#include <cmath> // std::abs
#include "los.h"

// From RogueBasin...
std::vector<Location> bresenham_los(int start_row, int start_cell, int end_row, int end_cell)
{
    std::vector<Location> result;

    int delta_cell(end_cell - start_cell);
    // if start_cell == end_cell, then it does not matter what we set here
    signed char const i_cell(static_cast<signed char>((delta_cell > 0) - (delta_cell < 0)));
    delta_cell = std::abs(delta_cell) << 1;
 
    int delta_row(end_row - start_row);
    // if start_row == end_row, then it does not matter what we set here
    signed char const i_row(static_cast<signed char>((delta_row > 0) - (delta_row < 0)));
    delta_row = std::abs(delta_row) << 1;
 
    // add the start
    result.push_back(Location(start_row, start_cell));
 
    if (delta_cell >= delta_row)
    {
        // error may go below zero
        int error(delta_row - (delta_cell >> 1));
 
        while (start_cell != end_cell)
        {
            // reduce error, while taking into account the corner case of error == 0
            if ((error > 0) || (!error && (i_cell > 0)))
            {
                error -= delta_cell;
                start_row += i_row;
            }
            // else do nothing
 
            error += delta_row;
            start_cell += i_cell;
 
            result.push_back(Location(start_row, start_cell));
        }
    }
    else
    {
        // error may go below zero
        int error(delta_cell - (delta_row >> 1));
 
        while (start_row != end_row)
        {
            // reduce error, while taking into account the corner case of error == 0
            if ((error > 0) || (!error && (i_row > 0)))
            {
                error -= delta_row;
                start_cell += i_cell;
            }
            // else do nothing
 
            error += delta_cell;
            start_row += i_row;
 
            result.push_back(Location(start_row, start_cell));
        }
    }

    return result;
}    
