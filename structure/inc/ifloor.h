#ifndef _ifloor_h_
#define _ifloor_h_

#include "uitokens.h"
#include "iupdate.h"

//
// An interface to communicate visuals to the ui
//
class iFloor
{
public:
    // register an update callback
    virtual bool register_update(iUpdate* update_interface) = 0;

    // the height of the floor (number of rows)
    virtual int height() = 0;

    // the width of the floor (number of cells per row)
    virtual int width() = 0;

    // the current ui token at the given location
    virtual UIToken token(int row, int cell) = 0;

    // the visibility of the given location
    virtual bool is_visible(int row, int cell) = 0;
};

#endif // _ifloor_h_