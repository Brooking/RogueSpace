#ifndef _tile_h_
#define _tile_h_

#include <stdexcept>
#include <vector>
#include <set>
#include <assert.h>
#include "uitokens.h"
#include "location.h"
#include "ithing.h"
#include "content_size.h"

class Floor;

#ifndef PROTECTED_ACCESS
#define PROTECTED_ACCESS protected
#endif

//
// A single spot on a floor
//
class Tile
{
public:
    Tile(Floor* floor, Location location) : 
        floor_(floor), token_(UIToken::bare_floor), location_(location), fullness_(ContentSize::empty),
        has_been_seen_(false)
    {}
    ~Tile() {}

    // Th UI token of the topmost thing on the tile
    UIToken token() const;

    // The floor location of this tile
    Location where() const { return location_; }

    // The floor this tile is in
    Floor* floor() const { return this->floor_; }

    // How full is the tile
    ContentSize how_full() const { return this->fullness_; }

    // will this thing fit in the tile
    bool there_is_room(iThing* thing);


    // add a thing to this tile
    bool add(iThing* thing);

    // remove a thing from this tile
    bool remove(iThing* thing);

    // how many thing are on this tile
    int num_things() const { return this->things_.size(); }

    // array notation thing accessor
    const iThing* operator [] (int i) const { return const_cast<const iThing*>(this->things_[i]); }

    // add a spot that is visible from this tile
    void add_visible(Location location);

    // ask whether a spot is visible from this tile
    bool is_visible(Location location) const;

    // Has visibility been calculated for this tile
    bool visibility_has_been_calculated() const;

    // this tile has been seen
    bool has_been_seen() { return this->has_been_seen_; }

    // see this tile
    void set_has_been_seen(bool seen) { this->has_been_seen_ = seen; }

PROTECTED_ACCESS:
    // calculate fullness based on contents
    ContentSize calculate_fullness();

private:
    // prohibit parameterless construction
    Tile();

private:
    // The floor that this tile is in
    Floor* floor_;

    // the current token
    UIToken token_;

    // the location of this tile
    Location location_;

    // the list of things on this tile
    std::vector<iThing*> things_;

    // the current fullness of the tile
    ContentSize fullness_;

    // all of the spots visible from this tile
    std::set<Location> visible_;

    // has this tile been seen
    bool has_been_seen_;
};

#endif // _tile_h_