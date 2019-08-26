#include "map_for_casting.h"
#include "tile.h"
#include "floor.h"

void MapForCasting::set_los(uint x, uint y, uint range_squared)
{
    if (range_squared < INT_MAX)
    {
        std::shared_ptr<Tile> tile = this->floor_->tile(Location(y,x));
        if (this->scan_ == CastingScan::visibility)
        {
            this->tile_->add_los_range(Location(y,x), sqrt(range_squared));
            if (range_squared <= this->sighting_range_squared_)
            {
                // seen - in range
                tile->set_has_been_seen(true);
            }
            else if (tile->is_lit())
            {
                // seen - in los and lit
                tile->set_has_been_seen(true);                
            }

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
