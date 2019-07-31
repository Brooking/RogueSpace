#include <stdexcept>
#include <assert.h>
#include "floor.h"

Floor::Floor(int height, int width)
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

Tile* Floor::tile(Location location)
{
    if (location.row() >= this->height() || location.row() < 0 ||
        location.cell() >= this->width() || location.cell() < 0 )
    {
        return nullptr;
    }
    return (&(this->tile_[location.row()][location.cell()])); 
}
