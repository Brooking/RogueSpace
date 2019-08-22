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
    Hero(std::shared_ptr<Tile> tile = nullptr, int sight_range = 5);
    virtual ~Hero() {}

    // iThing: move (not used for heroes)
    virtual bool move();

    // where is this hero now
    Location where() const { return (this->tile_ == nullptr) ? Location(-1,-1) : this->tile_->where(); }

    // move the hero this direction
    bool move(Direction direction);

    // can the hero see this spot
    bool can_see(Location location);

    // can the hero see this tile
    bool can_see(const std::shared_ptr<Tile> tile);

PROTECTED_ACCESS:

private:
    int sight_range_;
};

#endif // _hero_h_

