#ifndef _map_for_casting_h_
#define _map_for_casting_h_

#include "original_shadow_cast.h"
#include "tile.h"

class MapForCasting : public iMap
{
public:
    MapForCasting(Tile* tile) : tile_(tile) {}
    virtual ~MapForCasting() {}

    // iMap: Set the visibility of the cell at the given position.
    virtual void set_visible(uint x, uint y, bool visible);

    // iMap: Return the width of the map.
    virtual uint get_width() const;

    // iMap: Return the height of the map.
    virtual uint get_height() const;

    // iMap: Return whether the given position holds an opaque cell.
    virtual bool is_opaque(uint x, uint y) const;

private:
    Tile* tile_;
};

#endif // _map_for_casting_h_