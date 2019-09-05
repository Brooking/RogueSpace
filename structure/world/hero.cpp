#include <assert.h>
#include "floor.h"
#include "hero.h"
#include "map_for_casting.h"
#include "visibility/original_shadow_cast.h"

Hero::Hero(unsigned int sight_range) : 
    ThingBase(UIToken::hero, ContentSize::large, /*center*/true),
    sight_range_(sight_range)
{}

__attribute__((__noreturn__)) bool Hero::move()
{
    throw std::domain_error("heroes do not move at random");
}

bool Hero::move(Direction direction)
{
    Location newLocation = this->where().apply_direction(direction);
    std::shared_ptr<Floor> floor = this->tile()->floor();
    std::shared_ptr<Tile> newTile = floor->tile(newLocation);   
    std::shared_ptr<iThing> shared_this = this->shared_from_this();
    if (newTile != nullptr && newTile->there_is_room(shared_this)) 
    {
        this->tile()->remove(shared_this);
        this->tile_ = newTile;
        newTile->add(shared_this);
        return true;
    }

    return false;
}

bool Hero::can_see(Location location)
{
    unsigned int los_range = this->tile()->get_los_range(location);
    if (los_range <= this->sight_range_)
    {
        // location is in los and close enough to see
        return true;
    }

    std::shared_ptr<Tile> target = this->tile()->floor()->tile(location);
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

bool Hero::can_be_seen_from(Location seer, unsigned int sight_range)
{
    unsigned int los_range = this->tile()->get_los_range(seer);
    if (los_range <= sight_range)
    {
        // location is in los and close enough to see
        return true;
    }

    if (los_range < INT_MAX && this->tile()->is_lit())
    {
        // the hero is lit and in los
        return true;
    }

    return false;
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

Location Hero::where() const
{
    if (!this->tile_.expired())
    {
        return this->tile_.lock()->where();
    }
    return Location();
}
