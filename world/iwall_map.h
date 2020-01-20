#ifndef _iwall_map_h_
#define _iwall_map_h_

//#include<bits/stdc++.h>

//
// An interface for shadow casting and dijksta graphs to use
// to interact with the floor 
//
class iWallMap 
{
    public:
        virtual ~iWallMap() = default;

        // Return the width of the map.
        virtual unsigned int width() const = 0;

        // Return the height of the map.
        virtual unsigned int height() const = 0;

        // Return whether the given position holds a wall.
        virtual bool is_opaque(unsigned int row, unsigned int cell) const = 0;

        // Set a wall in a position
        virtual void set_opaque(unsigned int row, unsigned int cell, bool opaque) = 0;
};

#endif // _iwall_map_h_
