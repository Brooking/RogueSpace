#include <assert.h>
#include <memory>
#include <stdexcept>
#include "floor.h"
#include "map_for_casting.h"
#include "visibility/original_shadow_cast.h"

std::shared_ptr<Floor> Floor::create(unsigned int height, unsigned int width)
{
    // can not use "std::make_shared<Floor>();" here because that requires a public c'tor
    std::shared_ptr<Floor> floor = std::shared_ptr<Floor>(new Floor());
    floor->init(height, width);
    return floor;
}

void Floor::init(unsigned int height, unsigned int width)
{
    if (height < 1) {
        throw std::invalid_argument("height must be positive");
    }
    if (width < 1) {
        throw std::invalid_argument("width must be positive");
    }
    for (unsigned int row = 0; row < height; row++)
    {
        this->tile_.push_back(std::vector<std::shared_ptr<Tile>>());
        for (unsigned int cell = 0; cell < width; cell++)
        {
            std::shared_ptr<Tile> tile = std::make_shared<Tile>(this->shared_from_this(), Location(row, cell));
            this->tile_[row].push_back(tile);
        }
    }
}



bool Floor::register_update(std::shared_ptr<iUpdate> update_interface)
{
    this->update_interface_ = update_interface;
    return true;
}


UIToken Floor::token(unsigned int row, unsigned int cell)
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
    if (location.row() >= this->height() || location.cell() >= this->width())
    {
        return nullptr;
    }
    return (this->tile_[location.row()][location.cell()]); 
}

bool Floor::update(Location location, bool is_center)
{
    if (!this->update_interface_.expired())
    {
        std::shared_ptr<iUpdate> locked_update_interface = 
            this->update_interface_.lock();
        // tell the ui something changed
        locked_update_interface->update(location.row(), location.cell(), is_center);
        return true;
    }

    return false;
}

bool Floor::add_light(unsigned int row, unsigned int cell, unsigned int radius)
{
    std::shared_ptr<Tile> tile = this->tile(Location(row, cell));
    tile->set_is_lit(true);

    MapForCasting map(tile, CastingScan::illumination);
    do_fov(map, cell, row, radius);
    return true;
}
