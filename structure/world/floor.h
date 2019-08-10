#ifndef _floor_h_
#define _floor_h_

#include <vector>
#include "tile.h"
#include "location.h"
#include "hero.h"
#include "ifloor.h"

//
// Holds a single floor
//
class Floor : public iFloor
{
public:
    Floor(int height, int width);
    virtual ~Floor() {}

    // iFloor: the ui is giving us a callback
    virtual bool register_update(iUpdate* update_interface);

    // iFloor: returns the height (number of rows)
    virtual int height() { return tile_.size(); }

    // iFloor: returns the width (number of cells per row)
    virtual int width() { return tile_[0].size(); }

    // iFloor: returns the ui token for a given location
    virtual UIToken token(Location location);

    // returns the tile at a given location
    Tile* tile(Location location);

    // the spot our tiles call us when things change
    bool update(Location location, bool is_center = false);

    // a pointer to our hero
    // todo...it is odd that the floor knows where the hero is
    Hero* hero() { return this->hero_; }
    void add_hero(Hero* hero) { this->hero_ = hero; }


private:
    std::vector<std::vector<Tile>> tile_;
    iUpdate* update_interface_;
    Hero* hero_;
};

#endif //_floor_h_