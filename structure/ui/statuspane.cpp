#include "statuspane.h"
StatusPane::StatusPane(
    std::shared_ptr<iScreen> screen, 
    std::weak_ptr<Hero> hero,
    unsigned int screen_row, 
    unsigned int screen_cell,
    unsigned int height)
:
    screen_(screen), hero_ptr_(hero), window_(nullptr),
    screen_row_(screen_row), screen_cell_(screen_cell), 
    height_(height), width_(StatusPane::StatusPaneWidth)
{
    this->window_ = this->screen_->create_window(
        this->screen_row_, 
        this->screen_cell_, 
        this->height_, 
        this->width_);

    // we do not automaticaly fill or refresh, we await other's orders
}

void StatusPane::refill()
{
    // paint the background
    for (unsigned int row = 0; row < this->window_->height(); row++)
    {
        for (unsigned int cell = 0; cell < this->window_->width(); cell++)
        {
            this->window_->place_character(
                row,
                cell,
                ' ',
                StatusPane::pane_foreground,
                StatusPane::pane_background);
        }
    }

    this->update();
}

void StatusPane::refresh()
{
    this->window_->refresh();
}

bool StatusPane::update(unsigned int, unsigned int, bool center)
{ 
    if (center)
    {
        return this->update();
    }
    return false;
}

bool StatusPane::update()
{
    std::shared_ptr<Hero> hero = this->hero_ptr_.lock();
    static const unsigned int top_margin = 0;
    static const unsigned int bottom_margin = 1;
    static const unsigned int health_cell = 1;
    static const unsigned int energy_cell = 3;

    unsigned int therm_top = this->screen_row() + top_margin;
    unsigned int therm_height = 
        this->window_->height() - top_margin - bottom_margin;

    // health
    fill_thermometer(therm_top, health_cell, therm_height, 'H', 
        hero->max_health(), hero->current_health(),
        StatusPane::health_foreground, StatusPane::pane_background);

    // energy

    fill_thermometer(therm_top, energy_cell, therm_height, 'E', 
        hero->max_energy(), hero->current_energy(),
        StatusPane::energy_foreground, StatusPane::pane_background);

    return true;
}

void StatusPane::fill_thermometer(
    unsigned int screen_row, 
    unsigned int screen_cell,
    unsigned int height,
    unsigned int label,
    unsigned int max,
    unsigned int current,
    io::Color therm_color,
    io::Color pane_background)
{
    unsigned int therm_height = height - 1;
    unsigned int therm_row = screen_row + 1;
    unsigned int blocks = (therm_height * current) / max;
    unsigned int blanks = therm_height - blocks;

    // print out the label
    this->window_->place_character(
        screen_row,
        screen_cell,
        label,
        therm_color,
        pane_background);

    // print the actual thermometer
    for (unsigned int i = 0; i < therm_height; i++)
    {
        io::Color foreground = therm_color;
        io::Color background = (i < blanks) ? pane_background : therm_color;
        this->window_->place_character(
            therm_row + i,
            screen_cell,
            static_cast<unsigned int>(io::Character::FROST),
            foreground,
            background);
    }
}