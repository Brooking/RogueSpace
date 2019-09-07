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
    IconData(
        TokenType token_type, 
        unsigned int symbol, 
        io::Color foreground_visible, 
        io::Color foreground_lit = io::Color::BLACK, 
        io::Color foreground_seen = io::Color::BLACK, 
        io::Color background = io::Color::BLACK) 
    :
        token_type_(token_type),
        foreground_visible_(foreground_visible),
        foreground_lit_(foreground_lit),
        foreground_seen_(foreground_seen),
        background_(background),
        symbol_(symbol)
    {
        if (this->foreground_lit_ == io::Color::BLACK)
        {
            // those tokens that do not specify a lit color will use their visible color
            this->foreground_lit_ = this->foreground_visible_;
        }
    }

    IconData(
        TokenType token_type, 
        io::Character symbol, 
        io::Color foreground_visible, 
        io::Color foreground_lit = io::Color::WHITE, 
        io::Color foreground_seen = io::Color::BLACK, 
        io::Color background = io::Color::BLACK) 
    :
        token_type_(token_type),
        foreground_visible_(foreground_visible),
        foreground_lit_(foreground_lit),
        foreground_seen_(foreground_seen),
        background_(background),
        symbol_(static_cast<unsigned int>(symbol))
    {
        if (this->foreground_lit_ == io::Color::BLACK)
        {
            // those tokens that do not specify a lit color will use their visible color
            this->foreground_lit_ = this->foreground_visible_;
        }
    }

    TokenType token_type() const { return this->token_type_; }
    io::Color foreground_visible() const { return this->foreground_visible_; }
    io::Color foreground_lit() const { return this->foreground_lit_; }
    io::Color foreground_seen() const { return this->foreground_seen_; }
    io::Color background() const { return this->background_; }
    unsigned int symbol() const { return this->symbol_; }

private:
    TokenType token_type_;
    io::Color foreground_visible_;
    io::Color foreground_lit_;
    io::Color foreground_seen_;
    io::Color background_;
    unsigned int symbol_;
};

//
// Table assigning display characters to tokens
//
static const std::array<IconData,static_cast<unsigned int>(TokenType::num_tokens)> IconList 
{
    IconData(TokenType::none, ' ', io::Color::BLACK),
    IconData(TokenType::test, '?', io::Color::BRIGHT_MAGENTA),
    IconData(TokenType::floor, io::Character::BULLET, 
        /*visible*/io::Color::WHITE,
        /*lit*/io::Color::YELLOW,
        /*seen*/io::Color::BRIGHT_BLACK),
    IconData(TokenType::wall, '+',
        /*visible*/io::Color::WHITE,
        /*lit*/io::Color::YELLOW,
        /*seen*/io::Color::BRIGHT_BLACK),
    IconData(TokenType::hero, '@', io::Color::BRIGHT_CYAN),
    IconData(TokenType::rat, 'r', io::Color::BRIGHT_RED),
    IconData(TokenType::bee, 'b', io::Color::BRIGHT_RED),
    IconData(TokenType::dog, 'd', io::Color::BRIGHT_CYAN)
};

//
// Table giving wall icons
//
static const std::array<unsigned int, static_cast<int>(WallType::count)> WallIcons
{
    /* 0:pillar*/'+',
    /* 1:n     */static_cast<unsigned int>(io::Character::WALL_NS),
    /* 2:e     */static_cast<unsigned int>(io::Character::WALL_WE),
    /* 3:ne    */static_cast<unsigned int>(io::Character::WALL_NE),
    /* 4:s     */static_cast<unsigned int>(io::Character::WALL_NS),
    /* 5:ns    */static_cast<unsigned int>(io::Character::WALL_NS),
    /* 6:se    */static_cast<unsigned int>(io::Character::WALL_SE),
    /* 7:nse   */static_cast<unsigned int>(io::Character::WALL_NSE),
    /* 8:w     */static_cast<unsigned int>(io::Character::WALL_WE),
    /* 9:nw    */static_cast<unsigned int>(io::Character::WALL_NW),
    /*10:we    */static_cast<unsigned int>(io::Character::WALL_WE),
    /*11:nwe   */static_cast<unsigned int>(io::Character::WALL_NWE),
    /*12:sw    */static_cast<unsigned int>(io::Character::WALL_SW),
    /*13:nsw   */static_cast<unsigned int>(io::Character::WALL_NSW),
    /*14:swe   */static_cast<unsigned int>(io::Character::WALL_SWE),
    /*15:nswe  */static_cast<unsigned int>(io::Character::WALL_NSWE)
};

