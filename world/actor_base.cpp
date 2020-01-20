#include "actor_base.h"
#include "dijkstra.h"
#include "floor.h"
#include "ifloor.h"
#include "safe_math.h"

unsigned int ActorBase::move(Location destination)
{
    std::shared_ptr<Tile> tile = this->tile();
    std::shared_ptr<Floor> floor = tile->floor();
    std::shared_ptr<Tile> destination_tile = floor->tile(destination);
    bool diagonal;

    if (tile->where().is_adjacent(destination, diagonal))
    {
        // this is where we add attacking logic
        // todo: return 0 to allow actor to attack
        return this->move_time_;
    }

    const std::shared_ptr<std::vector<std::vector<unsigned int>>>& dmap = tile->get_dmap();
    Location next = this->next_step(dmap);
    if (next == Location())
    {
        // a move is not indicated
        // wait...
        return this->move_time_;
    }

    // move this actor
    this->place(destination_tile);
    return this->calculate_move_time(tile->where());
}

Location ActorBase::next_step(const std::shared_ptr<std::vector<std::vector<unsigned int>>>& dmap)
{
    Location here = this->tile()->where();
    std::vector<std::vector<unsigned int>>* map = dmap.get(); // todo - remove this
    unsigned int current_distance = (*map)[here.row()][here.cell()];
    std::vector<Location> next_locations;

    for (unsigned int i = 0; i < 8; i++)
    {
        unsigned int row = SafeMath::Add(here.row(), Dijkstra::Neighbors[i].first);
        unsigned int cell = SafeMath::Add(here.cell(), Dijkstra::Neighbors[i].second);
        if (row >= static_cast<unsigned int>((*map).size()) || 
            cell >= static_cast<unsigned int>((*map)[0].size()))
        {
            // off the map
            continue;
        }
        unsigned int new_distance = (*map)[row][cell];
        if (new_distance == INT_MAX)
        {
            // wall
            continue;
        }

        if (new_distance < current_distance)
        {
            // found a next step
            // assert(new_distance == current_distance - 1); todo - assert for orth/diag
            next_locations.push_back(Location(row, cell));
        }
    }

    if (next_locations.size() == 0)
    {
        // could not find a next step
        return Location();
    }
    std::sort(next_locations.begin(),next_locations.end(),
        []( Location a,  Location b) { return a < b; }
    );

    std::shared_ptr<Floor> floor = this->tile_.lock()->floor();
    for (unsigned int i = 0; i < next_locations.size(); i++)
    {
        if (floor->tile(next_locations[i])->there_is_room(this->shared_from_this()))
        {
            return next_locations[i];
        }
    }

    return Location();
}


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
    bool diagonal = false;
    if (this->tile()->where().is_adjacent(original, diagonal))
    {
        return diagonal;
    }
    return false;
}

