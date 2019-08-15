#include "map_for_casting.h"
#include "tile.h"
#include "floor.h"

void MapForCasting::set_visible(uint x, uint y, bool visible)
{
    if (visible)
    {
        this->tile_->add_visible(Location(y,x));
        Tile* tile = this->tile_->floor()->tile(Location(y,x));
        tile->set_has_been_seen(true);
    }
}

uint MapForCasting::get_width() const
{
    return this->tile_->floor()->width();
}

uint MapForCasting::get_height() const
{
    return this->tile_->floor()->height();
}

bool MapForCasting::is_opaque(uint x, uint y) const
{
    return this->tile_->floor()->tile(Location(y, x))->how_full() == ContentSize::full;
}