Icon::Icon(UIToken token) : 
    token_(token), foreground_color_(), background_color_(), symbol_()
{
    long unsigned int token_type_int = static_cast<long unsigned int>(token.token_type());
    if ( token_type_int >= static_cast<long unsigned int>(TokenType::num_tokens))
    {
        throw std::invalid_argument("token type too large");
    }

    // <clip>
    // We always set a character, hiddenness is created via color manipulation
    if (token.token_type() == TokenType::wall)
    {
        // this is a wall
        this->symbol_ = WallIcons[static_cast<long unsigned int>(token.wall_type())];
    }
    else
    {
        // non walls are more straighforward
        this->symbol_ = IconList[token_type_int].symbol();
    }

    // set the background color
    this->background_color_ = IconList[token_type_int].background();
    assert(
        static_cast<unsigned int>(this->background_color_) <= 
        static_cast<unsigned int>(io::Color::WHITE));

    // set the foreground color
    if (token.is_visible())
    {
        if (token.is_lit())
        {
            // visible and lit
            this->foreground_color_ = IconList[token_type_int].foreground_lit();
        }
        else
        {
            // visible and unlit
            this->foreground_color_ = IconList[token_type_int].foreground_visible();
        }
    }
    else
    {
        if (token.has_been_seen())
        {
            // not visible but seen
            this->foreground_color_ = IconList[token_type_int].foreground_seen();
        }
        else
        {
            // neither visible nor seen
            this->foreground_color_ = io::Color::BLACK;
        }
    }

    // // set the symbol
    // if (!token.is_visible() && !token.has_been_seen())
    // {
    //     // this spot has never been seen (take care of it here!)
    //     token_type_int = static_cast<long unsigned int>(TokenType::none);
    //     this->symbol_ = IconList[token_type_int].symbol();
    //     this->background_color_ = IconList[token_type_int].background();
    //     this->foreground_color_ = IconList[token_type_int].background(); // yes, background!
    //     return;
    // }

    // if (!token.is_visible() && !token.has_been_seen())
    // {
    //     // this spot has never been seen (take care of it here!)
    //     token_type_int = static_cast<long unsigned int>(TokenType::none);
    //     this->symbol_ = IconList[token_type_int].symbol();
    //     this->background_color_ = IconList[token_type_int].background();
    //     this->foreground_color_ = IconList[token_type_int].background(); // yes, background!
    //     return;
    // }

    // // visible or has been seen
    // if (token.token_type() == TokenType::wall)
    // {
    //     // this is a wall
    //     this->symbol_ = WallIcons[static_cast<long unsigned int>(token.wall_type())];
    // }
    // else
    // {
    //     // non walls are more straighforward
    //     this->symbol_ = IconList[token_type_int].symbol();
    // }

    

    // // set the background color
    // this->background_color_ = IconList[token_type_int].background();
    // assert(
    //     static_cast<unsigned int>(this->background_color_) <= 
    //     static_cast<unsigned int>(io::Color::WHITE));

    // // set the foreground color
    // if (token.is_lit())
    // {
    //     this->foreground_color_ = IconList[token_type_int].foreground_lit();
    // }
    // else if (token.is_visible())
    // {
    //     this->foreground_color_ = IconList[token_type_int].foreground_visible();
    // }
    // else if (token.has_been_seen())
    // {
    //     this->foreground_color_ = IconList[token_type_int].foreground_seen();
    // }
    // else
    // {
    //     this->foreground_color_ = io::Color::BLACK;
    // }        
}
