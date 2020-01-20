#ifndef _thing_base_h_
#define _thing_base_h_

#include "ithing.h"
#include "tile.h"

#ifndef PROTECTED_ACCESS
#define PROTECTED_ACCESS protected
#endif

// std::enable_shared_from_this has an accessible non-virtual destructor
#pragma GCC diagnostic ignored "-Wnon-virtual-dtor"

//
// a base class for all things
//
class ThingBase : public iThing, public std::enable_shared_from_this<iThing>
{
public:
    ThingBase(TokenType token_type, ContentSize content_size, bool center) : 
        tile_(), token_type_(token_type), content_size_(content_size), center_(center)
    {}
    virtual ~ThingBase() = default;

    // iThing: The tile that this thing is on
    virtual std::shared_ptr<Tile> tile() const override { return this->tile_.lock(); }

    // iThing: Get the lightweight token type
    virtual TokenType token_type() const override { return this->token_type_; }

    // iThing: How this thing should be displayed in the UI
    virtual UIToken token() const override;

    // iThing: This thing fills the tile
    virtual ContentSize content_size() const override { return this->content_size_; }

    // iThing: This thing is centered
    virtual bool is_center() const override { return this->center_; }

    // iThing: put the thing on the tile
    virtual bool place(std::shared_ptr<Tile> tile) override;

    // iThing: remove the thing from a tile
    virtual bool remove() override;

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
    std::weak_ptr<Tile> tile_;
    TokenType token_type_;
    ContentSize content_size_;
    bool center_;
};

#endif // _thing_base_h_
