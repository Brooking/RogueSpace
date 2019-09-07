#include <stdexcept>
#include "uitoken.h"

static const bool default_visible = false;
static const bool default_lit = false;
static const bool default_seen = false;

UIToken::UIToken(WallType wall_type, bool visible, bool seen, bool lit) :
    token_type_(TokenType::wall), 
    visible_(visible),
    seen_(seen),
    lit_(lit),
    wall_type_(wall_type)
{
    this->verify_visible_seen();
}

UIToken::UIToken(WallType wall_type) :
    token_type_(TokenType::wall), 
    visible_(default_visible),
    seen_(default_seen),
    lit_(default_lit),
    wall_type_(wall_type)
{
    this->verify_visible_seen();
}

UIToken::UIToken(TokenType token_type, bool visible, bool seen, bool lit) :
    token_type_(token_type), 
    visible_(visible),
    seen_(seen),
    lit_(lit),
    wall_type_(WallType::pillar)
{
    this->verify_visible_seen();
    this->verify_non_wall();
}

UIToken::UIToken(TokenType token_type) :
    token_type_(token_type), 
    visible_(default_visible),
    seen_(default_seen),
    lit_(default_lit),
    wall_type_(WallType::pillar)
{
    this->verify_visible_seen();
    this->verify_non_wall();
}

UIToken::UIToken() :
    token_type_(TokenType::none), 
    visible_(default_visible),
    seen_(default_seen),
    lit_(default_lit),
    wall_type_(WallType::pillar)
{
    this->verify_visible_seen();
    this->verify_non_wall();
}

void UIToken::verify_visible_seen() const
{
    if (this->is_visible() && !this->has_been_seen())
    {
        // if it is currently visible, then it has been seen
        // this state indicates an internal inconsistency
        throw std::invalid_argument("if a UItoken is visible, then it has been seen");
    }
}

void UIToken::verify_non_wall() const
{
    if (this->token_type() == TokenType::wall)
    {
        // walls have their own constructor
        throw std::invalid_argument("walls must use the wall constructor");
    }
}