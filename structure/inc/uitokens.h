#ifndef _uitokens_h_
#define _uitokens_h_

enum class UIToken
{
    none = 0,
    test,
    lit_floor,
    visible_floor,
    seen_floor,
    lit_wall,
    visible_wall,
    seen_wall,
    hero,
    rat,
    bee,
    dog,
    num_tokens
};

inline bool is_wall(UIToken token)
{ 
    return token == UIToken::lit_wall || 
           token == UIToken::visible_wall || 
           token == UIToken::seen_wall;
}


#endif // _uitokens_h_