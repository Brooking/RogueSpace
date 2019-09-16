#ifndef _floor_h_
#define _floor_h_

#include <memory>
#include <vector>
#include "hero.h"
#include "ifloor.h"
#include "ifov.h"
#include "iwall_map.h"
#include "location.h"
#include "tile.h"

//
// Holds a single floor
//
class Floor : public iFloor, public iWallMap, public std::enable_shared_from_this<Floor>
{
public:
    static std::shared_ptr<Floor> create(unsigned int height, unsigned int width);
    virtual ~Floor() = default;

    // iFloor: the ui is giving us a callback
    virtual bool register_update(std::shared_ptr<iUpdate> update_interface) override;

    // iFloor+iWallMap: returns the height (number of rows)
    virtual unsigned int height() const override { return static_cast<unsigned int>(tile_.size()); }

    // iFloor+iWallMap: returns the width (number of cells per row)
    virtual unsigned int width() const override { return static_cast<unsigned int>(tile_[0].size()); }

    // iFloor: returns the ui token for a given location
    virtual UIToken token(unsigned int row, unsigned int cell) const override;

    // iFloor: returns the location of the hero on the floor
    virtual Location hero_location() const override { return this->hero_.lock()->where(); }

    // iWallMap: returns whether this spot contains a wall
    virtual bool is_opaque(unsigned int row, unsigned int cell) const override;

    // iWallMap: we don't
    virtual void set_opaque(uint, uint, bool) override
    {
        throw std::invalid_argument("dont artificially make a wall...");
    }

    // returns the tile at a given location
    std::shared_ptr<Tile> tile(Location location) const;

    // the spot our tiles call us when things change
    bool update(Location location, bool is_center = false);

    // a pointer to our hero
    // todo...it is odd that the floor knows where the hero is
    std::weak_ptr<Hero> hero() { return this->hero_; }
    void add_hero(std::weak_ptr<Hero> hero) { this->hero_ = hero; }

    // add a light
    bool add_light(unsigned int row, unsigned int cell, unsigned int radius);

    // given a list of locations, return a random one to move to
    Location choose_random(std::vector<Location> locations, std::shared_ptr<iThing> thing) const;

private:
    // private constructor (use Floor::create)
    Floor() : tile_(), update_interface_(), hero_(), lights_() {}

    // add all of the tiles to the floor
    void init(unsigned int height, unsigned int width);

private:
    // Class for responses from light casting
    class LightFov : public iFov
    {
    public:
        LightFov(std::shared_ptr<Floor> floor) : floor_(floor) {}
        void set_fov(unsigned int row, unsigned int cell, unsigned int) override
        {
            this->floor_->tile(Location(row,cell))->set_is_lit(true);
        }
        unsigned int get_fov(unsigned int row, unsigned int cell)
        {
            return this->floor_->tile(Location(row,cell))->is_lit();
        };
    private:
        std::shared_ptr<Floor> floor_;
    };

private:
    // all of the tiles on this floor
    std::vector<std::vector<std::shared_ptr<Tile>>> tile_;

    // the interface to call when something changes
    std::weak_ptr<iUpdate> update_interface_;

    // The hero on the floor
    // TODO: is this the right spot for it?
    std::weak_ptr<Hero> hero_;

    // all of the lights
    std::vector<std::shared_ptr<Tile>> lights_;
};

#endif //_floor_h_