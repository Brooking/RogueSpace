#include "../world/ithing.h"

class iThingMock : public iThing
{
public:
    iThingMock(UIToken token, Tile* tile) : token_(token), tile_(tile) {}
    virtual ~iThingMock() {}

    virtual UIToken token() const { return this->token_; }
    virtual Tile* tile() const { return this->tile_; }
    virtual bool set_tile(Tile* tile) { this->tile_ = tile; return true; }

private:
    UIToken token_;
    Tile* tile_;
};
