#ifndef _rat_h_
#define _rat_h_

#include "monster_base.h"

//#include <cstdlib> // for rand()
#include "floor.h" // should be ifloor.h

class Rat : public MonsterBase
{
public:
    Rat(Tile* tile) : MonsterBase(tile, UIToken::rat) {}
    virtual ~Rat() {}

    // iThing: do its move
    virtual bool move()
    {
        Floor* floor = const_cast<Floor*>(this->tile_->floor());
        Location hero_location = floor->hero()->where();

        // move closer or stand still
        Location current = this->tile_->where();
        std::vector<Location> closer_locations = 
            current.closer_adjacent_locations(hero_location);
        Location new_location = current.chose_random(closer_locations, *floor, this);
        if (new_location != current)
        {
            this->place(floor->tile(new_location));
            return true;
        }

        return false;
    }
};

#endif // _rat_h_