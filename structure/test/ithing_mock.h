#include "ithing.h"

class iThingMock : public iThing
{
public:
    iThingMock(UIToken token, Tile* tile, bool fills = false) : token_(token), tile_(tile), fills_(fills) {}
    virtual ~iThingMock() {}

    virtual UIToken token() const { return this->token_; }
    virtual Tile* tile() const { return this->tile_; }
    virtual bool fills_tile() const { return this->fills_; }

private:
    UIToken token_;
    Tile* tile_;
    bool fills_;
};
