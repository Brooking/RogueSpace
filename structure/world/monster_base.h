#ifndef _monster_base_h_
#define _monster_base_h_

#include "ithing.h"

class MonsterBase : public iThing
{
public:
    MonsterBase(Tile* tile, UIToken token) : tile_(tile), token_(token) {}
    virtual ~MonsterBase() {}

    // iThing: return the ui token for this monster
    virtual UIToken token() const { return this->token_; }

    // iThing: return the monster's current tile
    virtual Tile* tile() const { return this->tile_; }

    // iThing: a monster does not fill the tile
    virtual bool fills_tile() const { return false; }

    // iThing: monster does not center
    virtual bool is_center() const { return false; }

    // iThing: do its move
    virtual bool move() = 0;

protected:
    Tile* tile_;
    UIToken token_;
};


#endif // _monster_base_h_
