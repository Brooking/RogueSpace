#include <assert.h>
#include "tile.h"
#include "floor.h"

UIToken Tile::token() const
{
    Floor* floor = this->floor();
    if (floor == nullptr)
    {
        return UIToken::none;
    }

    Hero* hero = floor->hero();
    if (hero == nullptr)
    {
        return UIToken::none;
    }

    UIToken result = UIToken::none;
    if (this->num_things() == 0)
    {
        // nothing on the tile, start with a floor
        result = UIToken::visible_floor; 
    }
    else
    {
        // start with the token from the top of the stack
        result = this->things_.back()->token();
    }

    if (floor->hero()->can_see(this) || this->is_lit_)
    {
        // if the hero can see this tile or the tile is lit, 
        // just return it
    }
    else if (this->has_been_seen_)
    {
        if (result == UIToken::visible_floor)
        {
            result = UIToken::seen_floor;
        }
        else if (result == UIToken::visible_wall)
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


bool Tile::add(iThing* thing)
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

bool Tile::remove(iThing* thing)
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

bool Tile::there_is_room(iThing* thing)
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

void Tile::add_los(Location location)
{
    this->los_.insert(location);
}

bool Tile::has_los(Location location) const
{
    return this->los_.count(location) > 0;
}

bool Tile::los_has_been_calculated() const
{
    return this->los_.size() > 0;
}

