#include <stdexcept>
#include <assert.h>
#include "floor.h"
#include "map_for_casting.h"
#include "../visibility/original_shadow_cast.h"

Floor::Floor(int height, int width) : update_interface_(nullptr), hero_(nullptr)
{
    if (height < 1) {
        throw std::invalid_argument("height must be positive");
    }
    if (width < 1) {
        throw std::invalid_argument("width must be positive");
    }
    for (int row = 0; row < height; row++)
    {
        this->tile_.push_back(std::vector<std::shared_ptr<Tile>>());
        for (int cell = 0; cell < width; cell++)
        {
            std::shared_ptr<Tile> tile = std::make_shared<Tile>(this, Location(row, cell));
            this->tile_[row].push_back(tile);
        }
    }
}

bool Floor::register_update(std::shared_ptr<iUpdate> update_interface)
{
    this->update_interface_ = update_interface;
    return true;
}


UIToken Floor::token(int row, int cell)
{
    Location location(row, cell);
    std::shared_ptr<Tile> tile = this->tile(location);
    if (tile == nullptr)
    {
        return UIToken::none;
    }
    return tile->token();
}


std::shared_ptr<Tile> Floor::tile(Location location)
{
    if (location.row() >= this->height() || location.row() < 0 ||
        location.cell() >= this->width() || location.cell() < 0 )
    {
        return nullptr;
    }
    return (this->tile_[location.row()][location.cell()]); 
}

bool Floor::update(Location location, bool is_center)
{
    if (this->update_interface_ != nullptr)
    {
        // tell the ui something changed
        this->update_interface_->update(location.row(), location.cell(), is_center);
        return true;
    }

    return false;
}

bool Floor::add_light(int row, int cell, int radius)
{
    std::shared_ptr<Tile> tile = this->tile(Location(row, cell));
    tile->set_is_lit(true);

    MapForCasting map(tile, CastingScan::illumination);
    do_fov(map, cell, row, radius);
    return true;
}
