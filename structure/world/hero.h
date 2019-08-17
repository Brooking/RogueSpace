#ifndef _hero_h_
#define _hero_h_

#include "uitokens.h"
#include "location.h"
#include "direction.h"
#include "thing_base.h"
#include "tile.h"

//
// Holds the player's avatar
//
class Hero : public ThingBase
{
public:
    Hero(Tile* tile = nullptr, int sight_range = 5);
    virtual ~Hero() {}

    // iThing: move (not used for heroes)
    virtual bool move();

    // where is this hero now
    Location where() const { return (this->tile_ == nullptr) ? Location(-1,-1) : this->tile_->where(); }

    // move the hero this direction
    bool move(Direction direction);

    // start moving the hero toward this location
    bool move_to(Location location);

    // how far can the hero see
    int sight_range() { return this->sight_range_; }

private:
    int sight_range_;
};

#endif // _hero_h_

