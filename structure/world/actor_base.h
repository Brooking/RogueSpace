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
    static constexpr double sqrt2 = 1.41;

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
    unsigned int calculate_move_time(Location original)
    {
        int row_diff = std::abs(
            static_cast<int>(this->tile()->where().row()) - static_cast<int>(original.row()));
        int cell_diff = std::abs(
            static_cast<int>(this->tile()->where().cell()) - static_cast<int>(original.cell()));
        assert(row_diff < 2);
        assert(cell_diff < 2);
        if (row_diff > 0 && cell_diff > 0)
        {
            // diagonal move
            return static_cast<unsigned int>(this->move_time_ * sqrt2);
        }

        // orthogonal (or no) move
        return this->move_time_;
    }

protected:
    unsigned int move_time_;
};


#endif // _actor_base_h_
