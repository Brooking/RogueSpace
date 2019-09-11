#include "actor_base.h"

unsigned int ActorBase::calculate_move_time(Location original) const
{
    if (this->is_diagonal_move(original))
    {
        // diagonal move
        return static_cast<unsigned int>(this->move_time_ * ActorBase::SquareRootOf2);
    }

    // orthogonal (or no) move
    return this->move_time_;
}

bool ActorBase::is_diagonal_move(Location original) const
{
    int row_diff = std::abs(
        static_cast<int>(this->tile()->where().row()) - static_cast<int>(original.row()));
    int cell_diff = std::abs(
        static_cast<int>(this->tile()->where().cell()) - static_cast<int>(original.cell()));
    assert(row_diff < 2);
    assert(cell_diff < 2);
    return (row_diff > 0 && cell_diff > 0);
}