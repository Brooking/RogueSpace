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
        this->things_.push_back(thing);
        if (this->floor_ != nullptr)
        {
            this->floor_->update(this->location_);
        }
        return true;
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
            if (this->floor_ != nullptr)
            {
                this->floor_->update(this->location_);
            }
            break;
        }
    }

    return thing_found;
}