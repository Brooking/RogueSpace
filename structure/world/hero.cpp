#include <assert.h>
#include "hero.h"
#include "floor.h"

bool Hero::move(Direction direction)
{
    Location newLocation = this->where().apply_direction(direction);
    Floor* floor = const_cast<Floor*>(this->tile_->floor());
    Tile* newTile = floor->tile(newLocation);    
    if (newTile != nullptr && newTile->is_open()) 
    {
        this->tile_->remove(this);
        newTile->add(this);
        this->tile_ = newTile;
        return true;
    }

    return false;
}

bool Hero::move_to(Location location)
{
    throw std::domain_error("move_to not yet implemented on hero");
}