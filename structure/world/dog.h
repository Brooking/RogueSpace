#ifndef _dog_h_
#define _dog_h_

#include "actor_base.h"

class Dog : public ActorBase
{
public:
    static const unsigned int MoveTime = 50;

public:
    Dog() : ActorBase(TokenType::dog, Dog::MoveTime) {}
    virtual ~Dog() {}

    // iActor: do its move
    virtual unsigned int move() override
    {
        Location original_location = this->tile()->where();
        std::shared_ptr<Floor> floor = this->tile()->floor();
        Location hero_location = floor->hero_location();

        unsigned int distance = this->tile()->where().distance(hero_location);
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
        
        Location new_location = floor->choose_random(locations, this->shared_from_this());
        if (new_location != Location())
        {
            this->place(floor->tile(new_location));
        }

        return this->calculate_move_time(original_location);
    }
};

#endif // _dog_h_