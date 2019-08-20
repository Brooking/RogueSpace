#ifndef _rat_h_
#define _rat_h_

#include "monster_base.h"
#include "floor.h" // todo should be ifloor.h

enum class AiState
{
    Wandering,
    Beelining,
    Homing
};

const int HomeRange = 5;

//
// Monster with short sight, but can path find
//
class Rat : public MonsterBase
{
public:
    Rat(Tile* tile) : 
        MonsterBase(tile, UIToken::rat), ai_state_(AiState::Wandering), 
        home_(this->tile_->where()), target_() {}
    virtual ~Rat() {}

    // iThing: do its move
    virtual bool move()
    {
        Location here = this->tile_->where();
        Floor* floor = const_cast<Floor*>(this->tile_->floor());
        Hero* hero = floor->hero();

        // handle state transitions
        bool changed;
        do
        {
            changed = false;

            if (hero->can_see(here))
            {
                // I see the hero
                if (this->ai_state_ != AiState::Beelining || here == this->target_)
                {
                    this->target_ = hero->tile()->where();
                    changed = true;
                }
                this->ai_state_ = AiState::Beelining;
                continue;
            } 
            else if (this->ai_state_ != AiState::Beelining)
            {
                if (here.distance(this->home_) > HomeRange)
                {
                    // I have wandered away from home
                    changed = (this->ai_state_ != AiState::Homing);
                    this->ai_state_ = AiState::Homing;
                    continue;
                } 
                else
                {
                    // Ima just wander
                    changed = (this->ai_state_ != AiState::Wandering);
                    this->ai_state_ = AiState::Wandering;
                    continue;
                }
            }
        } while(changed);

        // act in this state
        Location new_location;
        switch(this->ai_state_)
        {
        case AiState::Wandering:
            // just wander around
            new_location = here.chose_random(here.all_adjacent_locations(), *floor, this);
            break;

        case AiState::Beelining:
            // head toward where the hero was
            // todo - replace with pathfinder
            new_location = here.chose_random(here.closer_adjacent_locations(this->target_), *floor, this);
            break;

        case AiState::Homing:
            // head toward home
            // todo - replace with pathfinder
            new_location = here.chose_random(here.closer_adjacent_locations(this->home_), *floor, this);
            break;
        }

        if (new_location != here)
        {
            this->place(floor->tile(new_location));
            return true;
        }
        return false;
    }

private:
    AiState ai_state_;
    Location home_;
    Location target_;
};

#endif // _rat_h_