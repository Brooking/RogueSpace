#ifndef _blank_pane_h_
#define _blank_pane_h_

#include <memory>
#include <vector>
#include "ipane.h"
#include "iscreen.h"

//
// A blank pane to take up the spaces between real panes
//
class BlankPane final : public iPane
{
public:
    BlankPane(
        std::shared_ptr<iScreen> screen, 
        unsigned int screen_row, 
        unsigned int screen_cell,
        unsigned int height,
        unsigned int width);

    // iPane: blank panes ignore updates
    bool update(unsigned int /*row*/, unsigned int /*cell*/, bool /*center*/) override;

    // iPane: blank panes ignore updates
    bool update() override { return false; }

    // iPane: get the screen
    std::shared_ptr<iScreen> screen() const override { return this->screen_; };

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
    static const io::Color PaneForeground = io::Color::BLACK;
    static const io::Color PaneBackground = io::Color::BLACK;

private:
    std::shared_ptr<iScreen> screen_;
    std::shared_ptr<iWindow> window_;
    unsigned int screen_row_;
    unsigned int screen_cell_;
    unsigned int height_;
    unsigned int width_;
};

#endif // _blank_pane_h_