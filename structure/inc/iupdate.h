#ifndef _iupdate_h_
#define _iupdate_h_

//
// the interface for the world to tell the ui that something has changed
//
class iUpdate
{
public:
    virtual ~iUpdate() {}
    virtual bool update(unsigned int row, unsigned int cell, bool center = false) = 0;
};
#endif // _iupdate_h_