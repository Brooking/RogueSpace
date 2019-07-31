#include "tile.h"
#include "assert.h"

void Tile::add(iThing* thing)
{
    assert(thing->tile() == nullptr);
    this->things_.push_back(thing);
    thing->set_tile(this);
}

void Tile::remove(iThing* thing)
{
    assert(thing->tile() == this);
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

    // ensure we found the thing
    assert(thing_found);
}