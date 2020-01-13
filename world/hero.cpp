#include <assert.h>
#include "floor.h"
#include "hero.h"
#include "visibility/fov.h"

Hero::Hero(unsigned int sight_range) : 
    ActorBase(TokenType::hero, Hero::WalkTime, /*center*/true),
    sight_range_(sight_range),
    max_stamina_(Hero::DefaultMaxStamina),
    current_stamina_(Hero::DefaultMaxStamina),
    running_(false)
{}

unsigned int Hero::move()
{
    this->current_stamina_ = std::min(
        this->max_stamina_, 
        this->current_stamina_ + Hero::RestStaminaRecovery);

    // need to update because the normal mechanism for 
    // causing changes to show up in the UI is adds/deletes from
    // the floor. There are none here, but still want the UI 
    // to reflect the change
    this->tile()->floor()->update(this->where(),/*is_center*/true);
    return Hero::RunTime;
}

unsigned int Hero::move(Direction direction)
{
    Location original_location = this->tile()->where();
    Location newLocation = this->where().apply_direction(direction);
    std::shared_ptr<Floor> floor = this->tile()->floor();
    std::shared_ptr<Tile> newTile = floor->tile(newLocation);   
    std::shared_ptr<iThing> shared_this = this->shared_from_this();
    if (newTile != nullptr && newTile->there_is_room(shared_this)) 
    {
        this->tile()->remove(shared_this);
        this->tile_ = newTile;

        // handle stamina
        if (this->running_)
        {
            unsigned int stamina_cost = this->is_diagonal_move(original_location) ?
                static_cast<unsigned int>(Hero::RunStaminaCost * Hero::SquareRootOf2) :
                Hero::RunStaminaCost;
            if (this->current_stamina_ < stamina_cost)
            {
                this->current_stamina_ = 0;
                this->toggle_run();
            }
            else
            {
                this->current_stamina_ -= stamina_cost;
            }            
        }
        else
        {
            this->current_stamina_ = std::min(
                this->max_stamina_, 
                this->current_stamina_ + Hero::WalkStaminaRecovery);
        }

        newTile->add(shared_this);
        return this->calculate_move_time(original_location);
    }

    return 0;
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

void Hero::toggle_run()
{
    this->running_ = !this->running_;
    this->move_time_ = (this->running_) ? Hero::RunTime : Hero::WalkTime;
    this->tile()->floor()->update(this->where(),/*is_center*/true);
}
