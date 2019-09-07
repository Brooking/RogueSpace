#include <assert.h>
#include <bitset>
#include "icon.h"
#include "viewport.h"

Viewport::Viewport(
    std::shared_ptr<iScreen> screen, 
    std::shared_ptr<iFloor> floor, 
    unsigned int screen_row,
    unsigned int screen_cell, 
    unsigned int height, 
    unsigned int width, 
    unsigned int center_row,
    unsigned int center_cell)
: 
    screen_(screen), window_(nullptr), floor_(floor), 
    screen_row_(screen_row), screen_cell_(screen_cell),
    height_(height), width_(width), 
    window_origin_row_offset_from_floor_(0), window_origin_cell_offset_from_floor_(0)
{
    // place the window on the screen
    this->window_ = this->screen_->create_window(screen_row, screen_cell, height, width);

    // we do not automaticaly fill or refresh, we await other's orders
    this->update_center(center_row, center_cell, false);
}

bool Viewport::update_center(unsigned int center_row, unsigned int center_cell, bool update)
{
    int corner_row = center_row - this->height_/2;
    int corner_cell = center_cell - this->width_/2;
    bool center_moved = corner_row != this->window_origin_row_offset_from_floor_ ||
                        corner_cell != this->window_origin_cell_offset_from_floor_;
    this->window_origin_row_offset_from_floor_ = corner_row;
    this->window_origin_cell_offset_from_floor_ = corner_cell;
    if (center_moved && update)
    {
        return this->update();
    }
    return true;
}

void Viewport::refill()
{
    // there is no decoration on a viewport (...yet...)
    this->update();
}


// this is an update request from the world
// location is in floor coordinates
bool Viewport::update(unsigned int row, unsigned int cell, bool center)
{
    if (center)
    {
        this->update_center(row, cell, true);
    }

    return this->update_worker(row - this->window_origin_row_offset_from_floor_, 
                        cell - this->window_origin_cell_offset_from_floor_);
}

// this is an internal update
// row and cell are in window coordinates
bool Viewport::update_worker(unsigned int row, unsigned int cell)
{
    unsigned int floor_row = row + this->window_origin_row_offset_from_floor_;
    unsigned int floor_cell = cell + this->window_origin_cell_offset_from_floor_;

    UIToken token = this->floor_->token(floor_row, floor_cell);
    Icon icon(token);
    this->window_->place_character(
        row,
        cell,
        icon.symbol(),
        icon.foreground_color(),
        icon.background_color());
    return true;
}

bool Viewport::update()
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