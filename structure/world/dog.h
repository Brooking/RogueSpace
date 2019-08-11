#ifndef _dog_h_
#define _dog_h_

#include "monster_base.h"

class Dog : public MonsterBase
{
public:
    Dog(Tile* tile) : MonsterBase(tile, UIToken::dog) {}
    virtual ~Dog() {}

    // iThing: do its move
    virtual bool move()
    {
        Floor* floor = this->tile_->floor();
        Location hero_location = floor->hero()->where();
        Tile* newTile = nullptr;

        int distance = this->tile_->where().distance(hero_location);
        std::vector<Location> locations;
        if (distance > 3)
        {
            // move closer or stand still
            locations = this->tile_->where().closer_adjacent_locations(hero_location);
        }
        else
        {
            // the dog is close enough, just move at random
            locations = this->tile()->where().all_adjacent_locations();
        }
        
        while (locations.size() > 0)
        {
            int index = rand() % locations.size();
            newTile = floor->tile(locations[index]);
            if (newTile->there_is_room(this))
            {
                // we can move here
                break;
            }
            locations.erase(locations.begin()+index);
            newTile = nullptr;
        }

        // for now, freeze if you can't advance
        if (newTile == nullptr)
        {
            return false;
        }

        this->place(newTile);
        return true;
    }
};

#endif // _dog_h_