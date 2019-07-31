#ifndef _floor_h_
#define _floor_h_

#include <vector>
#include "tile.h"
#include "../inc/location.h"

//
// Holds a single floor
//
class Floor
{
public:
    Floor(int height, int width);

    int height() { return tile_.size(); }
    int width() { return tile_[0].size(); }
    Tile* tile(Location location) {return (&(this->tile_[location.row][location.cell])); }

private:
    std::vector<std::vector<Tile>> tile_;
};

#endif //_floor_h_