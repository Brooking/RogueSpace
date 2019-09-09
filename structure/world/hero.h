#ifndef _hero_h_
#define _hero_h_

#include <memory>
#include "actor_base.h"
#include "direction.h"
#include "location.h"
#include "tile.h"
#include "uitoken.h"

#ifndef PROTECTED_ACCESS
#define PROTECTED_ACCESS protected
#endif

//
// Holds the player's avatar
//
class Hero : public ActorBase
{
public:
    Hero(unsigned int sight_range = Hero::DefaultSightRange);
    virtual ~Hero() = default;

    // iActor: move (ironically, for the hero, this means stand still...)
    virtual unsigned int move() override;

    // iActor: move the hero this direction
    virtual unsigned int move(Direction direction) override;

    // iThing: place the hero (and update the floor's 'hero' value)
    virtual bool place(std::shared_ptr<Tile> tile) override;

    // where is this hero now
    Location where() const;

    // can the hero see this spot
    bool can_see(Location location);

    // can the hero see this tile
    bool can_see(const std::shared_ptr<Tile> tile);

    // can the hero be seen here from a given spot
    bool can_be_seen_from(Location seer, unsigned int sight_range);

    // switch from running to walking
    void toggle_run();

    // the hero is running
    bool is_running() { return this->running_; }

    unsigned int max_health() const { return 100; }
    unsigned int current_health() const { return 50; }
    unsigned int max_energy() const { return 100; }
    unsigned int current_energy() const { return 100; }
    unsigned int max_stamina() const { return this->max_stamina_; }
    unsigned int current_stamina() const { return this->current_stamina_; }

private:
    static const unsigned WalkTime = 200;
    static const unsigned RunTime = 100;
    static const unsigned int DefaultSightRange = 5;
    static const unsigned int DefaultMaxStamina = 100;
    static const unsigned int RunStaminaCost = 10;
    static const unsigned int WalkStaminaRecovery = 5;
    static const unsigned int RestStaminaRecovery = 10;

private:
    unsigned int sight_range_;
    unsigned int max_stamina_;
    unsigned int current_stamina_;
    bool running_;
};

#endif // _hero_h_

