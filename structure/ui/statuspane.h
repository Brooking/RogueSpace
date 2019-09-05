#ifndef _statuspane_h_
#define _statuspane_h_

#include <memory>
#include "ipane.h"
#include "io/screen.h"
#include "io/window.h"
#include "../inc/io_constants.h"
#include "../inc/iupdate.h"
#include "../world/hero.h"

class StatusPane final : public iPane
{
public:
    StatusPane(
        std::shared_ptr<io::Screen> screen, 
        std::shared_ptr<Hero> hero,
        unsigned int screen_row, 
        unsigned int screen_cell,
        unsigned int height,
        unsigned int width);

    ~StatusPane() {}

    // iPane: get the screen
    std::shared_ptr<io::Screen> screen() const override { return this->screen_; };

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

private:
    static const io::Color pane_foreground = io::Color::BRIGHT_BLACK;
    static const io::Color pane_background = io::Color::WHITE;
    static const io::Color health_foreground = io::Color::RED;
    static const io::Color energy_foreground = io::Color::BLUE;

private:
    std::shared_ptr<io::Screen> screen_;
    std::shared_ptr<Hero> hero_;
    std::shared_ptr<io::Window> window_;
    unsigned int screen_row_;
    unsigned int screen_cell_;
    unsigned int height_;
    unsigned int width_;
};

#endif //  _statuspane_h_
