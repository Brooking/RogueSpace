#include <bitset>
#include <assert.h>
#include "viewport.h"
#include "icon.h"

Viewport::Viewport(io::Screen* screen, iFloor& floor, unsigned int height, unsigned int width, 
                   Location center) : 
    screen_(screen), window_(nullptr), floor_(floor), 
    height_(height), width_(width), 
    window_origin_row_offset_from_floor_(0), window_origin_cell_offset_from_floor_(0)
{
    // place the window on the screen
    unsigned int screen_y = 0;
    unsigned int screen_x = 0;
    this->window_ = this->screen_->create_window(screen_y, screen_x, height, width);

    // center (implies fill) and refresh
    this->update_center(center);
    this->refresh();
}

bool Viewport::update_center(Location center)
{
    Location corner(center.row() - this->height_/2, center.cell() - this->width_/2);
    bool center_moved = corner.row() != this->window_origin_row_offset_from_floor_ ||
                        corner.cell() != this->window_origin_cell_offset_from_floor_;
    this->window_origin_row_offset_from_floor_ = corner.row();
    this->window_origin_cell_offset_from_floor_ = corner.cell();
    if (center_moved)
    {
        return this->full_update();
    }
    return true;
}

// this is an update request from the world
// location is in floor coordinates
bool Viewport::update(Location location, bool center)
{
    if (center)
    {
        this->update_center(location);
    }

    return this->update(location.row() - this->window_origin_row_offset_from_floor_, 
                        location.cell() - this->window_origin_cell_offset_from_floor_);
}

// this is an internal update
// row and cell are in window coordinates
bool Viewport::update(unsigned int row, unsigned int cell)
{
    // location is in floor coordinates
    Location location(row + this->window_origin_row_offset_from_floor_, 
                      cell + this->window_origin_cell_offset_from_floor_);

    UIToken token = this->floor_.token(location);
    std::bitset<8> adjacency;
    if (token == UIToken::wall)
    {
        adjacency[AdjacentWallBits::North] = this->floor_.token(Location(location.row()-1, location.cell())) == UIToken::wall;
        adjacency[AdjacentWallBits::East] = this->floor_.token(Location(location.row(), location.cell()+1)) == UIToken::wall;
        adjacency[AdjacentWallBits::South] = this->floor_.token(Location(location.row()+1, location.cell())) == UIToken::wall;
        adjacency[AdjacentWallBits::West] = this->floor_.token(Location(location.row(), location.cell()-1)) == UIToken::wall;
    }
    Icon icon(token, static_cast<int>(adjacency.to_ulong()));
    this->window_->place_character(row, cell, icon.symbol());
    return true;
}

bool Viewport::full_update()
{

    for (unsigned int row = 0; row < this->height_; row++)
    {
        for (unsigned int cell = 0; cell < this->width_; cell++)
        {
            this->update(row,cell);
        }
    }

    return true;
}

void Viewport::refresh()
{
    this->window_->refresh();
}