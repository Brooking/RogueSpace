#include <stdexcept>
#include <assert.h>
#include "floor.h"

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


UIToken Floor::token(Location location)
{
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

bool Floor::update(Location location)
{
    if (this->update_interface_ != nullptr)
    {
        this->update_interface_->update(location);
        return true;
    }

    return false;
}