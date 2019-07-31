#include <assert.h>
#include "floor.h"

Floor::Floor(int height, int width)
{
    assert(height > 0);
    assert(width > 0);
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