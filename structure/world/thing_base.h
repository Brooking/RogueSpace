#ifndef _thing_base_h_
#define _thing_base_h_

#include "ithing.h"
#include "tile.h"

#ifndef PROTECTED_ACCESS
#define PROTECTED_ACCESS protected
#endif

class ThingBase : public iThing, public std::enable_shared_from_this<iThing>
{
public:
    ThingBase(UIToken token, ContentSize content_size, bool center) : 
        tile_(nullptr), token_(token), content_size_(content_size), center_(center)
    {}
    virtual ~ThingBase() {}

    // The tile that this thing is on
    virtual std::shared_ptr<Tile> tile() const { return this->tile_; }

    // How this thing should be displayed in the UI
    virtual UIToken token() const { return this->token_; }

    // This thing fills the tile
    virtual ContentSize content_size() const { return this->content_size_; }

    // This thing is centered
    virtual bool is_center() const { return this->center_; }

    // put the thing on the tile
    virtual bool place(std::shared_ptr<Tile> tile)
    {
        if (tile != nullptr && tile->there_is_room(this->shared_from_this()))
        {
            this->remove();
            tile->add(this->shared_from_this());
            this->tile_ = tile;
            return true;
        }

        return false;
    }

    // remove the thing from a tile
    virtual bool remove()
    {
        if (this->tile_ != nullptr)
        {
            this->tile_->remove(this->shared_from_this());
            this->tile_ = nullptr;
        }

        return true;
    }

PROTECTED_ACCESS:
    // A worker to do the magic of getting a shared pointer
    // to the derived class when ThingBase is where the
    // shared from this functionality is located
    template<class derived>
    std::shared_ptr<derived> derived_shared_from_this()
    {
        return std::dynamic_pointer_cast<derived>(ThingBase::shared_from_this());
    }

protected:
    std::shared_ptr<Tile> tile_;
    UIToken token_;
    ContentSize content_size_;
    bool center_;    
};

#endif // _thing_base_h_
