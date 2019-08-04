#ifndef _hero_h_
#define _hero_h_

#include "uitokens.h"
#include "location.h"
#include "direction.h"
#include "ithing.h"
#include "tile.h"

//
// Holds the player's avatar
//
class Hero : public iThing
{
public:
    Hero(Tile* tile = nullptr);
    virtual ~Hero() {}

    // iThing: return the ui token for this hero
    virtual UIToken token() const { return this->token_; }

    // iThing: return the hero's current tile
    virtual Tile* tile() const {return this->tile_;}

    // iThing: a hero does not fill the tile
    virtual bool fills_tile() const { return false; }

    // iThing: hero always centers
    virtual bool is_center() const { return true; }
    
    // where is this hero now
    Location where() const { return (this->tile_ == nullptr) ? Location(-1,-1) : this->tile_->where(); }

    // command stuff...
    // put the hero here (regardless of where he was)
    bool place(Tile* tile);

    // move the hero this direction
    bool move(Direction direction);

    // start moving the hero toward this location
    bool move_to(Location location);

private:
    UIToken token_;
    Tile* tile_;
};

#endif // _hero_h_

