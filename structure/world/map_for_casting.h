#ifndef _map_for_casting_h_
#define _map_for_casting_h_

#include <memory>
#include "../visibility/original_shadow_cast.h"
#include "tile.h"

enum CastingScan
{
    visibility,
    illumination
};

class MapForCasting : public iMap
{
public:
    MapForCasting(std::shared_ptr<Tile> tile, CastingScan scan, uint sighting_range) : 
        tile_(tile), floor_(tile->floor()), scan_(scan), 
        sighting_range_squared_(sighting_range*sighting_range)
    {}
    virtual ~MapForCasting() {}

    // iMap: Set the visibility of the cell at the given position.
    virtual void set_los(uint x, uint y, uint range_squared) override;

    // iMap: Return the width of the map.
    virtual uint get_width() const override;

    // iMap: Return the height of the map.
    virtual uint get_height() const override;

    // iMap: Return whether the given position holds an opaque cell.
    virtual bool is_opaque(uint x, uint y) const override;

private:
    std::shared_ptr<Tile> tile_;
    std::shared_ptr<Floor> floor_;
    CastingScan scan_;
    uint sighting_range_squared_;
};

#endif // _map_for_casting_h_