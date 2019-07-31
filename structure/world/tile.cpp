#include <assert.h>
#include "tile.h"

bool Tile::add(iThing* thing)
{
    if (thing != nullptr && thing->tile() == nullptr)
    {
        this->things_.push_back(thing);
        thing->set_tile(this);
        return true;
    }
    
    return false;
}

bool Tile::remove(iThing* thing)
{
    if (thing == nullptr || thing->tile() != this) 
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
            thing->set_tile(nullptr);
            break;
        }
    }

    return thing_found;
}