#include "icon.h"

Icon::Icon(UIToken token) : token_(token)
{
    if ((long unsigned int)token >= (long unsigned int)UIToken::num_tokens)
    {
        throw std::invalid_argument("token too large");
    }

    if (token == UIToken::wall)
    {
        
    }
    this->color_pair_ = IconList[(long unsigned int)token].color_pair;
    this->symbol_ = IconList[(long unsigned int)token].symbol;
}
