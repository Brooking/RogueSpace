#ifndef _tile_h_
#define _tile_h_

#include <assert.h>
#include <memory>
#include <stdexcept>
#include <set>
#include <vector>
#include "content_size.h"
#include "ifov.h"
#include "ithing.h"
#include "location.h"
#include "uitoken.h"

class Floor;

#ifndef PROTECTED_ACCESS
#define PROTECTED_ACCESS protected
#endif

//
// A single spot on a floor
//
class Tile : public std::enable_shared_from_this<Tile>
{
public:
    Tile(std::shared_ptr<Floor> floor, Location location) : 
        floor_(floor), location_(location), things_(), fullness_(ContentSize::empty),
        los_range_(), has_been_seen_(false), is_lit_(false), d_map_()
    {}
    ~Tile() {}

    // Th UI token of the topmost thing on the tile
    UIToken token();

    // The floor location of this tile
    Location where() const { return location_; }

    // The floor this tile is in
    std::shared_ptr<Floor> floor() const { return this->floor_.lock(); }

    // How full is the tile
    ContentSize how_full() const { return this->fullness_; }

    // will this thing fit in the tile
    bool there_is_room(std::shared_ptr<iThing> thing);

    // add a thing to this tile
    bool add(std::shared_ptr<iThing> thing);

    // remove a thing from this tile
    bool remove(std::shared_ptr<iThing> thing);

    // how many thing are on this tile
    long unsigned int num_things() const { return this->things_.size(); }

    // array notation thing accessor
    const std::shared_ptr<iThing> thing(unsigned int i) const { return this->things_[i]; }

    // add a spot that has los from this tile
    void add_los_range(Location location, unsigned int range);

    // ask how far los id from this tile
    // (returns UINT_MAX if no line of sight)
    unsigned int get_los_range(Location location);

    // this tile has been seen
    bool has_been_seen() { return this->has_been_seen_; }

    // set this tile as lit
    void set_is_lit(bool lit) { this->is_lit_ = lit; }

    // returns whether this tile is lit
    bool is_lit() { return this->is_lit_; }

    // returns whether the hero can see this tile
    bool hero_can_see();

    // returns whether this tile contains a wall
    bool is_wall();

    // calculate dijkstra map
    const std::shared_ptr<std::vector<std::vector<unsigned int>>> get_dmap();

PROTECTED_ACCESS:
    // calculate fullness based on contents
    ContentSize calculate_fullness();

private:
    // prohibit parameterless construction
    Tile() = delete;

    // prohibit copying
    Tile(const Tile&) = delete;
    Tile& operator=(const Tile&) = delete;

private:
    // Class for responses from eye casting
    class EyeLos : public iFov
    {
    public:
        EyeLos(std::shared_ptr<Tile> tile) : tile_(tile) {}
        void set_fov(unsigned int row, unsigned int cell, unsigned int distance) override
        {
            if (this->get_fov(row,cell) > distance)
            {
                // store the shortest distance...
                this->tile_->add_los_range(Location(row,cell), distance);
            }
        }

        unsigned int get_fov(unsigned int row, unsigned int cell) override
        {
            return this->tile_->get_los_range(Location(row,cell));
        }
    private:
        std::shared_ptr<Tile> tile_;
    };

private:
    // The floor that this tile is in
    std::weak_ptr<Floor> floor_;

    // the location of this tile
    Location location_;

    // the list of things on this tile
    std::vector<std::shared_ptr<iThing>> things_;

    // the current fullness of the tile
    ContentSize fullness_;

    // all of the spots with los from this tile
    std::vector<std::vector<unsigned int>>* los_range_;

    // has this tile been seen
    bool has_been_seen_;

    // is this tile lit
    bool is_lit_;

    // Paths to this tile
    std::shared_ptr<std::vector<std::vector<unsigned int>>> d_map_;
};

#endif // _tile_h_