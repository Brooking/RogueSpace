#include <assert.h>
#include "hero.h"
#include "floor.h"

void Hero::move(Direction direction)
{
    Location newLocation = apply_direction(this->where(), direction);
    Floor* floor = const_cast<Floor*>(this->tile_->floor());
    Tile* newTile = floor->tile(newLocation);
    if (newTile->is_open()) 
    {
        this->tile_->remove(this);
        newTile->add(this);
        this->tile_ = newTile;
    }
}

void Hero::move_to(Location location)
{
    assert(false);
}