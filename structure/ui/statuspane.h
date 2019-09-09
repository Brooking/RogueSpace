#ifndef _statuspane_h_
#define _statuspane_h_

#include <memory>
#include "io_constants.h"
#include "ipane.h"
#include "iscreen.h"
#include "iupdate.h"
#include "iwindow.h"
#include "../world/hero.h"

class StatusPane final : public iPane
{
public:
    StatusPane(
        std::shared_ptr<iScreen> screen, 
        std::weak_ptr<Hero> hero,
        unsigned int screen_row, 
        unsigned int screen_cell,
        unsigned int height);

    ~StatusPane() {}

    // iPane: get the screen
    std::shared_ptr<iScreen> screen() const override { return this->screen_; };

    // iUpdate: a specific update notification from the world
    bool update(unsigned int, unsigned int, bool center = false) override;

    // iUpdate: a general update notification from the world
    bool update() override;

    // iPane: get the screen row
    unsigned int screen_row() const override { return this->screen_row_; }

    // iPane: get the screen cell
    unsigned int screen_cell() const override { return this->screen_cell_; }

    // iPane: get the pane height
    unsigned int height() const override { return this->height_; }

    // iPane: get the pane width
    unsigned int width() const override { return this->width_; }

    // iPane: completely refill the pane (includes a full update)
    void refill() override;

    // iPane: time to implement all of the updates (normally called from the game)
    void refresh() override;

protected:
    void fill_thermometer(
        unsigned int screen_row, 
        unsigned int screen_cell,
        unsigned int height,
        unsigned int label,
        unsigned int max,
        unsigned int current,
        io::Color foreground,
        io::Color background);

private:
    static const unsigned int top_margin = 0;
    static const unsigned int bottom_margin = 1;
    static const unsigned int health_cell = 1;
    static const unsigned int energy_cell = 3;
    static const unsigned int stamina_cell = 5;
    static const unsigned int status_pane_width = 7;
    static const io::Color pane_foreground = io::Color::BRIGHT_BLACK;
    static const io::Color pane_background = io::Color::WHITE;
    static const io::Color health_foreground = io::Color::RED;
    static const io::Color energy_foreground = io::Color::BLUE;
    static const io::Color stamina_foreground = io::Color::CYAN;

private:
    std::shared_ptr<iScreen> screen_;
    std::weak_ptr<Hero> hero_ptr_;
    std::shared_ptr<iWindow> window_;
    unsigned int screen_row_;
    unsigned int screen_cell_;
    unsigned int height_;
    unsigned int width_;
};

#endif //  _statuspane_h_
