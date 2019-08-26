#ifndef _imap_h_
#define _imap_h_

#include<bits/stdc++.h>
typedef unsigned int uint;

//
// An interface for shadow casting and dijksta graphs to use
// to interact with the floor 
//
class iMap {
    public:
        // Set the los of the cell at the given position.
        virtual void set_los(uint x, uint y, uint range_squared) = 0;

        // Return the width of the map.
        virtual uint get_width() const = 0;

        // Return the height of the map.
        virtual uint get_height() const = 0;

        // Return whether the given position holds an opaque cell.
        virtual bool is_opaque(uint x, uint y) const = 0;
};

#endif // _imap_h_
