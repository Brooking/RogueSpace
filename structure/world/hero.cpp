#include <assert.h>
#include "hero.h"
#include "floor.h"
#include "map_for_casting.h"
#include "../visibility/original_shadow_cast.h"

Hero::Hero(std::shared_ptr<Tile> tile, int sight_range) : 
    ThingBase(tile, UIToken::hero, ContentSize::large, /*center*/true),
    sight_range_(sight_range)
{
    std::shared_ptr<Tile> hero_tile = this->tile();
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
    std::shared_ptr<Tile> newTile = floor->tile(newLocation);    
    if (newTile != nullptr && newTile->there_is_room(this)) 
    {
        this->tile_->remove(this);
        this->tile_ = newTile;
        newTile->add(this);
        return true;
    }

    return false;
}

bool Hero::can_see(Location location)
{
    std::shared_ptr<Tile> tile = this->tile_;
    if (!tile->los_has_been_calculated())
    {
        MapForCasting map(tile, CastingScan::visibility);
        do_fov(map, tile->where().cell(), tile->where().row(), this->sight_range_);
    }
    return tile->has_los(location);
}

// todo - why can this not be a shared_ptr?
bool Hero::can_see(const Tile* tile)
{
    return this->can_see(tile->where());
}