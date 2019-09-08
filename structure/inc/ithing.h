#ifndef _ithing_h_
#define _ithing_h_

#include <memory>
#include "content_size.h"
#include "uitoken.h"
class Tile;

//
// interface for stuff that can be in the floor
//
class iThing
{
public:
    virtual ~iThing() = default;

    // How this thing should be displayed in the UI
    virtual UIToken token() const = 0;

    // The tile that this thing is on
    virtual std::shared_ptr<Tile> tile() const = 0;

    // This thing fills the tile
    virtual ContentSize content_size() const = 0;

    // This thing is centered
    virtual bool is_center() const = 0;

    // Put this thing on a tile (remove it from its current tile)
    virtual bool place(std::shared_ptr<Tile> tile) = 0;

    // Remove this thing from its tile
    virtual bool remove() = 0;
};

#endif // _ithing_h_
