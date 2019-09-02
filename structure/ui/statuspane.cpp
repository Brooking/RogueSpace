#include "statuspane.h"
StatusPane::StatusPane(
    std::shared_ptr<io::Screen> screen, 
    std::shared_ptr<Hero> hero,
    unsigned int screen_row, 
    unsigned int screen_cell,
    unsigned int height,
    unsigned int width)
    :
    screen_(screen), hero_(hero), window_(nullptr)
{
    this->window_ = this->screen_->create_window(screen_row, screen_cell, height, width);

    // paint the background
    for (unsigned int row = 0; row < this->window_->height(); row++)
    {
        for (unsigned int cell = 0; cell < this->window_->width(); cell++)
        {
            this->window_->place_character(row, cell, ' ', StatusPane::pane_foreground, StatusPane::pane_background);
        }
    }

    // update with current data
    this->update();
    this->refresh();
}

bool StatusPane::update(int, int, bool center)
{ 
    if (center)
    {
        return this->update();
    }
    return false;
}

void StatusPane::refresh()
{
    this->window_->refresh();
}

bool StatusPane::update()
{
    static int top_margin = 0;
    static int bottom_margin = 1;
    static int label_margin = 1;
    int therm_blocks = this->window_->height() - top_margin - bottom_margin - label_margin;
    int health_blocks = (therm_blocks * this->hero_->current_health()) / this->hero_->max_health();
    int energy_blocks = (therm_blocks * this->hero_->current_energy()) / this->hero_->max_energy();

    static int health_cell = 1;
    static int energy_cell = 3;

    this->window_->place_character(top_margin, health_cell, 'H', StatusPane::health_foreground, StatusPane::pane_background);
    int top = top_margin + label_margin + (therm_blocks - health_blocks);
    for (int i = 0; i < health_blocks; i++)
    {
        this->window_->place_character(top+i, health_cell, ' ', StatusPane::health_foreground, StatusPane::health_foreground);
    }

    this->window_->place_character(top_margin, energy_cell, 'E', StatusPane::energy_foreground, StatusPane::pane_background);
    top = top_margin + label_margin + (therm_blocks - energy_blocks);
    for (int i = 0; i < energy_blocks; i++)
    {
        this->window_->place_character(top+i, energy_cell, ' ', StatusPane::energy_foreground, StatusPane::energy_foreground);
    }

    return true;
}