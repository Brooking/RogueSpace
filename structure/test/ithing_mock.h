#include "ithing.h"

class iThingMock : public iThing
{
public:
    iThingMock(UIToken token, Tile* tile, ContentSize size = ContentSize::small, bool center = false) : 
        token_(token), tile_(tile), content_size_(size), center_(center)
    {}
    virtual ~iThingMock() {}

    // iThing
    virtual UIToken token() const { return this->token_; }
    virtual Tile* tile() const { return this->tile_; }
    virtual ContentSize content_size() const { return this->content_size_; }
    virtual bool is_center() const { return this->center_; }
    virtual bool move() { return true; }

private:
    UIToken token_;
    Tile* tile_;
    ContentSize content_size_;
    bool center_;
};
