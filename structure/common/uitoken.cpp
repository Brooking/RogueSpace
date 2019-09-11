#include <stdexcept>
#include "uitoken.h"

UIToken::UIToken(WallType wall_type, bool visible, bool remembered, bool lit) :
    token_type_(TokenType::wall), 
    visible_(visible),
    remembered_(remembered),
    lit_(lit),
    wall_type_(wall_type)
{}

UIToken::UIToken(WallType wall_type) :
    token_type_(TokenType::wall), 
    visible_(UIToken::DefaultVisible),
    remembered_(UIToken::DefaultRemembered),
    lit_(UIToken::DefaultLit),
    wall_type_(wall_type)
{}

UIToken::UIToken(TokenType token_type, bool visible, bool remembered, bool lit) :
    token_type_(token_type), 
    visible_(visible),
    remembered_(remembered),
    lit_(lit),
    wall_type_(WallType::pillar)
{
    this->verify_non_wall();
}

UIToken::UIToken(TokenType token_type) :
    token_type_(token_type), 
    visible_(UIToken::DefaultVisible),
    remembered_(UIToken::DefaultRemembered),
    lit_(UIToken::DefaultLit),
    wall_type_(WallType::pillar)
{
    this->verify_non_wall();
}

UIToken::UIToken() :
    token_type_(TokenType::none), 
    visible_(UIToken::DefaultVisible),
    remembered_(UIToken::DefaultRemembered),
    lit_(UIToken::DefaultLit),
    wall_type_(WallType::pillar)
{
    this->verify_non_wall();
}

void UIToken::verify_non_wall() const
{
    if (this->token_type() == TokenType::wall)
    {
        // walls have their own constructor
        throw std::invalid_argument("walls must use the wall constructor");
    }
}