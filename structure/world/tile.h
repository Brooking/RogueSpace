#ifndef _tile_h_
#define _tile_h_

#include <stdexcept>
#include <vector>
#include <assert.h>
#include "uitokens.h"
#include "location.h"
#include "ithing.h"
#include "content_size.h"

class Floor;

//
// A single spot on a floor
//
class Tile
{
public:
    Tile(Floor* floor, Location location) : 
        floor_(floor), token_(UIToken::bare_floor), location_(location), fullness_(ContentSize::empty) 
    {}
    ~Tile() {}

    // Th UI token of the topmost thing on the tile
    UIToken token() const;

    // The floor location of this tile
    Location where() { return location_; }

    // The floor this tile is in
    const Floor* floor() const { return this->floor_; }

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

private:
    Tile();
    ContentSize calculate_fullness();

private:
    Floor* floor_;
    UIToken token_;
    Location location_;
    std::vector<iThing*> things_;
    ContentSize fullness_;
};

#endif // _tile_h_