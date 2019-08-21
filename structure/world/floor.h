#ifndef _floor_h_
#define _floor_h_

#include <memory>
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
    virtual bool register_update(std::shared_ptr<iUpdate> update_interface);

    // iFloor: returns the height (number of rows)
    virtual int height() { return tile_.size(); }

    // iFloor: returns the width (number of cells per row)
    virtual int width() { return tile_[0].size(); }

    // iFloor: returns the ui token for a given location
    virtual UIToken token(int row, int cell);

    // returns the tile at a given location
    Tile* tile(Location location);

    // the spot our tiles call us when things change
    bool update(Location location, bool is_center = false);

    // a pointer to our hero
    // todo...it is odd that the floor knows where the hero is
    Hero* hero() { return this->hero_; }
    void add_hero(Hero* hero) { this->hero_ = hero; }

    // add a light
    bool add_light(int row, int cell, int radius);

private:
    // all of the tiles on this floor
    std::vector<std::vector<Tile>> tile_;

    // the interface to call when something changes
    std::shared_ptr<iUpdate> update_interface_;

    // The hero on the floor
    // TODO: is this the right spot for it?
    Hero* hero_;

    // all of the lights
    std::vector<Tile*> lights_;
};

#endif //_floor_h_