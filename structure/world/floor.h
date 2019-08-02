#ifndef _floor_h_
#define _floor_h_

#include <vector>
#include "tile.h"
#include "location.h"
#include "ifloor.h"

//
// Holds a single floor
//
class Floor : public iFloor
{
public:
    Floor(int height, int width);
    virtual ~Floor() {}

    // iFloor...
    // the ui is giving us a callback
    virtual bool register_update(iUpdate* update_interface);

    // returns the height (number of rows)
    virtual int height() { return tile_.size(); }

    // returns the width (number of cells per row)
    virtual int width() { return tile_[0].size(); }

    // returns the ui token for a given location
    virtual UIToken token(Location location);

    // returns the tile at a given location
    Tile* tile(Location location);

    // the spot our tiles call us when things change
    bool update(Location location);

private:
    std::vector<std::vector<Tile>> tile_;
    iUpdate* update_interface_;
};

#endif //_floor_h_