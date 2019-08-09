#ifndef _ithing_h_
#define _ithing_h_

#include "uitokens.h"
class Tile;

//
// interface for stuff that can be in the floor
//
class iThing
{
public:
    // How this thing should be displayed in the UI
    virtual UIToken token() const = 0;

    // The tile that this thing is on
    virtual Tile* tile() const = 0;

    // This thing fills the tile
    virtual bool fills_tile() const = 0;

    // This thing is centered
    virtual bool is_center() const = 0;

    // Move this thing
    virtual bool move() = 0;
};

#endif // _ithing_h_
