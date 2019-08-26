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
const int SightRange = 10;

//
// Monster with short sight, but can path find
//
class Rat : public MonsterBase
{
public:
    Rat() : 
        MonsterBase(UIToken::rat), ai_state_(AiState::Wandering), 
        home_(Location()), target_() {}
    virtual ~Rat() {}

    // iThing: do its move
    virtual bool move() override
    {
        Location here = this->tile_->where();
        std::shared_ptr<Floor> floor = this->tile_->floor();
        std::shared_ptr<Hero> hero = floor->hero();

        // handle state transitions
        bool changed;
        do
        {
            changed = false;

            if (hero->can_be_seen_from(here, SightRange))
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
        std::shared_ptr<iThing> shared_this = this->shared_from_this();
        switch(this->ai_state_)
        {
        case AiState::Wandering:
            // just wander around
            new_location = here.choose_random(here.all_adjacent_locations(), floor, shared_this);
            break;

        case AiState::Beelining:
            // head toward where the hero was
            // todo - replace with pathfinder
            new_location = here.choose_random(here.closer_adjacent_locations(this->target_), floor, shared_this);
            break;

        case AiState::Homing:
            // head toward home
            // todo - replace with pathfinder
            new_location = here.choose_random(here.closer_adjacent_locations(this->home_), floor, shared_this);
            break;
        }

        if (new_location != here)
        {
            this->place(floor->tile(new_location));
            return true;
        }
        return false;
    }

    virtual bool place(std::shared_ptr<Tile> tile) override
    {
        bool result = ThingBase::place(tile);
        this->home_ = tile->where();
        return result;
    }

private:
    AiState ai_state_;
    Location home_;
    Location target_;
};

#endif // _rat_h_