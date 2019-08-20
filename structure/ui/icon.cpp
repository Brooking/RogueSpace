#include "icon.h"
#include <stdexcept>
#include <array>
#include "io_constants.h"

//
// static container of character information
//
struct IconData
{
    constexpr IconData(UIToken token, io::Color foreground, io::Color background, unsigned long symbol) :
        token(token), foreground_(foreground), background_(background), symbol(symbol)
    {}

    constexpr IconData(UIToken token, io::Color foreground, unsigned long symbol) :
        IconData(token, foreground, io::Color::BLACK, symbol)
    {}

    UIToken token;
    io::Color foreground_;
    io::Color background_;
    unsigned long symbol;
};

//
// Table assigning display characters to tokens
//
static const std::array<IconData,(long unsigned int)UIToken::num_tokens> IconList 
{
    IconData(UIToken::none, io::Color::BLACK, ' '),
    IconData(UIToken::test, io::Color::BRIGHT_YELLOW, '?'),
    IconData(UIToken::visible_floor, io::Color::WHITE, io::Character::BULLET),
    IconData(UIToken::seen_floor, io::Color::BRIGHT_BLACK, io::Character::BULLET),
    IconData(UIToken::visible_wall, io::Color::WHITE, '+'),
    IconData(UIToken::seen_wall, io::Color::BRIGHT_BLACK, '+'),
    IconData(UIToken::hero, io::Color::BRIGHT_CYAN, '@'),
    IconData(UIToken::rat, io::Color::BRIGHT_RED, 'r'),
    IconData(UIToken::bee, io::Color::BRIGHT_RED, 'b'),
    IconData(UIToken::dog, io::Color::BRIGHT_CYAN, 'd')
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

    this->foreground_color_ = IconList[(long unsigned int)token].foreground_;
    this->background_color_ = IconList[(long unsigned int)token].background_;
    if (is_wall(token))
     {
        // walls' shapes rely on adjacent walls
        if (adjacency >= 16) 
        {
            throw std::invalid_argument("adjacency too large");
        }
        this->symbol_ = AdjacentWallList[adjacency];
    }
    else
    {
        this->symbol_ = IconList[(long unsigned int)token].symbol;
    }
}
