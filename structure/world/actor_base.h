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

    unsigned int calculate_move_time(Location original)
    {
        if (this->is_diagonal_move(original))
        {
            // diagonal move
            return static_cast<unsigned int>(this->move_time_ * ActorBase::SquareRootOf2);
        }

        // orthogonal (or no) move
        return this->move_time_;
    }

    bool is_diagonal_move(Location original)
    {
       int row_diff = std::abs(
            static_cast<int>(this->tile()->where().row()) - static_cast<int>(original.row()));
        int cell_diff = std::abs(
            static_cast<int>(this->tile()->where().cell()) - static_cast<int>(original.cell()));
        assert(row_diff < 2);
        assert(cell_diff < 2);
        return (row_diff > 0 && cell_diff > 0);
    }

protected:
    unsigned int move_time_;
};


#endif // _actor_base_h_
