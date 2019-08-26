#include <assert.h>
#include "hero.h"
#include "floor.h"
#include "map_for_casting.h"
#include "../visibility/original_shadow_cast.h"

Hero::Hero(int sight_range) : 
    ThingBase(UIToken::hero, ContentSize::large, /*center*/true),
    sight_range_(sight_range)
{}

bool Hero::move()
{
    throw std::domain_error("heroes do not move at random");
}

bool Hero::move(Direction direction)
{
    Location newLocation = this->where().apply_direction(direction);
    std::shared_ptr<Floor> floor = this->tile_->floor();
    std::shared_ptr<Tile> newTile = floor->tile(newLocation);   
    std::shared_ptr shared_this = this->shared_from_this();
    if (newTile != nullptr && newTile->there_is_room(shared_this)) 
    {
        this->tile_->remove(shared_this);
        this->tile_ = newTile;
        newTile->add(shared_this);
        return true;
    }

    return false;
}

bool Hero::can_see(Location location)
{
    std::shared_ptr<Tile> tile = this->tile_;
    int los_range = this->tile_->get_los_range(location, this->sight_range_);
    if (los_range <= this->sight_range_)
    {
        // location is in los and close enough to see
        return true;
    }

    std::shared_ptr<Tile> target = tile->floor()->tile(location);
    if (los_range < INT_MAX && target->is_lit())
    {
        // location is in los and lit
        return true;
    }

    return false;
}

bool Hero::can_see(const std::shared_ptr<Tile> tile)
{
    return this->can_see(tile->where());
}

bool Hero::place(std::shared_ptr<Tile> tile)
{
    bool result = ThingBase::place(tile);
    if (tile != nullptr)
    {
        std::shared_ptr<Floor> hero_floor = tile->floor();
        if (hero_floor != nullptr)
        {
            hero_floor->add_hero(this->derived_shared_from_this<Hero>());
            hero_floor->update(tile->where(),/*is_center*/true);
        }
    }

    return result;
}
