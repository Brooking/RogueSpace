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
                StatusPane::PaneForeground,
                StatusPane::PaneBackground);
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
    unsigned int therm_top = this->screen_row() + TopMargin;
    unsigned int therm_height = 
        this->window_->height() - TopMargin - BottomMargin;
    unsigned int run_row = this->window_->height() - 1;

    // health
    fill_thermometer(therm_top, StatusPane::HealthCell, therm_height, 'H', 
        hero->max_health(), hero->current_health(),
        StatusPane::HealthForeground, StatusPane::PaneBackground);

    // energy
    fill_thermometer(therm_top, StatusPane::EnergyCell, therm_height, 'E', 
        hero->max_energy(), hero->current_energy(),
        StatusPane::EnergyForeground, StatusPane::PaneBackground);

    // stamina
    fill_thermometer(therm_top, StatusPane::StaminaCell, therm_height, 'S', 
        hero->max_stamina(), hero->current_stamina(),
        StatusPane::StaminaForeground, StatusPane::PaneBackground);

    // update run/walk
    if (hero->is_running())
    {
        this->window_->place_string(
            run_row,
            StatusPane::HealthCell,
            "run ",
            StatusPane::PaneForeground,
            StatusPane::PaneBackground);
    }
    else
    {
        this->window_->place_string(
            run_row,
            StatusPane::HealthCell,
            "walk",
            StatusPane::PaneForeground,
            StatusPane::PaneBackground);
    }
    
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