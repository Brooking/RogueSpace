#ifndef _bee_h_
#define _bee_h_

#include "floor.h" // todo should be ifloor.h
#include "monster_base.h"

//
// Monster that sees you wherever you are, but can't navigate well
//
class Bee : public MonsterBase
{
public:
    Bee() : MonsterBase(TokenType::bee) {}
    virtual ~Bee() {}

    // iThing: do its move
    virtual bool move() override
    {
        std::shared_ptr<Floor> floor = this->tile()->floor();
        Location hero_location = floor->hero()->where();

        // move closer or stand still
        Location current = this->tile()->where();
        std::vector<Location> closer_locations = 
            current.closer_adjacent_locations(hero_location);
        Location new_location = floor->choose_random(closer_locations, this->shared_from_this());
        if (new_location != Location())
        {
            this->place(floor->tile(new_location));
            return true;
        }

        return false;
    }
};
#endif // _bee_h_