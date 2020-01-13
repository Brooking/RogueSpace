#ifndef _content_size_h_
#define _content_size_h_

#include "assert.h"

enum class ContentSize
{
    // nothing
    empty,

    // lots of these can be on a tile
    small,

    // only one of these can be on a tile
    // (along with many smalls)
    large,

    // must be alone on the tile
    full
};

#endif // _content_size_h_