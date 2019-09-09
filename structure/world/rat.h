#ifndef _rat_h_
#define _rat_h_

#include "floor.h" // todo should be ifloor.h
#include "actor_base.h"

enum class AiState
{
    Wandering,
    Beelining,
    Homing
};

//
// Monster with short sight, but can path find
//
class Rat : public ActorBase
{
public:
    static const unsigned int SightRange = 10;
    static const unsigned int MoveTime = 100;
    static const unsigned int HomeRange = 5;

public:
    Rat() : 
        ActorBase(TokenType::rat, Rat::MoveTime), 
        ai_state_(AiState::Wandering), 
        home_(Location()), target_() {}
    virtual ~Rat() = default;

    // iActor: do its move
    virtual unsigned int move() override
    {
        Location original_location = this->tile()->where();
        std::shared_ptr<Floor> floor = this->tile()->floor();
        std::shared_ptr<Hero> hero = floor->hero().lock();

        // handle state transitions
        bool changed;
        do
        {
            changed = false;

            if (hero->can_be_seen_from(original_location, SightRange))
            {
                // I see the hero
                if (this->ai_state_ != AiState::Beelining || original_location == this->target_)
                {
                    this->target_ = hero->tile()->where();
                    changed = true;
                }
                this->ai_state_ = AiState::Beelining;
                continue;
            } 
            else if (this->ai_state_ != AiState::Beelining)
            {
                if (original_location.distance(this->home_) > HomeRange)
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
        default:
        case AiState::Wandering:
            // just wander around
            new_location = floor->choose_random(
                original_location.all_adjacent_locations(),
                shared_this);
            break;

        case AiState::Beelining:
            // head toward where the hero was
            // todo - replace with pathfinder
            new_location = floor->choose_random(
                original_location.closer_adjacent_locations(this->target_),
                shared_this);
            break;

        case AiState::Homing:
            // head toward home
            // todo - replace with pathfinder
            new_location = floor->choose_random(
                original_location.closer_adjacent_locations(this->home_),
                shared_this);
            break;
        }

        if (new_location != Location())
        {
            this->place(floor->tile(new_location));
        }
        return this->calculate_move_time(original_location);
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