#include <assert.h>
#include "floor.h"
#include "map_for_casting.h"
#include "tile.h"

UIToken Tile::token()
{
    std::shared_ptr<Floor> floor = this->floor();
    if (floor == nullptr)
    {
        return UIToken::none;
    }

    std::shared_ptr<Hero> hero = floor->hero();
    if (hero == nullptr)
    {
        return UIToken::none;
    }

    UIToken result = UIToken::none;
    if (this->num_things() == 0)
    {
        // nothing on the tile, start with a floor
        result = this->is_lit_ ? 
                    UIToken::lit_floor : 
                    UIToken::visible_floor; 
    }
    else
    {
        // start with the token from the top of the stack
        result = this->things_.back()->token();
    }

    if (floor->hero()->can_see(this->where()))
    {
        // the hero can see this, mark it as having been seen
        // (this has the side effect of only marking those
        //  spots that appear on the screen as having been seen,
        //  which makes some sense)
        this->has_been_seen_ = true;
    }
    else if (this->has_been_seen_)
    {
        if (is_wall(result))
        {
            result = UIToken::seen_wall;
        }
        else
        {
            result = UIToken::seen_floor;
        }
    }
    else
    {
        // can't see and has never been seen
        result = UIToken::none;
    }

    return result;
}


bool Tile::add(std::shared_ptr<iThing> thing)
{
    if (thing != nullptr)
    {
        if (this->there_is_room(thing))
        {
            this->things_.push_back(thing);
            this->fullness_ = this->calculate_fullness();
            if (this->floor_ != nullptr)
            {
                this->floor_->update(this->location_, thing->is_center());
            }
            return true;
        }
    }
    
    return false;
}

bool Tile::remove(std::shared_ptr<iThing> thing)
{
    if (thing == nullptr) 
    {
        return false;
    }

    bool thing_found = false;
    for (size_t i = 0; i < this->things_.size(); i++) 
    {
        if (this->things_[i] == thing) 
        {
            thing_found = true;
            this->things_.erase(this->things_.begin()+i);
            this->fullness_ = this->calculate_fullness();
            if (this->floor_ != nullptr)
            {
                this->floor_->update(this->location_);
            }
            break;
        }
    }

    return thing_found;
}

ContentSize Tile::calculate_fullness()
{
    ContentSize size = ContentSize::empty;
    for (auto thing : this->things_)
    {
        if (static_cast<unsigned int>(thing->content_size()) > static_cast<unsigned int>(size))
        {
            size = thing->content_size();
        }
    }

    return size;
}

bool Tile::there_is_room(std::shared_ptr<iThing> thing)
{
    assert(thing->content_size() != ContentSize::empty);

    if (this->fullness_ == ContentSize::empty)
    {
        return true;
    }

    if (this->fullness_ == ContentSize::small)
    {
        return thing->content_size() != ContentSize::full;
    }

    if (this->fullness_ == ContentSize::large)
    {
        return thing->content_size() == ContentSize::small;
    }

    assert(this->fullness_ == ContentSize::full);
    return false;
}

void Tile::add_los_range(Location location, int range)
{
    (*this->los_range_)[location.row()][location.cell()] = range;
}

int Tile::get_los_range(Location location)
{
    if (this->los_range_ == nullptr)
    {
        this->los_range_ = 
            new std::vector<std::vector<int>>(
                this->floor_->height(), 
                std::vector<int>(
                    this->floor_->width(), 
                    INT_MAX
                )
            );
        
        MapForCasting map(this->shared_from_this(), CastingScan::visibility);
        do_fov(map, this->where().cell(), this->where().row());
        
    }

    return ((*this->los_range_)[location.row()][location.cell()]);
}
