#ifndef _statuspane_h_
#define _statuspane_h_

#include <memory>
#include "../inc/io_constants.h"
#include "../inc/iupdate.h"
#include "../io/screen.h"
#include "../io/window.h"
#include "../world/hero.h"

class StatusPane : public iUpdate
{
public:
    StatusPane(
        std::shared_ptr<io::Screen> screen, 
        std::shared_ptr<Hero> hero,
        unsigned int screen_row, 
        unsigned int screen_cell,
        unsigned int height,
        unsigned int width);

    virtual ~StatusPane() {}

    // iUpdate: an update notification from the world
    virtual bool update(int row, int cell, bool center = false) override;

    // time to implement all of the updates (normally called from the game)
    void refresh();

private:
    bool update();

private:
    std::shared_ptr<io::Screen> screen_;
    std::shared_ptr<Hero> hero_;
    std::shared_ptr<io::Window> window_;
    static const io::Color pane_foreground = io::Color::BRIGHT_BLACK;
    static const io::Color pane_background = io::Color::WHITE;
    static const io::Color health_foreground = io::Color::RED;
    static const io::Color energy_foreground = io::Color::BLUE;
};

#endif //  _statuspane_h_
