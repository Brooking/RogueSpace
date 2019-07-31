#ifndef _ithing_h_
#define _ithing_h_

#include "../inc/uitokens.h"
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

    // Change this thing's tile 
    // todo: this method does not check the current tile before working...
    virtual bool set_tile(Tile* tile) = 0;
};

#endif // _ithing_h_
