#ifndef _ifov_h_
#define _ifov_h_

// 
// The interface for conclusions from field-of-view calculations
//
class iFov
{
public:
    virtual ~iFov() = default;

    // Set this spot to be in fov
    virtual void set_fov(unsigned int row, unsigned int cell, unsigned int distance) = 0;

    // This spot is in fov
    virtual unsigned int get_fov(unsigned int row, unsigned int cell) = 0;
};

#endif // _ifov_h_
