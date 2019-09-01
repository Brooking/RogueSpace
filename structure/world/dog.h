#ifndef _dog_h_
#define _dog_h_

#include "monster_base.h"

class Dog : public MonsterBase
{
public:
    Dog() : MonsterBase(UIToken::dog) {}
    virtual ~Dog() {}

    // iThing: do its move
    virtual bool move() override
    {
        std::shared_ptr<Floor> floor = this->tile()->floor();
        Location hero_location = floor->hero()->where();

        int distance = this->tile()->where().distance(hero_location);
        std::vector<Location> locations;
        if (distance > 3)
        {
            // move closer or stand still
            locations = this->tile()->where().closer_adjacent_locations(hero_location);
        }
        else
        {
            // the dog is close enough, just move at random
            locations = this->tile()->where().all_adjacent_locations();
        }
        
        Location current = this->tile()->where();
        Location new_location = current.choose_random(locations, floor, this->shared_from_this());
        if (new_location != current)
        {
            this->place(floor->tile(new_location));
            return true;
        }

        return false;
    }
};

#endif // _dog_h_