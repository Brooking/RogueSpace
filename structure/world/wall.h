#ifndef _wall_h_
#define _wall_h_

#include <stdexcept>
#include "tile.h"
#include "uitokens.h"
#include "ithing.h"

class Wall : public iThing 
{
public:
    Wall(Tile* tile) : tile_(tile) 
    {
        if (this->tile_ == nullptr)
        {
            throw std::invalid_argument("Wall cannot be placed on a null tile");
        }
        if (this->tile_->num_things() > 0)
        {
            throw std::invalid_argument("Wall cannot be placed on a non-empty tile");
        }
        this->tile_->add(this);
    }

    virtual ~Wall() {}

    // iThing: return the ui token
    virtual UIToken token() const { return UIToken::wall; }

    // iThing: return the current tile
    virtual Tile* tile() const { return this->tile_; }

    // iThing: a wall does fill a tile
    virtual bool fills_tile() const { return true; }

    // iThing: walls are not centers
    virtual bool is_center() const { return false; }
    
    // iThing: walls don't move
    virtual bool move() { return false; }
    
private:
    Tile* tile_;
};

#endif // _wall.h_