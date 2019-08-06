#include "icon.h"

Icon::Icon(UIToken token, unsigned int adjacency) : token_(token)
{
    if ((long unsigned int)token >= (long unsigned int)UIToken::num_tokens)
    {
        throw std::invalid_argument("token too large");
    }

    this->color_pair_ = IconList[(long unsigned int)token].color_pair;
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
