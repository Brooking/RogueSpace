#include <assert.h>
#include "tile.h"
#include "floor.h"

UIToken Tile::token() const
{ 
    if (this->num_things() == 0)
    {
        // nothing on the tile, return the tile's own token
        return this->token_; 
    }

    // return the token from the top of the stack
    return this->things_.back()->token();
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

void Tile::add_visible(Location location)
{
    this->visible_.insert(location);
}

bool Tile::is_visible(Location location) const
{
    return this->visible_.count(location) > 0;
}

bool Tile::visibility_has_been_calculated() const
{
    return this->visible_.size() > 0;
}

