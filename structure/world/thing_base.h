#ifndef _thing_base_h_
#define _thing_base_h_

#include "ithing.h"
#include "tile.h"

class ThingBase : public iThing
{
public:
    ThingBase(Tile* tile, UIToken token, ContentSize content_size, bool center) : 
        tile_(tile), token_(token), content_size_(content_size), center_(center)
    {
        this->place(this->tile_);
    }
    virtual ~ThingBase() {}

    // The tile that this thing is on
    virtual Tile* tile() const { return this->tile_; }

    // How this thing should be displayed in the UI
    virtual UIToken token() const { return this->token_; }

    // This thing fills the tile
    virtual ContentSize content_size() const { return this->content_size_; }

    // This thing is centered
    virtual bool is_center() const { return this->center_; }

    // put the thing on the tile
    virtual bool place(Tile* tile)
    {
        if (tile != nullptr && tile->there_is_room(this))
        {
            if (this->tile_ != nullptr)
            {
                this->tile_->remove(this);
                this->tile_ = nullptr;
            }
            tile->add(this);
            this->tile_ = tile;
            return true;
        }

        return false;
    }

protected:
    Tile* tile_;
    UIToken token_;
    ContentSize content_size_;
    bool center_;    
};

#endif // _thing_base_h_
