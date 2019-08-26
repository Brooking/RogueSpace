#ifndef _hero_h_
#define _hero_h_

#include <memory>
#include "uitokens.h"
#include "location.h"
#include "direction.h"
#include "thing_base.h"
#include "tile.h"

#ifndef PROTECTED_ACCESS
#define PROTECTED_ACCESS protected
#endif

//
// Holds the player's avatar
//
class Hero : public ThingBase
{
public:
    Hero(int sight_range = 5);
    virtual ~Hero() {}

    // iThing: move (not used for heroes)
    virtual bool move() override;

    // iThing: place the hero (and update the floor's 'hero' value)
    virtual bool place(std::shared_ptr<Tile> tile) override;

    // where is this hero now
    Location where() const { return (this->tile_ == nullptr) ? Location() : this->tile_->where(); }

    // move the hero this direction
    bool move(Direction direction);

    // can the hero see this spot
    bool can_see(Location location);

    // can the hero see this tile
    bool can_see(const std::shared_ptr<Tile> tile);

    // can the hero be seen here from a given spot
    bool can_be_seen_from(Location seer, int sight_range);

private:
    int sight_range_;
};

#endif // _hero_h_

