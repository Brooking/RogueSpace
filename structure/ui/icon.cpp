#include <array>
#include <stdexcept>
#include <assert.h>
#include "icon.h"
#include "io_constants.h"

//
// static container of character information
//
class IconData
{
public:
    constexpr IconData(
        UIToken token, 
        unsigned long symbol, 
        io::Color foreground, 
        io::Color background = io::Color::BLACK) 
    :
        token_(token), foreground_(foreground), background_(background), symbol_(symbol)
    {}

    constexpr IconData(
        UIToken token, 
        io::Character symbol, 
        io::Color foreground, 
        io::Color background = io::Color::BLACK) 
    :
        token_(token), foreground_(foreground), background_(background), symbol_(static_cast<unsigned int>(symbol))
    {}

    UIToken token() const { return this->token_; }
    io::Color foreground() const { return this->foreground_; }
    io::Color background() const { return this->background_; }
    unsigned long symbol() const { return this->symbol_; }

private:
    UIToken token_;
    io::Color foreground_;
    io::Color background_;
    unsigned long symbol_;
};

//
// Table assigning display characters to tokens
//
static const std::array<IconData,static_cast<unsigned int>(UIToken::num_tokens)> IconList 
{
    IconData(UIToken::none, ' ', io::Color::BLACK),
    IconData(UIToken::test, '?', io::Color::BRIGHT_YELLOW),
    IconData(UIToken::lit_floor, io::Character::BULLET, io::Color::YELLOW),
    IconData(UIToken::visible_floor, io::Character::BULLET, io::Color::WHITE),
    IconData(UIToken::seen_floor, io::Character::BULLET, io::Color::BRIGHT_BLACK),
    IconData(UIToken::lit_wall, '+', io::Color::YELLOW),
    IconData(UIToken::visible_wall, '+', io::Color::WHITE),
    IconData(UIToken::seen_wall, '+', io::Color::BRIGHT_BLACK),
    IconData(UIToken::hero, '@', io::Color::BRIGHT_CYAN),
    IconData(UIToken::rat, 'r', io::Color::BRIGHT_RED),
    IconData(UIToken::bee, 'b', io::Color::BRIGHT_RED),
    IconData(UIToken::dog, 'd', io::Color::BRIGHT_CYAN)
};

//
// Table giving wall shapes based on wall adjacencies
//
static const std::array<unsigned int,16> AdjacentWallList
{
    /* 0:none*/'+',
    /* 1:N   */static_cast<unsigned int>(io::Character::WALL_NS),
    /* 2:E   */static_cast<unsigned int>(io::Character::WALL_EW),
    /* 3:NE  */static_cast<unsigned int>(io::Character::WALL_NE),
    /* 4:S   */static_cast<unsigned int>(io::Character::WALL_NS),
    /* 5:NS  */static_cast<unsigned int>(io::Character::WALL_NS),
    /* 6:SE  */static_cast<unsigned int>(io::Character::WALL_SE),
    /* 7:NSE */static_cast<unsigned int>(io::Character::WALL_NSE),
    /* 8:W   */static_cast<unsigned int>(io::Character::WALL_EW),
    /* 9:NW  */static_cast<unsigned int>(io::Character::WALL_NW),
    /*10:EW  */static_cast<unsigned int>(io::Character::WALL_EW),
    /*11:NEW */static_cast<unsigned int>(io::Character::WALL_NEW),
    /*12:SW  */static_cast<unsigned int>(io::Character::WALL_SW),
    /*13:NSW */static_cast<unsigned int>(io::Character::WALL_NSW),
    /*14:SEW */static_cast<unsigned int>(io::Character::WALL_SEW),
    /*15:NSEW*/static_cast<unsigned int>(io::Character::WALL_NSEW)
};

Icon::Icon(UIToken token, unsigned int adjacency) : token_(token)
{
    if ((long unsigned int)token >= (long unsigned int)UIToken::num_tokens)
    {
        throw std::invalid_argument("token too large");
    }

    this->foreground_color_ = IconList[(long unsigned int)token].foreground();
    this->background_color_ = IconList[(long unsigned int)token].background();
    assert(static_cast<unsigned int>(this->background_color_) <= static_cast<unsigned int>(io::Color::WHITE));

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
        this->symbol_ = IconList[(long unsigned int)token].symbol();
    }
}
