#include <assert.h>
#include "hero.h"
#include "floor.h"

Hero::Hero(Tile* tile, int sight_range) : 
    ThingBase(tile, UIToken::hero, ContentSize::large, /*center*/true),
    sight_range_(sight_range)
{
    Tile* hero_tile = this->tile();
    if (hero_tile != nullptr)
    {
        Floor* hero_floor = hero_tile->floor();
        if (hero_floor != nullptr)
        {
            hero_floor->add_hero(this);
            hero_floor->update(hero_tile->where(),/*is_center*/true);
        }
    }
}

bool Hero::move()
{
    throw std::domain_error("heroes do not move at random");
}

bool Hero::move(Direction direction)
{
    Location newLocation = this->where().apply_direction(direction);
    Floor* floor = const_cast<Floor*>(this->tile_->floor());
    Tile* newTile = floor->tile(newLocation);    
    if (newTile != nullptr && newTile->there_is_room(this)) 
    {
        this->tile_->remove(this);
        this->tile_ = newTile;
        newTile->add(this);
        return true;
    }

    return false;
}

bool Hero::move_to(Location location)
{
    throw std::domain_error("move_to not yet implemented on hero");
}