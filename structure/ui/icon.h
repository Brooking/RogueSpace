#ifndef _icon_h_
#define _icon_h_

#include "uitokens.h"

//
// Adjacency informaion (used in drawing walls)
//
enum AdjacentWallBits
{
    North = 0,
    East = 1,
    South = 2,
    West = 3
};

//
// A container for a displayable ui icon
//
class Icon
{
public:
    Icon(UIToken token, unsigned int adjacency = 0);
    virtual ~Icon() {}

    // the display color pair
    int color_pair_index() { return this->color_pair_index_; }

    // the symbol to show
    unsigned long symbol() { return this->symbol_; }

private:
    UIToken token_;
    int color_pair_index_;
    unsigned long symbol_;
};

#endif // _icon_h_