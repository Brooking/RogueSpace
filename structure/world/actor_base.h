#ifndef _actor_base_h_
#define _actor_base_h_

#include <cmath> // for abs
#include <assert.h>
#include "iactor.h"
#include "thing_base.h"

//
// Base class for all actors
//
class ActorBase : public ThingBase, public iActor
{
public:

public:
    ActorBase(TokenType token_type, unsigned int move_time, bool center = false) : 
        ThingBase(token_type, ContentSize::large, center),
         move_time_(move_time)
    {}
    virtual ~ActorBase() = default;

    // iActor: directed move (most actors ignore this)
    virtual unsigned int move(Direction) override
    {
        throw std::invalid_argument("This type of actor can not be told what to do");
    }

protected:
    static constexpr double SquareRootOf2 = 1.41;

protected:
    // determine the cost of the move
    unsigned int calculate_move_time(Location original) const;

    // determine if a given move is diagonal
    bool is_diagonal_move(Location original) const;

protected:
    unsigned int move_time_;
};

#endif // _actor_base_h_
