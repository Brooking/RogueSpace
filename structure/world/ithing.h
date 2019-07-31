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
    virtual UIToken token() const = 0;
    virtual Tile* tile() const = 0;
    virtual void set_tile(Tile* tile) = 0;
};

#endif // _ithing_h_
