#include "blank_pane.h"
#include "io/window.h"

BlankPane::BlankPane(
    std::shared_ptr<io::Screen> screen, 
    unsigned int screen_row, 
    unsigned int screen_cell,
    unsigned int height,
    unsigned int width)
:
    screen_(screen), window_(), 
    screen_row_(screen_row), screen_cell_(screen_cell), 
    height_(height), width_(width)
{
    this->window_ = this->screen_->create_window(screen_row, screen_cell, height, width);

    // we do not automaticaly fill or refresh, we await other's orders
}

void BlankPane::refill()
{
    // paint the background
    for (unsigned int row = 0; row < this->window_->height(); row++)
    {
        for (unsigned int cell = 0; cell < this->window_->width(); cell++)
        {
            this->window_->place_character(row, cell, ' ', 
                BlankPane::pane_foreground, BlankPane::pane_background);
        }
    }
}

void BlankPane::refresh()
{
    this->window_->refresh();
}
