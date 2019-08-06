#ifndef _icon_h_
#define _icon_h_

#include <stdexcept>
#include <array>
#include <ncurses.h>
#include "rawcurses.h"
#include "uitokens.h"

//
// static container of character information
//
struct IconData
{
    constexpr IconData(UIToken token, int color_pair, unsigned long symbol) :
        token(token), color_pair(color_pair), symbol(symbol)
    {}

    UIToken token;
    int color_pair;
    unsigned long symbol;
};

static const std::array<IconData,(long unsigned int)UIToken::num_tokens> IconList 
{
    IconData(UIToken::none, COLOR_PAIR(1), ' '),
    IconData(UIToken::test, COLOR_PAIR(1), '?'),
    IconData(UIToken::bare_floor, COLOR_PAIR(1), RawCurses::BULLET),
    IconData(UIToken::wall, COLOR_PAIR(1), '+'),
    IconData(UIToken::hero, COLOR_PAIR(1), '@')
};

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

static const std::array<unsigned long,16> AdjacentWallList
{
    /* 0:none*/'+',
    /* 1:N   */RawCurses::WALL_NS,
    /* 2:E   */RawCurses::WALL_EW,
    /* 3:NE  */RawCurses::WALL_NE,
    /* 4:S   */RawCurses::WALL_NS,
    /* 5:NS  */RawCurses::WALL_NS,
    /* 6:SE  */RawCurses::WALL_SE,
    /* 7:NSE */RawCurses::WALL_NSE,
    /* 8:W   */RawCurses::WALL_EW,
    /* 9:NW  */RawCurses::WALL_NW,
    /*10:EW  */RawCurses::WALL_EW,
    /*11:NEW */RawCurses::WALL_NEW,
    /*12:SW  */RawCurses::WALL_SW,
    /*13:NSW */RawCurses::WALL_NSW,
    /*14:SEW */RawCurses::WALL_SEW,
    /*15:NSEW*/RawCurses::WALL_NSEW,
};

static const std::array<unsigned long,16> SimpleAdjacentWallList
{
    /* 0:none*/'?',
    /* 1:N   */'|',
    /* 2:E   */'-',
    /* 3:NE  */'+',
    /* 4:S   */'|',
    /* 5:NS  */'|',
    /* 6:ES  */'+',
    /* 7:NES */'+',
    /* 8:W   */'-',
    /* 9:NW  */'+',
    /*10:EW  */'-',
    /*11:NEW */'+',
    /*12:SW  */'+',
    /*13:NSW */'+',
    /*14:ESW */'+',
    /*15:NESW*/'+',
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
    int color_pair() { return this->color_pair_; }

    // the symbol to show
    unsigned long symbol() { return this->symbol_; }

private:
    UIToken token_;
    int color_pair_;
    unsigned long symbol_;
};

#endif // _icon_h_