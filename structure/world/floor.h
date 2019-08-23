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
class Floor : public iFloor, public std::enable_shared_from_this<Floor>
{
public:
    static std::shared_ptr<Floor> create(int height, int width);
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
    std::shared_ptr<Tile> tile(Location location);

    // the spot our tiles call us when things change
    bool update(Location location, bool is_center = false);

    // a pointer to our hero
    // todo...it is odd that the floor knows where the hero is
    std::shared_ptr<Hero> hero() { return this->hero_; }
    void add_hero(std::shared_ptr<Hero> hero) { this->hero_ = hero; }

    // add a light
    bool add_light(int row, int cell, int radius);

private:
    // private constructor (use Floor::create)
    Floor() : update_interface_(nullptr), hero_(nullptr) {}

    // add all of the tiles to the floor
    void init(int height, int width);

private:
    // all of the tiles on this floor
    std::vector<std::vector<std::shared_ptr<Tile>>> tile_;

    // the interface to call when something changes
    std::shared_ptr<iUpdate> update_interface_;

    // The hero on the floor
    // TODO: is this the right spot for it?
    std::shared_ptr<Hero> hero_;

    // all of the lights
    std::vector<std::shared_ptr<Tile>> lights_;
};

#endif //_floor_h_