#include <assert.h>
#include "hero.h"
#include "floor.h"

Hero::Hero(Tile* tile) : 
    token_(UIToken::hero), tile_(nullptr)
{
    this->place(tile);
}


bool Hero::place(Tile* tile)
{
    if (tile != nullptr && tile->is_open())
    {
        if (this->tile_ != nullptr)
        {
            this->tile_->remove(this);
            this->tile_ = nullptr;
        }
        tile->add(this);
        this->tile_ = tile;
        return true;
    }

    return false;
}

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