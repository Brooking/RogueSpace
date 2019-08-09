#ifndef _rat_h_
#define _rat_h_

#include "monster_base.h"

//#include <cstdlib> // for rand()
#include "floor.h" // should be ifloor.h

class Rat : public MonsterBase
{
public:
    Rat(Tile* tile) : MonsterBase(tile, UIToken::rat) {}
    virtual ~Rat() {}

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
};

#endif // _rat_h_