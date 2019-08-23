#ifndef _bee_h_
#define _bee_h_

#include "monster_base.h"
//#include <cstdlib> // for rand()
#include "floor.h" // todo should be ifloor.h

//
// Monster that sees you wherever you are, but can't navigate well
//
class Bee : public MonsterBase
{
public:
    Bee() : MonsterBase(UIToken::bee) {}
    virtual ~Bee() {}

    // iThing: do its move
    virtual bool move()
    {
        std::shared_ptr<Floor> floor = this->tile_->floor();
        Location hero_location = floor->hero()->where();

        // move closer or stand still
        Location current = this->tile_->where();
        std::vector<Location> closer_locations = 
            current.closer_adjacent_locations(hero_location);
        Location new_location = current.chose_random(closer_locations, floor, this->shared_from_this());
        if (new_location != current)
        {
            this->place(floor->tile(new_location));
            return true;
        }

        return false;
    }
};
#endif // _bee_h_