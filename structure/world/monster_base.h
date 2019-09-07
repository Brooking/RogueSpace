#ifndef _monster_base_h_
#define _monster_base_h_

#include "ithing.h"

class MonsterBase : public ThingBase
{
public:
    MonsterBase(TokenType token_type) : 
        ThingBase(token_type, ContentSize::large, /*center*/false) {}
    virtual ~MonsterBase() {}
};


#endif // _monster_base_h_
