#ifndef _tile_h_
#define _tile_h_

#include <stdexcept>
#include <vector>
#include <assert.h>
#include "uitokens.h"
#include "location.h"
#include "ithing.h"

class Floor;

//
// A single spot on a floor
//
class Tile
{
public:
    Tile(Floor* floor, Location location) : 
        floor_(floor), token_(UIToken::bare_floor), location_(location), full_(false) 
    {}
    ~Tile() {}

    // Th UI token of the topmost thing on the tile
    UIToken token() const;

    // The floor location of this tile
    Location where() { return location_; }

    // The floor this tile is in
    const Floor* floor() const { return this->floor_; }

    // Does this tile contain a 'filling' thing (like a wall)
    bool is_full() const { return this->full_; }

    // add a thing to this tile
    bool add(iThing* thing);

    // remove a thing from this tile
    bool remove(iThing* thing);

    // how many thing are on this tile
    int num_things() const { return this->things_.size(); }

    // array notation thing accessor
    const iThing* operator [] (int i) const { return const_cast<const iThing*>(this->things_[i]); }

private:
    Tile();

private:
    Floor* floor_;
    UIToken token_;
    Location location_;
    std::vector<iThing*> things_;
    bool full_;
};

#endif // _tile_h_