#include <stdexcept>
#include <assert.h>
#include "floor.h"
#include "../visibility/map_for_casting.h"
#include "../visibility/original_shadow_cast.h"

Floor::Floor(int height, int width) : update_interface_(nullptr)
{
    if (height < 1) {
        throw std::invalid_argument("height must be positive");
    }
    if (width < 1) {
        throw std::invalid_argument("width must be positive");
    }
    for (int row = 0; row < height; row++)
    {
        this->tile_.push_back(std::vector<Tile>());
        for (int cell = 0; cell < width; cell++)
        {
            Tile tile(this, Location(row, cell));
            this->tile_[row].push_back(tile);
        }
    }
}

bool Floor::register_update(iUpdate* update_interface)
{
    this->update_interface_ = update_interface;
    return true;
}


UIToken Floor::token(int row, int cell)
{
    Location location(row, cell);
    Tile* tile = this->tile(location);
    if (tile == nullptr)
    {
        return UIToken::none;
    }
    return tile->token();
}


Tile* Floor::tile(Location location)
{
    if (location.row() >= this->height() || location.row() < 0 ||
        location.cell() >= this->width() || location.cell() < 0 )
    {
        return nullptr;
    }
    return (&(this->tile_[location.row()][location.cell()])); 
}

bool Floor::update(Location location, bool is_center)
{
    Tile* tile = this->tile(location);
    if (is_center && !tile->visibility_has_been_calculated())
    {
        MapForCasting map(tile);
        do_fov(map, location.cell(), location.row(), 10);
    }

    if (this->update_interface_ != nullptr)
    {
        this->update_interface_->update(location.row(), location.cell(), is_center);
        return true;
    }

    return false;
}

bool Floor::is_visible(int row, int cell)
{
    assert(this->hero_->tile()->visibility_has_been_calculated());
    Location location(row,cell);
    if (this->hero_->tile()->is_visible(Location(row,cell)))
    {
        return true;
    }

    Tile* tile = this->tile(location);
    if (tile != nullptr && tile->token() == UIToken::wall && tile->has_been_seen())
    {
        return true;
    }
    return false;
}
