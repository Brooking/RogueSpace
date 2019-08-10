#ifndef _rat_h_
#define _rat_h_

#include "monster_base.h"
#include "euclid.h"

//#include <cstdlib> // for rand()
#include "floor.h" // should be ifloor.h

class Rat : public MonsterBase
{
public:
    Rat(Tile* tile) : MonsterBase(tile, UIToken::rat) {}
    virtual ~Rat() {}

    // iThing: do it's move
    virtual bool move()
    {
        Floor* floor = const_cast<Floor*>(this->tile_->floor());
        Location hero_location = floor->hero()->where();
        Tile* newTile = nullptr;

        // move closer or stand still
        std::vector<Location> closer_locations = 
            euclid::closer_adjacent_locations(hero_location, this->tile_->where());
        while (closer_locations.size() > 0)
        {
            int index = rand() % closer_locations.size();
            newTile = floor->tile(closer_locations[index]);
            if (newTile->there_is_room(this))
            {
                // we can move here
                break;
            }
            closer_locations.erase(closer_locations.begin()+index);
            newTile = nullptr;
        }

        // for now, freeze if you cant advance
        if (newTile == nullptr)
        {
            return false;
        }

        this->place(newTile);
        return true;
    }
};

#endif // _rat_h_