#ifndef _hero_h_
#define _hero_h_

#include "../inc/uitokens.h"
#include "../inc/location.h"
#include "../inc/direction.h"
#include "ithing.h"
#include "tile.h"

//
// Holds the player's avatar
//
class Hero : public iThing
{
public:
    Hero(Tile* tile) : token_(UIToken::hero), tile_(tile) {}
    virtual ~Hero() {}

    // iThing
    virtual UIToken token() const { return this->token_; }
    virtual Tile* tile() const {return this->tile_;}
    virtual bool set_tile(Tile* tile) { this->tile_ = tile; return true; }
    
    Location where() const { return (this->tile_ == nullptr) ? Location(-1,-1) : this->tile_->where(); }

    // command stuff
    bool move(Direction direction);
    bool move_to(Location location);

private:
    UIToken token_;
    Tile* tile_;
};

#endif // _hero_h_

