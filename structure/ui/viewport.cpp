#include <bitset>
#include <assert.h>
#include "viewport.h"
#include "icon.h"

Viewport::Viewport(
    std::shared_ptr<io::Screen> screen, 
    std::shared_ptr<iFloor> floor, 
    unsigned int height, 
    unsigned int width, 
    int center_row,
    int center_cell)
    : 
    screen_(screen), window_(nullptr), floor_(floor), 
    height_(height), width_(width), 
    window_origin_row_offset_from_floor_(0), window_origin_cell_offset_from_floor_(0)
{
    // place the window on the screen
    unsigned int screen_y = 0;
    unsigned int screen_x = 0;
    this->window_ = this->screen_->create_window(screen_y, screen_x, height, width);

    this->full_update();
    this->update_center(center_row, center_cell);
    this->refresh();
}

bool Viewport::update_center(int center_row, int center_cell)
{
    int corner_row = center_row - this->height_/2;
    int corner_cell = center_cell - this->width_/2;
    bool center_moved = corner_row != this->window_origin_row_offset_from_floor_ ||
                        corner_cell != this->window_origin_cell_offset_from_floor_;
    this->window_origin_row_offset_from_floor_ = corner_row;
    this->window_origin_cell_offset_from_floor_ = corner_cell;
    if (center_moved)
    {
        return this->full_update();
    }
    return true;
}

// this is an update request from the world
// location is in floor coordinates
bool Viewport::update(int row, int cell, bool center)
{
    if (center)
    {
        this->update_center(row, cell);
    }

    return this->update_worker(row - this->window_origin_row_offset_from_floor_, 
                        cell - this->window_origin_cell_offset_from_floor_);
}

// this is an internal update
// row and cell are in window coordinates
bool Viewport::update_worker(unsigned int row, unsigned int cell)
{
    int floor_row = row + this->window_origin_row_offset_from_floor_;
    int floor_cell = cell + this->window_origin_cell_offset_from_floor_;

    std::bitset<8> adjacency;
    UIToken token = this->floor_->token(floor_row, floor_cell);
    if (is_wall(token))
    {
        adjacency[AdjacentWallBits::North] = is_wall(this->floor_->token(floor_row-1, floor_cell));
        adjacency[AdjacentWallBits::East] = is_wall(this->floor_->token(floor_row, floor_cell+1));
        adjacency[AdjacentWallBits::South] = is_wall(this->floor_->token(floor_row+1, floor_cell));
        adjacency[AdjacentWallBits::West] = is_wall(this->floor_->token(floor_row, floor_cell-1));
    }
   Icon icon(token, static_cast<int>(adjacency.to_ulong()));
    this->window_->place_character(row, cell, icon.symbol(), icon.foreground_color(), icon.background_color());
    return true;
}

bool Viewport::full_update()
{

    for (unsigned int row = 0; row < this->height_; row++)
    {
        for (unsigned int cell = 0; cell < this->width_; cell++)
        {
            this->update_worker(row,cell);
        }
    }

    return true;
}

void Viewport::refresh()
{
    this->window_->refresh();
}