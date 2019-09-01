#ifndef _wall_h_
#define _wall_h_

#include <stdexcept>
#include "thing_base.h"
#include "tile.h"
#include "uitokens.h"

class Wall : public ThingBase
{
public:
    Wall() : 
        ThingBase(UIToken::visible_wall, ContentSize::full, /*center*/false)
    {}

    virtual ~Wall() {}

    // iThing: return the ui token
    virtual UIToken token() const override
    { 
        return this->tile()->is_lit() ? UIToken::lit_wall :UIToken::visible_wall;
    }

    // iThing: walls don't move
    virtual bool move() override { return false; }
};

#endif // _wall.h_