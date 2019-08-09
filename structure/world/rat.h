#ifndef _rat_h_
#define _rat_h_

#include <cstdlib>
#include "uitokens.h"
#include "ithing.h"
#include "floor.h" // should be ifloor.h

class Rat : public iThing
{
public:
    Rat(Tile* tile) : tile_(tile) {}
    virtual ~Rat() {}

    // iThing: return the ui token for this hero
    virtual UIToken token() const { return UIToken::rat; }

    // iThing: return the rat's current tile
    virtual Tile* tile() const {return this->tile_;}

    // iThing: a rat does not fill the tile
    virtual bool fills_tile() const { return false; }

    // iThing: rat does not center
    virtual bool is_center() const { return false; }

    // iThing: do its move
    virtual bool move()
    {
        Floor* floor = const_cast<Floor*>(this->tile_->floor());

        Tile* newTile = nullptr;
        while (newTile == nullptr || newTile->is_full())
        {
            // random movement
            int delta_row = (rand() % 3) - 1;
            int delta_cell = (rand() % 3) - 1;
            Location location(
                this->tile_->where().row() + delta_row, 
                this->tile_->where().cell() + delta_cell);
            newTile = floor->tile(location);
        }

        this->tile_->remove(this);
        newTile->add(this);
        this->tile_ = newTile;
        return true;
    }

private:
    Tile* tile_;
};

#endif // _rat_h_