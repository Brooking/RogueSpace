#ifndef _iactor_h_
#define _iactor_h_

#include <memory>
#include "content_size.h"
#include "direction.h"
#include "location.h"
#include "uitoken.h"

//
// interface for things that can act
//
class iActor
{
public:
    virtual ~iActor() = default;

    // Tell this thing to move
    virtual unsigned int move() = 0;

    // Tell this thing to move (and tell it which direction)
    virtual unsigned int move(Direction direction) = 0;

    // Tell the thing to move toward a destination
    virtual unsigned int move(Location destination) = 0;
};

#endif // _iactor_h_
