#include "icon.h"
#include <stdexcept>
#include <array>
#include "io_constants.h"

//
// static container of character information
//
struct IconData
{
    constexpr IconData(UIToken token, int color_pair_index, unsigned long symbol) :
        token(token), color_pair_index(color_pair_index), symbol(symbol)
    {}

    UIToken token;
    int color_pair_index;
    unsigned long symbol;
};

//
// Table assigning display characters to tokens
//
static const std::array<IconData,(long unsigned int)UIToken::num_tokens> IconList 
{
    IconData(UIToken::none, 1, ' '),
    IconData(UIToken::test, 1, '?'),
    IconData(UIToken::bare_floor, 1, io::Character::BULLET),
    IconData(UIToken::wall, 1, '+'),
    IconData(UIToken::hero, 1, '@')
};

//
// Table giving wall shapes based on wall adjacencies
//
static const std::array<unsigned int,16> AdjacentWallList
{
    /* 0:none*/'+',
    /* 1:N   */io::Character::WALL_NS,
    /* 2:E   */io::Character::WALL_EW,
    /* 3:NE  */io::Character::WALL_NE,
    /* 4:S   */io::Character::WALL_NS,
    /* 5:NS  */io::Character::WALL_NS,
    /* 6:SE  */io::Character::WALL_SE,
    /* 7:NSE */io::Character::WALL_NSE,
    /* 8:W   */io::Character::WALL_EW,
    /* 9:NW  */io::Character::WALL_NW,
    /*10:EW  */io::Character::WALL_EW,
    /*11:NEW */io::Character::WALL_NEW,
    /*12:SW  */io::Character::WALL_SW,
    /*13:NSW */io::Character::WALL_NSW,
    /*14:SEW */io::Character::WALL_SEW,
    /*15:NSEW*/io::Character::WALL_NSEW,
};

Icon::Icon(UIToken token, unsigned int adjacency) : token_(token)
{
    if ((long unsigned int)token >= (long unsigned int)UIToken::num_tokens)
    {
        throw std::invalid_argument("token too large");
    }

    this->color_pair_index_ = IconList[(long unsigned int)token].color_pair_index;
    if (token != UIToken::wall)
    {
        this->symbol_ = IconList[(long unsigned int)token].symbol;
    }
    else
    {
        // walls' shapes rely on adjacent walls
        if (adjacency >= 16) 
        {
            throw std::invalid_argument("adjacency too large");
        }
        this->symbol_ = AdjacentWallList[adjacency];
    }
}
