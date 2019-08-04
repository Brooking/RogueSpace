#ifndef _iupdate_h_
#define _iupdate_h_

#include "location.h"

//
// the interface for thew world to tell the ui that something has changed
//
class iUpdate
{
public:
    virtual bool update(Location location, bool center = false) = 0;
};
#endif // _iupdate_h_