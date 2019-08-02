#ifndef _icon_h_
#define _icon_h_

#include <stdexcept>
#include <array>
#include <ncurses.h>
#include "uitokens.h"

//
// static container of character information
//
struct IconData
{
    constexpr IconData(UIToken token, int color_pair, char symbol) :
        token(token), color_pair(color_pair), symbol(symbol)
    {}

    UIToken token;
    int color_pair;
    char symbol;
};

static const std::array<IconData,(long unsigned int)UIToken::num_tokens> IconList 
{
    IconData(UIToken::none, COLOR_PAIR(1), ' '),
    IconData(UIToken::test, COLOR_PAIR(1), '?'),
    IconData(UIToken::bare_floor, COLOR_PAIR(1), '.'),
    IconData(UIToken::wall, COLOR_PAIR(1), '+'),
    IconData(UIToken::hero, COLOR_PAIR(1), '@')
};

//
// A container for a displayable ui icon
//

// todo, should be table driven
class Icon
{
public:
    Icon(UIToken token);
    virtual ~Icon() {}

    // the display color pair
    int color_pair() { return this->color_pair_; }

    // the symbol to show
    char symbol() { return this->symbol_; }

private:
    UIToken token_;
    int color_pair_;
    char symbol_;
};

#endif // _icon_h_