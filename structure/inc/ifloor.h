#ifndef _ifloor_h_
#define _ifloor_h_

#include <memory>
#include "iupdate.h"
#include "uitoken.h"

//
// An interface to communicate visuals to the ui
//
class iFloor
{
public:
    virtual ~iFloor() = default;

    // register an update callback
    virtual bool register_update(std::shared_ptr<iUpdate> update_interface) = 0;

    // the height of the floor (number of rows)
    virtual unsigned int height() const = 0;

    // the width of the floor (number of cells per row)
    virtual unsigned int width() const = 0;

    // the current ui token at the given location
    virtual UIToken token(unsigned int row, unsigned int cell) const = 0;
};

#endif // _ifloor_h_