#include "ithing.h"

class iThingMock : public iThing
{
public:
    iThingMock(UIToken token, Tile* tile, bool fills = false, bool center = false) : 
        token_(token), tile_(tile), fills_(fills), center_(center)
    {}
    virtual ~iThingMock() {}

    // iThing
    virtual UIToken token() const { return this->token_; }
    virtual Tile* tile() const { return this->tile_; }
    virtual bool fills_tile() const { return this->fills_; }
    virtual bool is_center() const { return this->center_; }

private:
    UIToken token_;
    Tile* tile_;
    bool fills_;
    bool center_;
};
