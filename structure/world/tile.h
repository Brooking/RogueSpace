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
class Tile : public iThing
{
public:
    Tile(Floor* floor, Location location) : 
        floor_(floor), token_(UIToken::bare_floor), location_(location), full_(false) 
    {}
    ~Tile() {}

    // iThing
    virtual UIToken token() const;
    virtual Tile* tile() const { return const_cast<Tile*>(this); }
    virtual bool fills_tile() const { return false; }
    virtual bool is_center() const { return true; }

    // utility
    Location where() { return location_; }
    const Floor* floor() const { return this->floor_; }
    bool is_full() const { return this->full_; }

    // thing management
    bool add(iThing* thing);
    bool remove(iThing* thing);
    int num_things() const { return this->things_.size(); }
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