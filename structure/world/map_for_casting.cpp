#include "map_for_casting.h"
#include "tile.h"
#include "floor.h"

void MapForCasting::set_visible(uint x, uint y, bool visible)
{
    if (visible)
    {
        Tile* tile = this->floor_->tile(Location(y,x));
        if (this->scan_ == CastingScan::visibility)
        {
            this->tile_->add_visible(Location(y,x));
            tile->set_has_been_seen(true);
        }
        else if (this->scan_ == CastingScan::illumination)
        {
            tile->set_is_lit(true);
        }
    }
}

uint MapForCasting::get_width() const
{
    return this->floor_->width();
}

uint MapForCasting::get_height() const
{
    return this->floor_->height();
}

bool MapForCasting::is_opaque(uint x, uint y) const
{
    return this->floor_->tile(Location(y, x))->how_full() == ContentSize::full;
}
